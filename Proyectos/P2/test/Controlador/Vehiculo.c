#include "../Modelo/Vehiculo.h"
#include "../Modelo/Calles.h"
#include "../Modelo/Mapper.h"


//

int calleEnPista(int calle){
	return calle > 78;
}


int calleEnPuente(int calle){
	//return 0;	
	return (calle >= 37 && calle <= 41);
}
			
/*
* TODO: reglas para los puentes. Determinar parametros.
*/		


int esBus(int tipo){
	return tipo == BUS_NARANJA || tipo == BUS_ROSA || tipo == BUS_CELESTE || tipo == BUS_BLANCO || tipo == BUS_NEGRO || tipo == BUS_GRIS || tipo == BUS_ROJO || tipo == BUS_VERDE || tipo == BUS_AZUL;
}

void moverVehiculoEnCalle(int calle, int posEnCalle, int tipo, int viajesRestantes){
	VectorCalles[calle][posEnCalle] = tipo;
	VectorCallesViajesRestantes[calle][posEnCalle] = viajesRestantes;
}


int estoyEnUptown(int calle){
	return (calle >= 24 && calle <= 35);
}


void entrarAPuente(Vehiculo* vehiculo, int nuevaCalle){	
	int * calleActual = VectorCalles[vehiculo->calle]; 
	int * calleNueva = VectorCalles[nuevaCalle];
	int puente = mapearCallePuente(nuevaCalle);
	int * controlPuente = VectorControlPuentes[puente];
	sem_t mutexCalleNueva = VectorSemaforosCalles[nuevaCalle];
	sem_wait(&mutexCalleNueva);

	//if (Puente Moe) then
		if (estoyEnUptown(vehiculo->calle) && controlPuente[PASO_HACIA_DOWNTOWN]){			
			if (esBus(vehiculo->tipo) && calleNueva[0] == ESPACIO_VACIO && calleNueva[1] == ESPACIO_VACIO){ //Me puedo mover.
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle-1, ESPACIO_VACIO, -1);
			
				moverVehiculoEnCalle(nuevaCalle, 0, vehiculo->tipo, vehiculo->viajesRestantes);
				moverVehiculoEnCalle(nuevaCalle, 1, vehiculo->tipo, vehiculo->viajesRestantes);
				
				vehiculo->calle = nuevaCalle;
				vehiculo->posEnCalle = 1;					
				vehiculo->indiceRuta++;

				controlPuente[PASO_HACIA_DOWNTOWN]=1;
				controlPuente[PASO_HACIA_UPTOWN]=0;
				controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN]++;
			}

			if (!esBus(vehiculo->tipo) && calleNueva[0] == ESPACIO_VACIO){ //Me puedo mover.
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);			
				moverVehiculoEnCalle(nuevaCalle, 0, vehiculo->tipo, vehiculo->viajesRestantes);
				
				vehiculo->calle = nuevaCalle;
				vehiculo->posEnCalle = 0;					
				vehiculo->indiceRuta++;

				controlPuente[PASO_HACIA_DOWNTOWN]=1;
				controlPuente[PASO_HACIA_UPTOWN]=0;
				controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN]++;
			}
			
		}
		if (!estoyEnUptown(vehiculo->calle) && controlPuente[PASO_HACIA_UPTOWN]){

			if (esBus(vehiculo->tipo) && calleNueva[5] == ESPACIO_VACIO && calleNueva[4] == ESPACIO_VACIO){ //Me puedo mover.
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle-1, ESPACIO_VACIO, -1);
			
				moverVehiculoEnCalle(nuevaCalle, 5, vehiculo->tipo, vehiculo->viajesRestantes);
				moverVehiculoEnCalle(nuevaCalle, 4, vehiculo->tipo, vehiculo->viajesRestantes);
				
				vehiculo->calle = nuevaCalle;
				vehiculo->posEnCalle = 4;					
				vehiculo->indiceRuta++;
				
				controlPuente[PASO_HACIA_DOWNTOWN]=0;
				controlPuente[PASO_HACIA_UPTOWN]=1;
				controlPuente[NUM_VEHICULOS_HACIA_UPTOWN]++;
			
			}

			if (!esBus(vehiculo->tipo) && calleNueva[5] == ESPACIO_VACIO){ //Me puedo mover.
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);			
				moverVehiculoEnCalle(nuevaCalle, 5, vehiculo->tipo, vehiculo->viajesRestantes);
				
				vehiculo->calle = nuevaCalle;
				vehiculo->posEnCalle = 5;					
				vehiculo->indiceRuta++;

				controlPuente[PASO_HACIA_DOWNTOWN]=0;
				controlPuente[PASO_HACIA_UPTOWN]=1;
				controlPuente[NUM_VEHICULOS_HACIA_UPTOWN]++;
			}

			
		}

	// if (puente Larry & Joe) ...

	// if (puente Curly & Shemp) ...	

	sem_post(&mutexCalleNueva);	
}




