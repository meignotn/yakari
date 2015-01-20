#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


int creer_serveur(int port){
	int socket_serveur ;
	socket_serveur = socket ( AF_INET , SOCK_STREAM , 0);
	if ( socket_serveur == -1)
	{
		perror ( " socket_serveur " );
	/* traitement de l ’ erreur */
	}	
	/* Utilisation de la socket serveur */
	
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;/* Socket ipv4 */
	saddr.sin_port = htons (port); /* Port d ’ écoute */
	saddr.sin_addr.s_addr = INADDR_ANY ; /* écoute sur toutes les interfaces */	
	if (bind(socket_serveur,(struct sockaddr *)& saddr , sizeof( saddr )) == -1)
	{
		perror ( " bind socker_serveur " );
		/* traitement de l ’ erreur */
	}
	if ( listen ( socket_serveur , 10) == -1)
	{
		perror ( " listen socket_serveur " );
		/* traitement d ’ erreur */
	}
	
	return socket_serveur;
}
