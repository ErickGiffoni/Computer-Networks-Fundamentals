/*
*  Alunos:
*     Erick Giffoni - 170141161
*     Geise Saunier - 190124318
*
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <stdlib.h>

#define BUFFER_SIZE 140

int main(int argc, char *argv[]) {

   if(argc < 2){
      printf("Use: <server-ip> <server-port>\n");
      return 0;
   }

   int sockett, bindd;

   struct sockaddr_in client;
   struct sockaddr_in server;

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = inet_addr(argv[1]);
   server.sin_port = htons(atoi(argv[2]));

   client.sin_family = AF_INET;
   client.sin_addr.s_addr = htonl(INADDR_ANY);
   client.sin_port = htons(0);

   sockett = socket(AF_INET, SOCK_DGRAM, 0); // 0 -> internet protocol
   if(socket < 0){
      printf("%s: error trying to open socket :(\n", argv[0]);
      return 0;
   }

   bindd = bind(sockett, (struct sockaddr *) &client, sizeof(client));
   if(bindd < 0){
      printf("%s: error trying to bind", argv[0]);
      return 0;
   }

   char message[BUFFER_SIZE];
   memset(message, 0, sizeof(message));

   int bytes;

   while(1){
      printf("client: ");
      fgets(message, BUFFER_SIZE, stdin);
      if(strncmp(message, "disconnect", 9) == 0){
         printf("----- client disconnecting -----\n\n");
         break;
      }
      bytes = sendto(sockett, message, strlen(message), 0, (struct sockaddr *) &server, sizeof(server));
      if(bytes < 0){
         printf("Cannot send message\n");
      }

      memset((char *) &message, 0, sizeof(message));
   }

   close(sockett);

   return 0;
}