void salirDePuente(Vehiculo* vehiculo, int nuevaCalle){	
	int * calleActual = VectorCalles[vehiculo->calle]; 
	int * calleNueva = VectorCalles[nuevaCalle];
	int puente = mapearCallePuente(vehiculo->calle);
	int * controlPuente = VectorControlPuentes[puente];
	sem_t mutexCalleNueva = VectorSemaforosCalles[nuevaCalle];
	sem_wait(&mutexCalleNueva);

	//if (Puente Moe) then
					
			if (esBus(vehiculo->tipo) && calleNueva[0] == ESPACIO_VACIO && calleNueva[1] == ESPACIO_VACIO){ //Me puedo mover.
				moverVehiculoEnCalle(nuevaCalle, 0, vehiculo->tipo, vehiculo->viajesRestantes);
				moverVehiculoEnCalle(nuevaCalle, 1, vehiculo->tipo, vehiculo->viajesRestantes);		
				if (vehiculo->posEnCalle == 5){

					///printf("pa abajooo \n");
					moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
					moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle-1, ESPACIO_VACIO, -1);
					controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN]--;
					if (controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN] == 0){
						controlPuente[PASO_HACIA_UPTOWN]=1;
					}
				}else{
					///printf("pa arribaaa \n");
					moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
					moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle+1, ESPACIO_VACIO, -1);
					controlPuente[NUM_VEHICULOS_HACIA_UPTOWN]--;
					if (controlPuente[NUM_VEHICULOS_HACIA_UPTOWN] == 0){
						controlPuente[PASO_HACIA_DOWNTOWN]=1;
					}
				}

				vehiculo->calle = nuevaCalle;
				vehiculo->posEnCalle = 1;					
				vehiculo->indiceRuta++;
			}

			if (!esBus(vehiculo->tipo) && calleNueva[0] == ESPACIO_VACIO){ //Me puedo mover.
				moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);			
				moverVehiculoEnCalle(nuevaCalle, 0, vehiculo->tipo, vehiculo->viajesRestantes);

				if (vehiculo->posEnCalle == 5){
					controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN]--;
					if (controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN] == 0){
						controlPuente[PASO_HACIA_UPTOWN]=1;
					}
				}else{
					controlPuente[NUM_VEHICULOS_HACIA_UPTOWN]--;
					if (controlPuente[NUM_VEHICULOS_HACIA_UPTOWN] == 0){
						controlPuente[PASO_HACIA_DOWNTOWN]=1;
					}
				}

				vehiculo->calle = nuevaCalle;
				vehiculo->posEnCalle = 0;					
				vehiculo->indiceRuta++;
			}

			
		
	// if (puente Larry & Joe) ...

	// if (puente Curly & Shemp) ...	

	sem_post(&mutexCalleNueva);	
}



/*
* TODO: Es un metodo aparte, ya que dependiendo de la direccion un vehiculo avanza 0..1..2..3..4..5 o avanza 5...4...3...2..1...0
* Determinar parametros 
* Ahorita el mismo metodo se llama tanto para buses como para autos
*/

