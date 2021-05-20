/*
*  Alunos:
*     Erick Giffoni - 170141161
*     Geise Saunier - 190124318
*
*/

#include <stdio.h>
#include <sys/types.h>  // connect
#include <sys/socket.h> // connect, getsockname
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>  // inet_addr
#include <stdlib.h>     // atoi
#include <string.h>     // memset
#include <unistd.h>     // close

#define NUMBER_OF_CLIENTS  5
#define BUFFER_SIZE        140

int main (int argc, char * argv[]){

   if(argc < 2){
      printf("Use: <server-ip> <server-port>\n");
      printf("\thint: try loopback: 127.0.0.1\n");
      return 1;
   }

   int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
   if(socket_descriptor < 0){
      printf("%s: error trying to open socket :(\n", argv[0]);
      return 2;
   }

   struct sockaddr_in server;
   struct sockaddr_in client;

   server.sin_family       = AF_INET;
   server.sin_addr.s_addr  = inet_addr(argv[1]);
   server.sin_port         = htons(atoi(argv[2]));

   socklen_t serversz = sizeof(server);
   socklen_t clientsz = sizeof(client);

   int value = connect(socket_descriptor, (struct sockaddr *) &server, serversz);
   if(value < 0 ){
      printf("%s: error trying to connect to server\n\tmake sure server is up and running\n", argv[0]);
      return 3;
   }

   printf("----- connected to %s:%s -----\n\n", argv[1], argv[2]);

   getsockname(socket_descriptor, (struct sockaddr *) &client, &clientsz);
   
   char message[BUFFER_SIZE];

   while(1){

      memset(message, 0x0, sizeof(message));
      printf("[%s:%u] > ", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

      fgets(message, BUFFER_SIZE, stdin);

      send(socket_descriptor, message, sizeof(message), 0);

      if(strncmp(message, "disconnect", 9) == 0){
         printf("----- disconnecting from [%s:%s] -----\n\n", argv[1], argv[2]);
         break;
      }
      else if(strncmp(message, "over", 4) == 0){
         /* server will talk now */
         printf("\n...waiting server [%s:%s] to respond...\n\n", argv[1], argv[2]);

         while(1){
            memset(message, 0x0, sizeof(message));

            recv(socket_descriptor, message, sizeof(message), 0);

            printf("server [%s:%s]: %s", argv[1], argv[2], message);

            if(strncmp(message, "over", 4) == 0){
               printf("\n\nserver said over, your turn\n\n");
               break;
            }
         }
      }
   }

   close(socket_descriptor);

   return 0;
}