all:
	gcc `pkg-config gtk+-3.0 --cflags` -pthread Modelo/Calles.h Modelo/GrafoCalles.h Modelo/Iniciador.h Modelo/Mapper.h Modelo/Vehiculo.h Controlador/Calles.c Controlador/Mapper.c	Controlador/FabricaVehiculos.c threadvilleUI.c Controlador/Vehiculo.c -lm -o ThreadVille `pkg-config gtk+-3.0 --libs`

