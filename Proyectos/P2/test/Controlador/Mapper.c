#include "../Modelo/Mapper.h"

int mapearParadaCalle(int parada){
	if (parada < NUM_PARADAS){
		return MapeoParadasCalles[parada];
	}else{
		return -1;
	}
}


int mapearParadaPosicion(int parada){
	if (parada < NUM_PARADAS){
		return MapeoParadasPosicion[parada];
	}else{
		return -1;
	}
}

int mapearCallePuente(int calle){
	return calle-37;
}
