#include "../Modelo/FabricaVehiculos.h"
int rear = - 1;
int front = - 1;

void insert(int add_item)
{
    if (!(rear == MAXQ - 1))
    {
        if (front == - 1){
        /*If queue is initially empty */
	  front = 0;
	}
        rear = rear + 1;
        queue_array[rear] = add_item;
    }
} /*End of insert()*/
 
int get()
{
    int element=-1;
    if (!(front == - 1 || front > rear))
    {
	 // printf("Get \n");
        element=queue_array[front];
        front = front + 1;
    }
    return element;
} /*End of delete() */

void inicializarSolucion(){
  int i;
  for (i=0;i<NUM_CALLES;i++){
    //solucionDireccion[i]=-1;
      solucionDireccionReversa[i]=-1;
  }
  for (i=0;i<MAXQ;i++){
    queue_array[i]=-1;
  }
  rear=-1;
  front=-1;
}

void encolarNodosAdyacentes(int nodo){
  int i;
  int alreadyOnQ =0;
  for(i=0;i<NUM_CALLES;i++){
    if(GrafoCalles[nodo][i]){
      if(front==-1){
	//printf("Front=-1 \n");
	insert(i);
	   //printf("Nodo Insertado en q %i, com el padre %i \n", i, nodo);
	padres[i]=nodo;
      }
      else{
	int j;
	//printf("Voy a buscar en cola %i\n",alreadyOnQ);
	for(j=0;j<=rear && !alreadyOnQ;j++){ //no encola nodos ya vistados
	 // printf("buscando en cola\n");
	  if(queue_array[j]==i){
	   //  printf("Ya estaba en la cola %i \n", i);
	    alreadyOnQ=1;
	  }
	}
	// printf("Voy a insertar %i\n",alreadyOnQ);
	if (!alreadyOnQ){
	 // printf("insertar to\n");
	  insert(i);
	 // printf("Nodo Insertado en q %i, com el padre %i \n", i, nodo);
	  padres[i]=nodo;
	}
	alreadyOnQ=0;
      }
    }
  }
}

int * calcularRuta(int calleInicial, int calleFinal ){
//   printf("Ruta de %i -> % i, \n ", calleInicial,calleFinal);
   int * solucionDireccion = (int *)malloc(sizeof(int)*NUM_CALLES);
   int i;
   for (i=0;i<NUM_CALLES;i++){
    solucionDireccion[i]=-1;
  }
  inicializarSolucion();
  insert(calleInicial);
  int encontrado=0;
  int solIndice=0;
   //printf("voy a Calculando RUta \n");
  while(!(front == - 1 || front > rear) && !encontrado){
  //  printf("Calculando RUta \n");
    int nodo = get();
   // printf("Nodo %i \n", nodo);
    encolarNodosAdyacentes(nodo);
    if(nodo==calleFinal){
     // printf("Encontrado\n");
      encontrado=1;
    }
  }
  int nodoPadre=-1;
  int nodoActual=calleFinal;
  int indiceSolucionReversa=1;
  int indiceSolucion=0;;
  solucionDireccionReversa[0]=calleFinal;
  while(nodoPadre!=calleInicial){
    nodoPadre= padres[nodoActual];
    solucionDireccionReversa[indiceSolucionReversa]=nodoPadre;
    nodoActual=nodoPadre;
    indiceSolucionReversa++;
    
  }
  indiceSolucionReversa--;
  while(indiceSolucionReversa>=0){
    solucionDireccion[indiceSolucion]=solucionDireccionReversa[indiceSolucionReversa];
    indiceSolucionReversa--;
    indiceSolucion++;
    
  }
  //int j;
  //// printf("Solucion \n");
  // for(j=0;j<NUM_CALLES;j++){
	//// printf("%i, ",  solucionDireccion[j]);
   //  }
      ////  printf("SolucionFIN \n");
      return solucionDireccion;
}

Vehiculo crearVehiculo(int tipo){
  Vehiculo vehiculo;
  vehiculo.tipo=tipo;
  vehiculo.calle= ROTONDA_Y; 
  vehiculo.numeroDeViajes=(calcularNumeroAleatorio(MAX_VIAJES)+1);//se calcula un viaje mas para el ultimo viaje a Z
  vehiculo.viajesRestantes = vehiculo.numeroDeViajes; 
  ////vehiculo.numeroDeViajes=1; //borrar
  //printf("VIajes %i \n",  vehiculo.numeroDeViajes);
  vehiculo.destinos=calcularDestinosAleatorios(vehiculo.numeroDeViajes);
 //printf("despues de calcular destinos \n"); 
 vehiculo.posEnCalle=-1;
   int i,j = 0;
   vehiculo.rutas = (int **)malloc(sizeof(int *)*vehiculo.numeroDeViajes);
  for(i=0;i<vehiculo.numeroDeViajes;i++){
    vehiculo.rutas[i] = (int *)malloc(sizeof(int)*NUM_CALLES);
  }
  for(i=0;i<vehiculo.numeroDeViajes;i++){
     for(j=0;j<NUM_CALLES;j++){
	vehiculo.rutas[i][j]=-1;
     }
      if(i==0){
	vehiculo.rutas[i]=calcularRuta(ROTONDA_Y,mapearParadaCalle(vehiculo.destinos[i]));// Retorna la ruta desde Y hasta el primer destino, se mapea para obtener la calle
	
      }
      else{
	if(!(i==vehiculo.numeroDeViajes-1)){
	  vehiculo.rutas[i]=calcularRuta(mapearParadaCalle(vehiculo.destinos[i-1]),mapearParadaCalle(vehiculo.destinos[i]));// Retorna la ruta desde este hasta el proximo destino
	}
	else
	  vehiculo.rutas[i]=calcularRuta(mapearParadaCalle(vehiculo.destinos[i-1]),ROTONDA_Z);// Retorna la ruta desde este hasta el proximo destino
      }
  }

    for(i=0;i<vehiculo.numeroDeViajes;i++){
      //printf("Ruta %i\n",i);
     for(j=0;j<NUM_CALLES;j++){
	// printf("%i, ",  vehiculo.rutas[i][j]);
     }
      //printf("\n");
    }
  
  return vehiculo;
  
}

int calcularNumeroAleatorio(int tope){
  int numero;
  numero = rand() % tope + 1;
  //printf("Aleatorio %i \n",  numero);
  
  return numero;
}

int * calcularDestinosAleatorios(int numeroDeViajes){
  int i;
  int * vectorDestinos;
  vectorDestinos= (int *)malloc(sizeof(int *)*numeroDeViajes);
  for(i=0;i<numeroDeViajes;i++){
    vectorDestinos[i]=calcularNumeroAleatorio(NUM_PARADAS); //cierto sesgo a visitar y y z
  }
  //vectorDestinos[numeroDeViajes-1]=ROTONDA_Z;//ULTIMO destino siempre es Z
  return vectorDestinos;
}
