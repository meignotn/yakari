#include "socket.h"
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

void afficher_message(int socket_client ){
	const char * message_bienvenue = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┗(°.°)┛\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n"  ;  
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			sleep(1);
			message_bienvenue = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┗(°.°)┓\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n"  ;
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			sleep(1);
			message_bienvenue = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┏(°.°)┛\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n" ;
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			sleep(1);
			message_bienvenue = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┗(°.°)┓\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n"  ; 
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			sleep(1);
			message_bienvenue = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┏(°.°)┛\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n" ;
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			sleep(1);
			message_bienvenue = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nBonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┗(°.°)┛\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n"  ;
			write(socket_client , message_bienvenue , strlen(message_bienvenue));
			
}


int main(void){
	initialiser_signaux();
	int socket_serveur =creer_serveur(8000);
	int socket_client ;
	
	while(1){
		socket_client = accept ( socket_serveur , NULL , NULL );
		if (socket_client == -1)
			{
				perror ( "accept" );
				/* traitement d ’ erreur */
			}		
		int pid=fork();
		if(pid!=0){
			close(socket_client);
		}else{
			FILE *fichier= fdopen(socket_client,"w+");			
			afficher_message(socket_client);
			while(1){		
				char buff[50];
				if(fgets(buff,50,fichier)==NULL){
					break;
				}
					
				fprintf(fichier,"<yakari> ");
				fprintf(fichier,buff);
			}
			exit(0);
		}
	}
	
	
	return 0;
}
