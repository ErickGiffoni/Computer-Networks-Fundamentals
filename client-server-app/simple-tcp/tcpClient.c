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
#include <netdb.h>
#include <unistd.h>

#define NUMBER_OF_CLIENTS  7
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

   server.sin_family       = AF_INET;
   server.sin_addr.s_addr  = inet_addr(argv[1]);
   server.sin_port         = htons(atoi(argv[2]));

   int value = connect(socket_descriptor, (struct sockaddr *) &server, sizeof(server));
   if(value < 0 ){
      printf("%s: error trying to connect to server\n", argv[0]);
      return 3;
   }

   printf("----- connected to %s:%s -----\n\n", argv[1], argv[2]);
   
   char message[BUFFER_SIZE];

   /* Getting client's hostname and IP address 
    * source: https://www.geeksforgeeks.org/c-program-display-hostname-ip-address/
    */
   char hostbuffer[256];
   char *IPbuffer;
   struct hostent *host_entry;
   int hostname;

   hostname = gethostname(hostbuffer, sizeof(hostbuffer));

   host_entry = gethostbyname(hostbuffer);

   IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));
   /* end of Getting client's hostname and IP address */

   while(1){

      memset(message, 0x0, sizeof(message));
      printf("[%s:%d] > ", IPbuffer, (int) getpid());

      fgets(message, BUFFER_SIZE, stdin);

      send(socket_descriptor, message, sizeof(message), 0);

      if(strncmp(message, "disconnect", 9) == 0){
         printf("----- [%s:%s] disconnecting -----\n\n", argv[1], argv[2]);
         break;
      }


   }

   close(socket_descriptor);

   return 0;
}