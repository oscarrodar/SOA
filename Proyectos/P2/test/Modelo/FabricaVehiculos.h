#ifndef FabricaVehiculo_H_
#define FabricaVehiculo_H_ 

#include "../Modelo/Vehiculo.h"
#include "../Modelo/Calles.h"
#include "../Modelo/Mapper.h"
#include "../Modelo/GrafoCalles.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_VIAJES 5

#define MAXQ 1000
int queue_array[MAXQ];
int padres[NUM_CALLES];
int solucionDireccion[NUM_CALLES];
int solucionDireccionReversa[NUM_CALLES];


void insert(int add_item);
int get();

void inicializarSolucion();
void encolarNodosAdyacentes(int nodo);

int * calcularRuta(int calleInicial, int calleFinal );

Vehiculo crearVehiculo(int tipo);

int calcularNumeroAleatorio(int tope);

int * calcularDestinosAleatorios(int numeroDeViajes);

#endif