void avanzarEnPuente(Vehiculo* vehiculo){
	int tipo = vehiculo->tipo;
	int calle = vehiculo->calle;
	int posEnCalle = vehiculo->posEnCalle;
	int viajesRestantes = vehiculo->viajesRestantes;
 
	sem_t mutex = VectorSemaforosCalles[calle];
	int * vectorCalle;	
	int * controlPuente;
	int puente = mapearCallePuente(calle);
	sem_wait(&mutex);	
	vectorCalle = VectorCalles[calle]; 
	controlPuente = VectorControlPuentes[puente];
	
	if (controlPuente[PASO_HACIA_UPTOWN]){ //Me estoy moviendo hacia arriba
		if (esBus(tipo)){
			if (vectorCalle[posEnCalle-1] == ESPACIO_VACIO && vectorCalle[posEnCalle-2] == ESPACIO_VACIO){ //BUS se puede mover
				moverVehiculoEnCalle(calle, posEnCalle-1, tipo, viajesRestantes);
				moverVehiculoEnCalle(calle, posEnCalle-2, tipo, viajesRestantes);
				moverVehiculoEnCalle(calle, posEnCalle, ESPACIO_VACIO, -1);
				moverVehiculoEnCalle(calle, posEnCalle+1, ESPACIO_VACIO, -1);
				vehiculo->posEnCalle = posEnCalle-2;				 
			}
		}else{
			if (vectorCalle[posEnCalle-1] == ESPACIO_VACIO){
				moverVehiculoEnCalle(calle, posEnCalle-1, tipo, viajesRestantes);
				moverVehiculoEnCalle(calle, posEnCalle, ESPACIO_VACIO, -1);
				vehiculo->posEnCalle = posEnCalle-1;
			}

		}
	}else{ // Me estoy moviendo hacia abajo
		if (esBus(tipo)){
			if (vectorCalle[posEnCalle+1] == ESPACIO_VACIO && vectorCalle[posEnCalle+2] == ESPACIO_VACIO){ //BUS se puede mover
				moverVehiculoEnCalle(calle, posEnCalle+1, tipo, viajesRestantes);
				moverVehiculoEnCalle(calle, posEnCalle+2, tipo, viajesRestantes);
				moverVehiculoEnCalle(calle, posEnCalle, ESPACIO_VACIO, -1);
				moverVehiculoEnCalle(calle, posEnCalle-1, ESPACIO_VACIO, -1);
				vehiculo->posEnCalle = posEnCalle+2;				 
			}
		}else{
			if (vectorCalle[posEnCalle+1] == ESPACIO_VACIO){
				moverVehiculoEnCalle(calle, posEnCalle+1, tipo, viajesRestantes);
				moverVehiculoEnCalle(calle, posEnCalle, ESPACIO_VACIO, -1);
				vehiculo->posEnCalle = posEnCalle+1;
			}

		}

	}
	sem_post(&mutex);
}


void moverEnPuente(Vehiculo* vehiculo){
	sem_t mutex;
	int * calle;
	int * controlPuente;
	int maxVehiculos = (vehiculo->calle == ROTONDA_Y || vehiculo->calle == ROTONDA_Z) ? MAX_VEHICULOS_ROTONDA : MAX_VEHICULOS_CALLE;
	int posFinal;
	mutex = VectorSemaforosCalles[vehiculo->calle];
	sem_wait(&mutex);
	controlPuente = VectorControlPuentes[mapearCallePuente(vehiculo->calle)];
	calle = VectorCalles[vehiculo->calle];
	//posFinal = controlPuente[PASO_HACIA_DOWNTOWN] ? 5 : 0;

	if (controlPuente[PASO_HACIA_DOWNTOWN] && !controlPuente[PASO_HACIA_UPTOWN]){
		posFinal = 5;	
	}else if (!controlPuente[PASO_HACIA_DOWNTOWN] && controlPuente[PASO_HACIA_UPTOWN]){
		posFinal = 0;
	}else if (controlPuente[PASO_HACIA_DOWNTOWN] && controlPuente[PASO_HACIA_UPTOWN]){
		posFinal = (vehiculo->posEnCalle == 5)? 0:5;
	}
	///printf("PASO_HACIA_DOWNTOWN: %i \nPASO_HACIA_UPTOWN: %i \nNUM_HACIA_DOWNTOWN: %i \nNUM_HACIA_UPTOWN: %i!!!\n", controlPuente[PASO_HACIA_DOWNTOWN], controlPuente[PASO_HACIA_UPTOWN], controlPuente[NUM_VEHICULOS_HACIA_DOWNTOWN], controlPuente[NUM_VEHICULOS_HACIA_UPTOWN]);

	if (vehiculo->posEnCalle != posFinal){
		avanzarEnPuente(vehiculo);
	}else{
		int nuevaCalle = vehiculo->rutas[vehiculo->indiceDestinos][vehiculo->indiceRuta];
		salirDePuente(vehiculo, nuevaCalle);
	}
	sem_post(&mutex);
}


