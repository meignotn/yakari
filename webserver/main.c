#include "socket.h"


/*void afficher_message(int socket_client){
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
			
}*/


int main(void){
	const char * message_bienvenue = "Bonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┗(°.°)┛\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n" ;  
	initialiser_signaux();
	int socket_serveur =creer_serveur(8080);
	int socket_client ;
	int resultat=0;
	http_request mon_http_request;
	
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
			FILE *fichier_client= fdopen(socket_client,"w+");			/*FILE *fichier_serveur= fdopen(socket_serveur,"w+");			*/
			char buff[8000];
			fgets_or_exit(buff,8000,fichier_client);
			printf(buff);
			resultat=parse_http_request(buff,&mon_http_request);
			skip_headers(fichier_client );
			if(!resultat){
				send_response(fichier_client,400,"Bad Request","Bad request\r\n");
			}
			else if(mon_http_request.method==HTTP_UNSUPPORTED){
				send_response(fichier_client , 405 , "Method Not Allowed" , "Method Not Allowed\r\n" );
			}
			else if(strcmp(mon_http_request.url,"/")==0){
				send_response ( fichier_client , 200 , "OK" , message_bienvenue );
			}
			else{
				send_response ( fichier_client , 404 , "Not Found" , "Not Found\r\n" );
			}
			exit(0);
		}
	}
	return 0;
}
