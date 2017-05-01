#ifndef Vehiculo_H_
#define Vehiculo_H_

#include <stdlib.h>
#include <stdio.h>

//Tipos de Vehiculos
#define AUTO_ROJO 1
#define AUTO_AZUL 2
#define AUTO_VERDE 3
#define AUTO_NEGRO 4
#define AUTO_BLANCO 5
#define AUTO_AMARILLO 6
#define AMBULANCIA 7
#define BUS_NARANJA 8
#define BUS_ROSA 9
#define BUS_CELESTE 10
#define BUS_BLANCO 11
#define BUS_NEGRO 12
#define BUS_GRIS 13
#define BUS_ROJO 14
#define BUS_VERDE 15
#define BUS_AZUL 16

typedef struct Vehiculo {
	int tipo;
	int numeroDeViajes;
	int viajesRestantes;
	int calle;
	int posEnCalle; // valor de 0 a 5... Indica en que lugar del vector de la calle estoy
	int continuar;
	int **rutas;
	int *destinos;
	int indiceDestinos;
	int indiceRuta;
} Vehiculo;

void* encenderAutomovil(void * parametros);

#endif
