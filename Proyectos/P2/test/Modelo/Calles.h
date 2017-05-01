#ifndef Calle_H_
#define Calle_H_

#include <semaphore.h>
#define PARADA 10
#define ESPACIO_VACIO 0
#define MAX_VEHICULOS_CALLE 6 //Si decidimos manejar diferentes capacidades por calle (Ej. puente, rotonda), es mejor usar un vector
#define MAX_VEHICULOS_ROTONDA 4
#define NUM_CALLES 103
#define ROTONDA_Y 36
#define ROTONDA_Z 42

#define PASO_HACIA_DOWNTOWN 0
#define PASO_HACIA_UPTOWN 1
#define NUM_VEHICULOS_HACIA_DOWNTOWN 2
#define NUM_VEHICULOS_HACIA_UPTOWN 3


extern int VectorCalles[NUM_CALLES][MAX_VEHICULOS_CALLE]; //Se inicializa en Calles.c
extern int VectorCallesViajesRestantes[NUM_CALLES][MAX_VEHICULOS_CALLE]; //Se inicializa en Calles.c
extern sem_t VectorSemaforosCalles[NUM_CALLES]; // Inicializar en Calles.c si es necesario

extern int VectorControlPuentes[5][4];
extern sem_t VectorSemaforosControlPuentes[5];

int VectorCallesViajesRestantes[NUM_CALLES][MAX_VEHICULOS_CALLE];
int VectorCalles[NUM_CALLES][MAX_VEHICULOS_CALLE];
sem_t VectorSemaforosCalles[NUM_CALLES];

int VectorControlPuentes[5][4];
sem_t VectorSemaforosControlPuentes[5];

void inicializarVectorCalles();
void inicializarVectorSemaforosCalles();


#endif
