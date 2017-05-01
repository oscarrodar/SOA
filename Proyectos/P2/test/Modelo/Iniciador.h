#ifndef Iniciador_H_
#define Iniciador_H_

#include <pthread.h>

 pthread_t vehiculosNormales;
 pthread_t transportePublico;
 pthread_t reparaciones;
 pthread_t puentes;

 void threadVilleStart();
void iniciar();

#endif

