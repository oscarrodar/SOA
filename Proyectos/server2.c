#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/**********************************************************/
/* función MAIN */
/* Orden Parametros: Puerto */
/* */
/**********************************************************/
main(int argc, char *argv[]) 
{
int s;
struct sockaddr_in bs, in;
char entrada[255];
int sd;
if (argc == 2)
{
// Creamos el socket
s = socket(AF_INET,SOCK_DGRAM,0);
if (s != -1) 
{
bs.sin_family = AF_INET;
bs.sin_port = htons(atoi(argv[1])); //Asigna el puerto especificado por la línea de comandos
bs.sin_addr.s_addr = htonl(INADDR_ANY); //IP cualquiera de la máquina


//Asigna un nombre local al socket
if( bind(s,(struct sockaddr*)&bs, sizeof(bs)) != -1) 
{
printf("naServidor ACTIVO escuchando en el puerto: %sn",argv[1]);
//El while permite atender a múltiples clientes
while (1) 
{
//Recibe la cadena del cliente
if ( recvfrom(s,entrada, sizeof(entrada) ,0,(struct sockaddr*) &in, &sd)== -1)
perror("Error en recvfrom" );

//Devuelve la cadena al cliente
if (sendto(s,strcat(entrada, "" ; ) ,strlen(entrada)+1,0,(struct sockaddr*) &in, sizeof(in)) == -1)
perror("Error en sendto" );
}
//Se cierra el socket
close(s);
} 
else 
{
printf("ERROR al nombrar el socketn" );
}
}
else 
{
printf("ERROR: El socket no se ha creado correctamente!n" );
}
} 
else 
{
printf("nnaEl número de parámetros es incorrectonn" );
}
}