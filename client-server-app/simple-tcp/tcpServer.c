/*
*  Alunos:
*     Erick Giffoni - 170141161
*     Geise Saunier - 190124318
*
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr
#include <stdlib.h>     // atoi
#include <string.h>     // memset

#define NUMBER_OF_CLIENTS  7
#define BUFFER_SIZE        140

int main (int argc, char * argv[]){

   if(argc < 2){
      printf("Use: <ip-to-serve> <port>\n");
      printf("\thint: if your internal ip doesnt work, try loopback: 127.0.0.1\n");
      return 1;
   }

   int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
   if(socket_descriptor < 0){
      printf("%s: error trying to open socket :(\n", argv[0]);
      return 2;
   }

   struct sockaddr_in client;
   struct sockaddr_in server;

   server.sin_family       = AF_INET;
   server.sin_addr.s_addr  = inet_addr(argv[1]);
   server.sin_port         = htons(atoi(argv[2]));

   int value = bind(socket_descriptor, (struct sockaddr *) &server, sizeof(server));
   if(value < 0 ){
      printf("%s: error trying to bind\n", argv[0]);
      return 3;
   }

   if (listen(socket_descriptor, NUMBER_OF_CLIENTS) < 0) {
     printf("%s: failed listening to port %d\n", argv[0], atoi(argv[2]));
     return 4; 
   }

   printf("----- listening to %s:%s -----\n\n", argv[1], argv[2]);

   while(1){
      if(accept(socket_descriptor, (struct sockaddr *) &client, (socklen_t *) sizeof(client)) < 0){
         printf("> failed to accept connection\n");
      }
      else{
         printf("client [%s:%u] connected\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
         char message[BUFFER_SIZE];
         
         while(1){
            memset(message, 0x0, sizeof(message));

            recv(socket_descriptor, message, sizeof(message), 0);

            if(strncmp(message, "disconnect", 9) == 0){
               printf("----- [%s:%u] disconnecting -----\n\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
               break;
            }

            printf("[%s:%u] > %s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), message);

         }
      }
   }

   return 0;
}