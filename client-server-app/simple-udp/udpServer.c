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
      printf("Use: <ip-to-serve> <port>\n");
      return 0;
   }

   int sockett, bindd;

   struct sockaddr_in client;
   struct sockaddr_in server;

   sockett = socket(AF_INET, SOCK_DGRAM, 0); // 0 -> internet protocol
   if(sockett < 0){
      printf("%s: error trying to open socket :(\n", argv[0]);
      return 0;
   }

   server.sin_family = AF_INET;
   server.sin_addr.s_addr = inet_addr(argv[1]);
   server.sin_port = htons(atoi(argv[2]));

   // client.sin_family = AF_INET;
   // client.sin_addr.s_addr = htonl(INADDR_ANY);
   // client.sin_port = htons(0);

   bindd = bind(sockett, (struct sockaddr *) &server, sizeof(server));
   if(bindd < 0){
      printf("%s: error trying to bind\n", argv[0]);
      return 0;
   }

   printf("----- listening to %s:%s -----\n\n", argv[1], argv[2]);

   char receivedMessage[BUFFER_SIZE];
   memset(receivedMessage, 0x0, BUFFER_SIZE);
   // char sendMessage[BUFFER_SIZE];
   // memset(sendMessage, 0x0, BUFFER_SIZE);

   int clientSize;
   int bytes;
   // char back;

   while(1){
      
      clientSize = sizeof(client);
      bytes = recvfrom(sockett, receivedMessage, BUFFER_SIZE, 0, (struct sockaddr *) &client, (socklen_t *) &clientSize);
      
      if(bytes < 0){
         printf("Cannot receive message\n");
      }
      else {
         printf("client [%s:%u] --> %s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), receivedMessage);
         memset(receivedMessage, 0x0, BUFFER_SIZE);
         // printf("Do you want to send a message to this client ? (y/n) ");
         // scanf(" %c", &back);

         // if(strncmp(&back, "y", 1) == 0 ){
         //    // send a message
         //    fgets(sendMessage, BUFFER_SIZE, stdin);
         //    sendto(sockett, sendMessage, strlen(sendMessage), 0, (struct sockaddr *) &client, sizeof(client));
         // }
      }

      // memset(sendMessage, 0x0, BUFFER_SIZE);      

   }

   return 0;
}