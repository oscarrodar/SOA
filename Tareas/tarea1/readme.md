# Tarea 1 - Sistemas Operativos Avanzados

El programa rastreador despliega en pantalla una tabla que contiene información sobre los System Calls utilizados por otro programa pasado como parámetro. Esta información incluye el número del System Call, su nombre y la cantidad de veces que fue llamada

## Formato del comando: 

```bash	
$./rastreador [rastreador param] programa [programa params]
```

_'rastreador param'_ puede tomar uno de los siguientes valores:

* **-v** - Muestra la información de todos los systems calls conforme se van llamando. Se muestra el nombre del System Call, el PID del proceso que la invoca y los valores en los registros. Se muestra la info tanto cuando se entra al System Call como cuando se sale

* **-V** - Funciona igual que -v, la diferencia es que se hace una pausa entre cada System Call entry/exit de modo que el usuario debe presionar ENTER para continuar. El usuario puede escribir 'e' seguido de un Enter para salir del modo -V. Si no se especifica ninguno de los parámetros anteriores, el programa simplemente mostrará la tabla final.

_'programa'_ corresponde al nombre del programa que se desea rastrear

Por ejemplo: **ls, mkdir, cd**. En caso de que el programa a rastrear necesite sus propios parámetros, estos se especifican en 'programa params'

## Ejemplos de uso:
	
* $./rastreador -V mkdir Prueba	
* $./rastreador -v ls 
* $./rastreador cd ..