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

int main(int argc, char *argv[]){
	int fd=0;
	//const char * message_bienvenue = "Bonjour , bienvenue sur mon serveur \n****************\n*    YAKARI    *\n****************\nThe ultimate web server\nall your bases are belong to us\nCheck this amazing tribal dance\n\n     X \n____/ \\__o____ \n   /`-'\\ T      ___\n. /   ) \\   o ┗(°.°)┛\n /`--/--'\\ /\\   ( )	 \n:`-./A_,-'/> \\  / \\\n" ; 
	if(argc!=2){
		perror("Dossier non renseigné");
		return 0;
	}
	const char * root=argv[1];
	if(!check_path(root)){
		return 0;
	}
	init_stats();
	initialiser_signaux();
	int socket_serveur =creer_serveur(8000);
	int socket_client ;
	int resultat=0;
	http_request mon_http_request;
		while(1){
		socket_client = accept ( socket_serveur , NULL , NULL );
		sem_wait(get_semaphore());
		get_stats()->served_connections++;
		sem_post(get_semaphore());
		
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
			
			sem_wait(get_semaphore());
			(get_stats()->served_requests)++;
			sem_post(get_semaphore());

			fflush(stdout);
			if(!resultat){
				send_response(fichier_client,400,"Bad Request","Bad request\r\n");

				sem_wait(get_semaphore());
				(get_stats()->ko_400)++;
				sem_post(get_semaphore());
			
			}else if(!strcmp(mon_http_request.url,"/stats")){
				
				sem_wait(get_semaphore());
				(get_stats()->ok_200)++;
				sem_post(get_semaphore());

				send_stats (fichier_client);
			}else if(check_url(mon_http_request.url)){
				send_response(fichier_client , 403 , "Forbidden" , "Forbidden\r\n" );

				sem_wait(get_semaphore());
				(get_stats()->ko_403)++;
				sem_post(get_semaphore());
			
			}
			else if(mon_http_request.method==HTTP_UNSUPPORTED){
				send_response(fichier_client , 405 , "Method Not Allowed" , "Method Not Allowed\r\n" );
			}
			else if((fd=check_and_open(mon_http_request.url,root))!=-1){
				send_response_fd ( fichier_client , 200 , "OK" , fd,getmime(mon_http_request.url) );

				sem_wait(get_semaphore());
				(get_stats()->ok_200)++;
				sem_post(get_semaphore());


				copy(fd,socket_client);
			}
			else{
				send_response ( fichier_client , 404 , "Not Found" , "Not Found\r\n" );

				sem_wait(get_semaphore());
				(get_stats()->ko_404)++;
				sem_post(get_semaphore());
				
			}
			
			exit(0);
		}
	}
	return 0;
}
