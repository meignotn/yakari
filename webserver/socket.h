# ifndef __SOCKET_H__
# define __SOCKET_H__
#include "stats.h"
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
#include <sys/stat.h>
      



/* * Crée une socket serveur qui écoute sur toute les interfaces IPv4
de la machine sur le port passé en paramètre . La socket retournée
doit pouvoir être utilisée directement par un appel à accept .
La fonction retourne -1 en cas d ’ erreur ou le descripteur de la
socket créée . */
int creer_serveur(int port );
void initialiser_signaux(void);
void traitement_signal(int sig);
int requetevalide(char buff[]);
char * fgets_or_exit ( char * buffer , int size , FILE * stream );
enum http_method {
	HTTP_GET ,
	HTTP_UNSUPPORTED ,
};
typedef struct
{
enum http_method method ;
	int major_version ;
	int minor_version ;
	char * url ;
} http_request ;
int parse_http_request ( const char * request_line , http_request * request );
void skip_headers ( FILE * client );
void send_status ( FILE * client , int code , const char * reason_phrase );
void send_response ( FILE * client , int code , const char * reason_phrase , const char * message_body );
void send_response_fd ( FILE * client , int code , const char * reason_phrase , int fd ,char * mime);
int check_path (const char * url);
char * rewrite_url ( char * url );
int check_and_open ( const char * url , const char * document_root );
int get_file_size(int fd) ;
int copy(int in, int out);
char * getmime(char * nom);
int check_url(char * url);
void send_stats ( FILE * client );

# endif