void avanzarBus(Vehiculo* vehiculo){ 
	sem_t mutex;
	sem_t mutexCalleNueva;
	int * calle;
	int * calleViajesRestantes;
	int * calleNueva;
	int * calleNuevaViajesRestantes;
	int maxVehiculos = (vehiculo->calle == ROTONDA_Y || vehiculo->calle == ROTONDA_Z) ? MAX_VEHICULOS_ROTONDA : MAX_VEHICULOS_CALLE; 
			
	if ((vehiculo->calle == mapearParadaCalle(vehiculo->destinos[vehiculo->indiceDestinos]) && vehiculo->posEnCalle == mapearParadaPosicion(vehiculo->destinos[vehiculo->indiceDestinos])) || 
		(vehiculo->indiceDestinos==vehiculo->numeroDeViajes-1 && vehiculo->calle==ROTONDA_Z)){ //VERIFICA SI YA LLEGUE A DESTINO. 
		mutex = VectorSemaforosCalles[vehiculo->calle];
		sem_wait(&mutex);
		
		///printf("Soy Bus: %i. Llegue al destino: %i !!!\n", vehiculo->tipo, vehiculo->calle);
		vehiculo->indiceRuta = 1; 		
		vehiculo->indiceDestinos++; //Si ya estoy en la parada destino, debo continuar con la siguiente ruta
		vehiculo->viajesRestantes--;
		
		//hacer algo mas para que se vea graficamente que esta en una parada ?
		
		vehiculo->continuar = (vehiculo->indiceDestinos < vehiculo->numeroDeViajes); //Valida si ya estoy en el ultimo destino
		sem_post(&mutex);
		//vehiculo->calle = -1;
		//vehiculo->posEnCalle = PARADA; //Valor 10 para que en el siguiente movimiento intente entrar a posicion 0 de la siguiente calle
		if (vehiculo->continuar){
			sleep(3);
		}else{
			moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
			moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle-1, ESPACIO_VACIO, -1);
		}
	}else{

		if (!calleEnPuente(vehiculo->calle)){
			if (vehiculo->posEnCalle < (maxVehiculos - 1)) { //Si aun no llega al final de la calle
				mutex = VectorSemaforosCalles[vehiculo->calle];
				if (calleEnPuente(vehiculo->calle)){
					avanzarEnPuente(vehiculo); //TODO: Cambiar parametros 
				}else{
					sem_wait(&mutex);
					calle = VectorCalles[vehiculo->calle];
					calleViajesRestantes = VectorCallesViajesRestantes[vehiculo->calle];
		

					if ((calle[vehiculo->posEnCalle + 1] == ESPACIO_VACIO)&&(calle[vehiculo->posEnCalle + 2] == ESPACIO_VACIO)){ //Me puedo mover

						moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle + 1, vehiculo->tipo, vehiculo->viajesRestantes);
						moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle + 2, vehiculo->tipo, vehiculo->viajesRestantes);

						moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
						moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle-1, ESPACIO_VACIO, -1);

						vehiculo->posEnCalle = vehiculo->posEnCalle + 2;
					}
					sem_post(&mutex);
				}
			}else{ //Estoy en el final de la calle, debo ir a la siguiente
				//NOTA: Si hay una interseccion hay q implementar prioridades (ej. ambulancias)! Luego :D !!		
				int calleInvalida = (vehiculo->calle == -1);

				if (!calleInvalida){			
					mutex = VectorSemaforosCalles[vehiculo->calle];
					sem_wait(&mutex);
				}

				int dummyVector[vehiculo->posEnCalle];
				calle = !calleInvalida? VectorCalles[vehiculo->calle] : dummyVector ;
				calleViajesRestantes = !calleInvalida? VectorCallesViajesRestantes[vehiculo->calle] : dummyVector ;			
			
				int nuevaCalle = vehiculo->rutas[vehiculo->indiceDestinos][vehiculo->indiceRuta];

				/**************** LOGICA PARA MOVERME A UNA NUEVA CALLE*****************/

				if (nuevaCalle != -1){
					if (calleEnPuente(nuevaCalle)){
						entrarAPuente(vehiculo, nuevaCalle); //TODO: Cambiar parametros accordingly
					}else{
						calleNueva = VectorCalles[nuevaCalle];
						calleNuevaViajesRestantes = VectorCallesViajesRestantes[nuevaCalle];
		
						mutexCalleNueva = VectorSemaforosCalles[nuevaCalle];
						sem_wait(&mutexCalleNueva);
						if (calleNueva[0] == ESPACIO_VACIO && calleNueva[1] == ESPACIO_VACIO){ //Me puedo mover.
							if (!calleInvalida){
								moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
								moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle-1, ESPACIO_VACIO, -1);
							}
							moverVehiculoEnCalle(nuevaCalle, 0, vehiculo->tipo, vehiculo->viajesRestantes);
							moverVehiculoEnCalle(nuevaCalle, 1, vehiculo->tipo, vehiculo->viajesRestantes);
					
							vehiculo->calle = nuevaCalle;
							vehiculo->posEnCalle = 1;					
							vehiculo->indiceRuta++;
						}
						sem_post(&mutexCalleNueva);
					}
				}
				/***********************************************************************/

				if (!calleInvalida){			
					sem_post(&mutex);
				}
			}
		}else{
			moverEnPuente(vehiculo);
		}
	}
		
}



