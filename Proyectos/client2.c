#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**********************************************************/
/* función MAIN */
/* Orden Parametros: IP destino, puerto , mensaje */
/* */
/**********************************************************/
main(int argc, char *argv[]) 
{
int s;
struct sockaddr_in bs,des;
char resp[255];
int *sd;

if (argc == 4) 
{
// Creamos el socket
s = socket(AF_INET,SOCK_STREAM,0);

if (s != -1) 
{
bs.sin_family = AF_INET;
bs.sin_port = htons(0); //Asigna un puerto disponible dela máquina
bs.sin_addr.s_addr = htonl(INADDR_ANY); //Asigna una IP de la máquina

//Asigna un nombre local al socket
if ( bind(s,(struct sockaddr*)&bs, sizeof(bs)) != -1) 
{
//Se prepara el nombre de la máquina remota
des.sin_family = AF_INET;
des.sin_addr.s_addr = inet_addr(argv[1]);
des.sin_port = htons(atoi(argv[2]));

//Establece la conexión con la máquina remota
connect(s,(struct sockaddr*)&des,sizeof(des));

//Envía el mensaje
send(s,argv[3],strlen(argv[3])+1,0);
printf("nn->Enviando: %s, a: %s en el puerto: %s n",argv[3], argv[1], argv[2]);
//Recibe la respuesta
recv(s,resp, sizeof(resp) ,0);
printf("<-Recibido: %sn",resp);
//Se cierra la conexión (socket)
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