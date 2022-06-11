// Server side implementation of UDP client-server model 

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <pthread.h>
#include <curl/curl.h>
#include "base64.h"

#define PORT 53 
#define MAXLINE 5000

// Driver code 
FILE *pFile;

struct Paquete{
	socklen_t largoCliente;
	struct sockaddr_in cliente;
	unsigned char *buffer;
};

void* cliente_http(void* paquete){
    struct Paquete *pack = paquete;
    CURL *curl;
    CURLcode res;
    struct curl_slist *headerlist = NULL;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    char* encoded = base64_encode(pack->buffer);

    if(curl){
        fprintf(pFile, "Preparando datos de conexion. \n");
        fflush(pFile);
        headerlist = curl_slist_append(headerlist, "Content-Type: application/octet-stream");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_URL, "http://0.0.0.0:443/api/dns_resolver/");
        //printf("Buffer antes de cargar: %s, \n", pack->buffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, encoded);
        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);

        res = curl_easy_perform(curl);
        fprintf(pFile, "res: %d. \n", res);
        fflush(pFile);

        if(res != CURLE_OK){
            fprintf(pFile, "Error al recibir del servidor. \n");
            fflush(pFile);
        }

        curl_easy_cleanup(curl);
        
    }

    curl_global_cleanup();
}

void* admin_solicitud(void* paquete){

    struct Paquete *pack = paquete;

    //strcpy(buffer2, pack->buffer);
    //printf("Buffer entrante: %s, \n", pack->buffer);

    unsigned int qr = (unsigned int)pack->buffer[2];
    unsigned int opcode = (unsigned int)pack->buffer[2];
    int x = (int)strtol(pack->buffer, NULL, 16);

    
    //FILE * stream;
    //stream = fopen("file.txt", "w");

    //fprintf(stream, "%s", pack->buffer);

    //fclose(stream);
    
    
    qr = qr << 24;
    qr = qr >> 31;

    opcode = opcode << 25;
    opcode = opcode >> 28;

    //printf("QR: %d \n", qr);
    fprintf(pFile, "QR: %d. \n", qr);
    fflush(pFile);
    //printf("OpCode: %d \n", opcode);
    fprintf(pFile, "Opcode: %d. \n", opcode);
    fflush(pFile);

    if(!((qr != 1) && (opcode != 0))){
        fprintf(pFile, "Query no estandar. \n");
        fflush(pFile);
        cliente_http((void *) paquete);
    }

}

int main() { 
    pFile=fopen("/tmp/Serverlog", "a");
    //puts("Inicio del programa");
    fprintf(pFile, "Inicio del programa. \n");
    fflush(pFile);
    int sockfd; 
    //char buffer1[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;  

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        fprintf(pFile, "Fallo en creacion de socket. \n");
        fflush(pFile); 
        exit(EXIT_FAILURE); 
    }else{
        fprintf(pFile, "Socket creado con exito. \n");
        fflush(pFile); 
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 

    servaddr.sin_family    = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT);

    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        fprintf(pFile, "Error en el bind. \n");
        fflush(pFile);  
        exit(EXIT_FAILURE); 
    } else{
        fprintf(pFile, "Bind completo. \n");
        fflush(pFile); 
    }

    int len, n, i, x; 
    len = sizeof(cliaddr);
    x = 1;
    FILE * stream;
    while(1){

        //Struct para el manejo de la información del cliente y el buffer enviado.
        // Referencia: https://github.com/pranavgupta21/multithreaded-UDP-client-server/blob/master/server/server.c
        struct Paquete *paquete = (struct Paquete*) malloc(sizeof(struct Paquete));
        paquete->buffer = malloc(MAXLINE*sizeof(char));
        //bzero(paquete->buffer, MAXLINE);
        paquete->largoCliente = sizeof(struct sockaddr_in);
        fprintf(pFile, "Antes del recvfrom. \n");
        fflush(pFile); 
        //n = recvfrom(sockfd, (char *)buffer1, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        n = recvfrom(sockfd, paquete->buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &paquete->cliente, &paquete->largoCliente);
        fprintf(pFile, "Después de recvfrom. \n");
        fflush(pFile); 

        
        
        
        if(x==1){
            stream = fopen("file.txt", "wb");
            fwrite(paquete->buffer, 1, n, stream);
            //fprintf(stream, "%s", paquete->buffer);

            fclose(stream);
            x=0;
        }
        
        

        //fprintf(stream, "%s", paquete->buffer);


        printf("Variable n: %d \n", n);
    
        
        sleep(1);
        if(n > 0){
            pthread_t hilo;

            if(pthread_create(&hilo, NULL, admin_solicitud, (void*)paquete) > 0){
                pthread_join(hilo, NULL);

            }

        }   

    } 

    

    //sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 

    //printf("Hello message sent.\n");  

    return 0; 

}
