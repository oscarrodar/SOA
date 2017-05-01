#include "../Modelo/Calles.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void inicializarVectorCalles(){
	int i=0, j=0, limite=0;	
	for (i = 0; i < NUM_CALLES; ++i){
	  if(i!= ROTONDA_Z && i!= ROTONDA_Y){
	    limite=MAX_VEHICULOS_ROTONDA;
	  }
	  else{
	    limite= MAX_VEHICULOS_CALLE;
	  }
		for (j=0; j < limite; ++j){
		  
			VectorCalles[i][j]=ESPACIO_VACIO;

		}
	}
}

void inicializarVectorCallesViajesRestantes(){
	int i=0, j=0, limite=0;	
	for (i = 0; i < NUM_CALLES; ++i){
	  if(i!= ROTONDA_Z && i!= ROTONDA_Y){
	    limite=MAX_VEHICULOS_ROTONDA;
	  }
	  else{
	    limite= MAX_VEHICULOS_CALLE;
	  }
		for (j=0; j < limite; ++j){
		  
			VectorCallesViajesRestantes[i][j]=-1;
		}
	}
}


void inicializarVectorSemaforosCalles(){
	int i=0;
	for (i = 0; i < NUM_CALLES; ++i){
	    sem_init(&VectorSemaforosCalles[i],0,1);
	  
	}
}

void inicializarVectorControlPuentes(){
	int i=0;
	for (i = 0; i < 5; ++i){
	    VectorControlPuentes[i][0] = 1;
	    VectorControlPuentes[i][1] = 1;
	    VectorControlPuentes[i][2] = 0;
	    VectorControlPuentes[i][3] = 0;
	}
}


void inicializarVectorSemaforosControlPuentes(){
	int i=0;
	for (i = 0; i < 5; ++i){
	    sem_init(&VectorSemaforosControlPuentes[i],0,1);
	}
}


