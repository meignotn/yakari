#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h> 
int main(){
	fflush(stdout);
	printf("hello world");
	int socket_serveur =creer_serveur(8000);
	int socket_client ;
	char * buff=malloc(50);
	printf("test");
	
	while(1){
		socket_client = accept ( socket_serveur , NULL , NULL );
		if ( socket_client == -1)
		{
			perror ( " accept " );
			/* traitement d ’ erreur */
		}	
			const char * message_bienvenue = " Bonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\n check this amazing tribal dance\n\n     X \n____/ \\__o____ ┗(°.°)┓\n   /`-'\\ T\n. /   ) \\   o  ┗(°.°)┛\n /`--/--'\\ /\\ \n:`-./A_,-'/> U ┏(°.°)┛"  ;
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			while(1==1){
				read(socket_client,buff,50);
				write(socket_client , buff , 50);
			}
		}
	
	
	return 0;
}
