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
#include <unistd.h>     // fork

#define NUMBER_OF_CLIENTS  127
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

   int accept_descriptor;
   pid_t child;

   while(1){
      socklen_t clientsz = sizeof(client);
      if(( accept_descriptor = accept(socket_descriptor, (struct sockaddr *) &client, &clientsz)) < 0){
        printf("%d > failed to accept connection\n", accept_descriptor);
      }
      else{
         child = fork();
         if(child == 0){
            /* child */
            printf("client [%s:%u] connected\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
            char message[BUFFER_SIZE];

            while(1){
               memset(message, 0x0, sizeof(message));

               recv(accept_descriptor, message, sizeof(message), 0);

               printf("\n[%s:%u] > %s", inet_ntoa(client.sin_addr), ntohs(client.sin_port), message);

               if(strncmp(message, "disconnect", 9) == 0){
                  printf("----- [%s:%u] disconnecting -----\n\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                  break;
               }
               else if(strncmp(message, "over", 4) == 0){
                  /* wait for client's response */
                  printf("...client said over, your turn...\n");

                  while(1){
                     memset(message, 0x0, sizeof(message));

                     printf("\nyou > ");
                     fgets(message, BUFFER_SIZE, stdin);

                     send(accept_descriptor, message, sizeof(message), 0);

                     if(strncmp(message, "over", 4) == 0){
                        printf("waiting for client [%s:%u] to respond\n\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                        break;
                     }
                  }
               } // end else if server speaking
            }
            close(accept_descriptor);
         } // end if child
         else if(child < 0){
            /* error */
            printf("%s: tried to create a child to accept client but failed\n", argv[0]);
         }
      }
      close(accept_descriptor);
   }

   return 0;
}