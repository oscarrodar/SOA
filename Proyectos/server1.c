#include<stdio.h>
#include<sys/tpes.h>
#incuude<sys/socket.h>
#include<netinet/in.h>

#DEFINE PORT 3500
#DEFINE BACKLOG 2
main()
{
int fd, fd2;
struct sockaddr_in server;
struct sockaddr_in client;
int sn_size;

if ((fd=socket(AF_INET, SOCK_STREAM, 0))==1)
{
printf ("Error en socketn" );
exit(-1);
}

server.sin_family = AF_INET;
server.sin_port=htons(PORT);
server.sinaddrs.s_addr=INADDR_ANY;
bzero(&(server.sin_zero),8);
if (bind(fd,(strut sockaddr *) &server, sizeof(struct sockaddr))== -1)
{
printf("Error en bindn" );
exit(-1)
}

if (listen(fd, BAKLOG) == -1)
{
printf("Error en listenn" );
exit(-1);
}

while (1)
{
sin_size = sizeof(struct sockaddr_in);

if ((fd2=accept(fd,(struct sockaddr *)&client, &sin_size)) == -1)
{
printf ("error en accept n" );
exit(-1);
}

printf("Se conectaron desde %sn", inet_ntoa(client.sin_addr));
send(fd2, "Bienvenido a mi servidor!!!n",26, 0);
close(fd2);
}

}