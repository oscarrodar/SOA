#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#DEFINE PORT 3600
#DEFINE MAXDATASIZE 100

int main(int argc, char *argv[])
{
int fd, numbytes;
char buf[MAXDATASIZE];
struct hostent *he;
struck sockaddr_in server;

if (argc!=2) 
{
printf("Usa:%<Direccion IP>n", argv[0];
esit(-1);
}

if (he=gethostbyname(argv[1]))==NULL)
{
printf("error en gethosbynamen" );
exit(-1);
}

if ((fd=socket(AF_INET, sock_stream,0)==-|)
{
printf("error en socketn" );
exit(-1);
}

server.sin_family=AF_INET;
server.sin_port=htons(PORT);
server.sin_addr=*((struct in_addr*) he->h_addr);
bzero(&(server.sin_zero),0);

if (connect(fd,(struct sockaddr*)&server, sizeof(struct sockaddr))==-1)
{
printf("error en connectn" );
exit(-1);
}

if (numbytes=recv(fd,buf,MAXDATASIZE,0))==-1)
{
printf("error en recvn" );
exit(-1);
}

buf[numbytes]='0';
printf("Mensaje del servidor:%n",buf);
close(fd);

}