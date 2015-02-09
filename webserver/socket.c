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
/*int requetevalide(char buff[]){
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
		return 1;
	}
	if(!(buff[0]=='G' && buff[1]=='E' && buff[2]=='T')){
		return 1;
	}
	if(!(buff[debut_troisieme_mot]=='H' && buff[debut_troisieme_mot+1]=='T' && buff[debut_troisieme_mot+2]=='T' && buff[debut_troisieme_mot+3]=='P' && buff[debut_troisieme_mot+4]=='/')){
		return 1;
	}if(!(buff[debut_troisieme_mot+5]>='0' && buff[debut_troisieme_mot+5]<='1')){
		return 1;
	}if(!(buff[debut_troisieme_mot+6]=='.')){
		return 1;
	}if(!(buff[debut_troisieme_mot+7]>='0' && buff[debut_troisieme_mot+7]<='9')){
		return 1;
	}if(!(buff[debut_deuxieme_mot]=='/' && buff[debut_deuxieme_mot+1]==' ')){
		return 404;
	}
	
	return 200;
}*/
char * fgets_or_exit ( char * buffer , int size , FILE * stream ){
	if(fgets(buffer,size,stream)==NULL){
		printf("%s",buffer);
		exit(1);
	}
	return buffer;
}
int parse_http_request ( const char * request_line , http_request * request ){
	int i=0;
	int nbmot=1;
	int debut_troisieme_mot=0;
	int debut_deuxieme_mot=0;
	while(request_line[i]!='\0' && i!=8000){
		if(request_line[i]==' '){
			nbmot++;
			if(debut_deuxieme_mot==0){
				debut_deuxieme_mot=i+1;
			}
			debut_troisieme_mot=i+1;
			
		}
		i++;
	}
	
	if(nbmot!=3){
		return 0;
	}
	char * url = malloc(debut_troisieme_mot-debut_deuxieme_mot-1);
	char * buf =url;
	while(debut_deuxieme_mot<debut_troisieme_mot-1){
		*buf=request_line[debut_deuxieme_mot];
		buf++;
		debut_deuxieme_mot++;
	}
	request->url=url;
	
	if(!(request_line[0]=='G' && request_line[1]=='E' && request_line[2]=='T')){
		return 0;
	}else{
		request->method=HTTP_GET;
	}
	if(!(request_line[debut_troisieme_mot]=='H' && request_line[debut_troisieme_mot+1]=='T' && request_line[debut_troisieme_mot+2]=='T' && request_line[debut_troisieme_mot+3]=='P' && request_line[debut_troisieme_mot+4]=='/')){
		return 0;
	}if(!(request_line[debut_troisieme_mot+5]=='1')){
		return 0;
	}if(!(request_line[debut_troisieme_mot+6]=='.')){
		return 0;
	}if(!(request_line[debut_troisieme_mot+7]>='0' && request_line[debut_troisieme_mot+7]<='1')){
		return 0;
	}
	
	return 1;
}
void skip_headers(FILE * fichier_client){
	char buffer[8000];
	fgets_or_exit(buffer,8000,fichier_client);
	while(!(buffer[0]=='\n' || (buffer[0]=='\r' && buffer[1]=='\n'))){
		fgets_or_exit(buffer,8000,fichier_client);
		printf(buffer);
	}
}


void send_status ( FILE * fichier_client , int code , const char * reason_phrase ){
	fprintf(fichier_client, "HTTP/1.1 %d %s\r\n",code,reason_phrase);
}
void send_response ( FILE * fichier_client , int code , const char * reason_phrase , const char * message_body ){
	send_status(fichier_client,code,reason_phrase);
	fprintf(fichier_client,"Connection: close\r\nContent-Length: %d\n\r\n",(int) strlen(message_body));
	fprintf(fichier_client,"%s",message_body);
}
