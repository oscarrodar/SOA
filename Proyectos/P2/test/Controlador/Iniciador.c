#include "../Modelo/Iniciador.h"
#include "../Modelo/FabricaVehiculos.h"
#include <time.h>

pthread_t ponerVehiculoNormaltTh;
pthread_t ponerVehiculoNormaltTh2;
pthread_t ponerVehiculoNormaltTh3;
pthread_t ponerVehiculoNormaltTh4;
pthread_t ponerVehiculoNormaltTh5;
pthread_t vehiculoTh;
int main(){ // Boton iniciar en interfaz. Implementar junto con el terminar (finalizar).
	iniciar();
	
	int cantidad=10;
	Vehiculo vehiculo[cantidad];
	pthread_t threads[cantidad];
	int i = 0;
	for (i = 0; i < cantidad; ++i){
		vehiculo[i] = crearVehiculo((i%16)+1);
	}

	for (i = 0; i < cantidad; ++i){
		pthread_create(&threads[i], NULL, encenderAutomovil, (void*)&vehiculo[i]);
	}
	

	for (i = 0; i < cantidad; ++i){
		pthread_join(threads[i],NULL);
	}

	return 0;
}

void iniciar(){
	/**********Vista temporal************/
	///inicializarFrameBuffer();

	inicializarVectorCalles();
	inicializarVectorSemaforosCalles();
	
	inicializarVectorControlPuentes();
	inicializarVectorSemaforosControlPuentes();
}

void posicionarVehiculoY(int calle, Vehiculo vehiculo){
    sem_wait(&VectorSemaforosCalles[ROTONDA_Y]);//suponemos q si puede entrar es xq va a la primera posicion, es decir, el movimiento ya fue hecho
      vehiculo.posEnCalle=0; //Poner un vehiculo y empezar a moverlo es lo q faltaria
      
}

void * vehiculoNormal(){
  Vehiculo vehiculo = crearVehiculo(1); //donde el parametro es el tipo de vehiculo
  
  posicionarVehiculoY(ROTONDA_Y, vehiculo);//Mover se encargara de mover el carro
  
  return NULL;
}

void crearUnVehiculoNormal(){
  pthread_create(&ponerVehiculoNormaltTh, NULL, vehiculoNormal, NULL);//esto deberia esperar por la interfaz para crearlo
}

void threadVilleStart(){
 crearUnVehiculoNormal();
}