void avanzarAuto(Vehiculo* vehiculo){ //Para buses y ambulancias deberia ser otro metodo
	sem_t mutex;
	sem_t mutexCalleNueva;
	int * calle;
	int * calleViajesRestantes;
	int * calleNueva;
	int * calleNuevaViajesRestantes;
	int maxVehiculos = (vehiculo->calle == ROTONDA_Y || vehiculo->calle == ROTONDA_Z) ? MAX_VEHICULOS_ROTONDA : MAX_VEHICULOS_CALLE; 
			
	if ((vehiculo->calle == mapearParadaCalle(vehiculo->destinos[vehiculo->indiceDestinos]) && vehiculo->posEnCalle == mapearParadaPosicion(vehiculo->destinos[vehiculo->indiceDestinos])) || 
		(vehiculo->indiceDestinos==vehiculo->numeroDeViajes-1 && vehiculo->calle==ROTONDA_Z)){ //VERIFICA SI YA LLEGUE A DESTINO. 
		mutex = VectorSemaforosCalles[vehiculo->calle];
		sem_wait(&mutex);
		//moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
		//printf("Soy auto: %i. Llegue al destino: %i !!!\n", vehiculo->tipo, vehiculo->calle);
		vehiculo->indiceRuta = 1; 		
		vehiculo->indiceDestinos++; //Si ya estoy en la parada destino, debo continuar con la siguiente ruta
		vehiculo->viajesRestantes--;		
		vehiculo->continuar = (vehiculo->indiceDestinos < vehiculo->numeroDeViajes); //Valida si ya estoy en el ultimo destino
		sem_post(&mutex);
		//vehiculo->calle = -1;
		//vehiculo->posEnCalle = PARADA; //Valor 10 para que en el siguiente movimiento intente entrar a posicion 0 de la siguiente calle
		if (vehiculo->continuar){
			sleep(3);
		}else{
			moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
		}	
	}else{
		if (!calleEnPuente(vehiculo->calle)){
		
			if (vehiculo->posEnCalle < (maxVehiculos - 1)) { //Si aun no llega al final de la calle
				if (calleEnPuente(vehiculo->calle)){
					avanzarEnPuente(vehiculo); //TODO: Cambiar parametros
				}else{
					mutex = VectorSemaforosCalles[vehiculo->calle];
					sem_wait(&mutex);
					calle = VectorCalles[vehiculo->calle];
					calleViajesRestantes = VectorCallesViajesRestantes[vehiculo->calle];
					if (calle[vehiculo->posEnCalle + 1] == ESPACIO_VACIO){
						moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle + 1, vehiculo->tipo, vehiculo->viajesRestantes);
						moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
						vehiculo->posEnCalle = vehiculo->posEnCalle + 1;
					}
					sem_post(&mutex);
				}
		
			}else{ //Estoy en el final de la calle, debo ir a la siguiente
				//NOTA: Si hay una interseccion hay q implementar prioridades (ej. ambulancias)! Luego :D !!		

				int calleInvalida = (vehiculo->calle == -1);

				if (!calleInvalida){			
					mutex = VectorSemaforosCalles[vehiculo->calle];
					sem_wait(&mutex);
				}

				int dummyVector[vehiculo->posEnCalle];
				calle = !calleInvalida? VectorCalles[vehiculo->calle] : dummyVector ;
				calleViajesRestantes = !calleInvalida? VectorCallesViajesRestantes[vehiculo->calle] : dummyVector ;			
			
				int nuevaCalle = vehiculo->rutas[vehiculo->indiceDestinos][vehiculo->indiceRuta];

				/**************** LOGICA PARA MOVERME A UNA NUEVA CALLE*****************/

				if (nuevaCalle != -1){
					if (calleEnPuente(nuevaCalle)){
						entrarAPuente(vehiculo, nuevaCalle);
					}else{
				
						calleNueva = VectorCalles[nuevaCalle];
						calleNuevaViajesRestantes = VectorCallesViajesRestantes[nuevaCalle];
		
						mutexCalleNueva = VectorSemaforosCalles[nuevaCalle];
						sem_wait(&mutexCalleNueva);	
						if (calleNueva[0] == ESPACIO_VACIO){ //Me puedo mover.
							if (!calleInvalida){
								moverVehiculoEnCalle(vehiculo->calle, vehiculo->posEnCalle, ESPACIO_VACIO, -1);
							}
							moverVehiculoEnCalle(nuevaCalle, 0, vehiculo->tipo, vehiculo->viajesRestantes);
							vehiculo->calle = nuevaCalle;
							vehiculo->posEnCalle = 0;					
							vehiculo->indiceRuta++;
						}
						sem_post(&mutexCalleNueva);
					}
				}
				/***********************************************************************/
				if (!calleInvalida){			
					sem_post(&mutex);
				}
			}
		}else{
			moverEnPuente(vehiculo);
		}
	}
		
}


