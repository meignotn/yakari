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
#include <signal.h>
#include <sys/wait.h>

#include "socket.h"
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
	int optval = 1;
	if ( setsockopt ( socket_serveur , SOL_SOCKET , SO_REUSEADDR , & optval , sizeof(int)) == -1)
		perror ( " Can not set SO_REUSEADDR option " );	
	if (bind(socket_serveur,(struct sockaddr *)& saddr , sizeof( saddr )) == -1)
	{
		perror ( " bind socket_serveur " );
		/* traitement de l ’ erreur */
	}
	if ( listen ( socket_serveur , 10) == -1)
	{
		perror ( " listen socket_serveur " );
		/* traitement d ’ erreur */
	}
	
	
	
	return socket_serveur;
}

void initialiser_signaux(void){
	if ( signal ( SIGPIPE , SIG_IGN ) == SIG_ERR )
	{
		perror ( " signal " );
	}
	struct sigaction sa ;
	sa.sa_handler = traitement_signal ;
	sigemptyset (& sa.sa_mask );
	sa.sa_flags = SA_RESTART ;
	if ( sigaction (SIGCHLD,&sa,NULL ) == -1)
	{
		perror ( " sigaction ( SIGCHLD ) " );
	}
}

void traitement_signal(int sig ){
	if(sig==SIGCHLD){
		waitpid(-1,0,WNOHANG);
	}
}
int requetevalide(char buff[]){
	int i=0;
	int nbmot=1;
	int debut_troisieme_mot=0;
	int debut_deuxieme_mot=0;
	while(buff[i]!='\0' && i!=8000){
		if(buff[i]==' '){
			if(buff[i-1]!=' '){
				nbmot++;
				if(debut_deuxieme_mot==0){
					debut_deuxieme_mot=i+1;
				}
				debut_troisieme_mot=i+1;
			}
		}
		i++;
	}
	
	if(nbmot!=3){
		return 400;
	}
	if(!(buff[0]=='G' && buff[1]=='E' && buff[2]=='T')){
		return 400;
	}
	if(!(buff[debut_troisieme_mot]=='H' && buff[debut_troisieme_mot+1]=='T' && buff[debut_troisieme_mot+2]=='T' && buff[debut_troisieme_mot+3]=='P' && buff[debut_troisieme_mot+4]=='/')){
		return 400;
	}if(!(buff[debut_troisieme_mot+5]>='0' && buff[debut_troisieme_mot+5]<='1')){
		return 400;
	}if(!(buff[debut_troisieme_mot+6]=='.')){
		return 400;
	}if(!(buff[debut_troisieme_mot+7]>='0' && buff[debut_troisieme_mot+7]<='9')){
		return 400;
	}if(!(buff[debut_deuxieme_mot]=='/' && buff[debut_deuxieme_mot+1]==' ')){
		return 404;
	}
	
	return 200;
}