void esperar(int tipo, int pista){
	//printf("14 esperar\n");
	//int velocidad = pista? 2:1;
	int velocidad = pista? 1500:3000; //TEST: 20ms = 1s

	if (tipo == AUTO_ROJO){
		usleep(20*velocidad);
	}else if (tipo == AUTO_AZUL){
		usleep(50*velocidad);

	}else if (tipo == AUTO_VERDE){
		usleep(80*velocidad);
	}else if (tipo == AUTO_NEGRO){
		usleep(110*velocidad);
	}else if (tipo == AUTO_BLANCO){
		usleep(130*velocidad);
	}else if (tipo == AUTO_AMARILLO){
		usleep(160*velocidad);
	}else if (tipo == AMBULANCIA){
		usleep(10*velocidad);
	}else if (tipo == BUS_NARANJA){
		usleep(190*velocidad);
	}else if (tipo == BUS_ROSA){
		usleep(830*velocidad);
	}else if (tipo == BUS_CELESTE){
		usleep(830*velocidad);
	}else if (tipo == BUS_BLANCO){
		usleep(110*velocidad);
	}else if (tipo == BUS_NEGRO){
		usleep(110*velocidad);
	}else if (tipo == BUS_GRIS){
		usleep(110*velocidad);
	}else if (tipo == BUS_ROJO){
		usleep(130*velocidad);
	}else if (tipo == BUS_VERDE){
		usleep(130*velocidad);
	}else if (tipo == BUS_AZUL){
		usleep(130*velocidad);
	}
	//...
}



void* encenderAutomovil (void * parametros){
	Vehiculo *param = (Vehiculo*) parametros;
	int tipo;
	int numeroDeViajes;
	int calle;
	int posEnCalle; // valor de 0 a 5... Indica en que lugar del vector de la calle estoy
	int continuar;
	int **rutas;
	int *destinos;
	//Inicializa el automovil
	Vehiculo automovil;
	automovil.tipo = param->tipo;
	automovil.numeroDeViajes = param->numeroDeViajes;
	automovil.calle = -1; //En este momento no ha entrado a la rotonda Y
	automovil.posEnCalle = PARADA; //Numero grande para que el algoritmo de avanzar intente entrar a la rotonda Y

	automovil.rutas = param->rutas;
	automovil.destinos = param->destinos;
	automovil.indiceRuta = 0; //Me indica el lugar dentro de un vector ruta
	automovil.indiceDestinos = 0;	//Me indica la ruta y los destinos dentro de los vectores
	automovil.continuar = 1;
	
//	printf("va a iniciar el while del automovil \n");
	while (automovil.continuar){
		if (esBus(automovil.tipo)){
			avanzarBus(&automovil);
		}else{
			avanzarAuto(&automovil);
		}
//		//printf("15 voy a esperar\n");
		//printf("Soy auto: %i. Voy por calle: %i posicion: %i .\n", automovil.tipo, automovil.calle, automovil.posEnCalle);				
		
		esperar(automovil.tipo, 0);

	}
}



