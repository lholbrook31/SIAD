/*Logan Holbrook Lab 2*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[]){
   char servername[256];

   printf("Client program\n");
   if(argc != 3){
      printf("Usage: %s <server> <port>\n", argv[0]);
      exit(0);
   }

   strcpy(servername, argv[1]);
   printf("Server: ");
   printf(servername);
   printf("\n");
   return 0;

  /* servername = argv[1];
   port = atoi(argv[2]);
   printf("Servername = %s, port = %d\n", servername, port);

   //The socket is a protocol that creates a channel over a TCP connection.
   int socketfd;
   socketfd = socket(AF_INET, SOCK_STREAM, 0);
   if(socketfd < 0){
      perror("ERROR opening socket");
      close(socketfd);
   }

   struct hostent *server_he;
   if((server_he = gethostbyname(servername)) == NULL){
      perror("ERROR in gethostbyname\n");
      return 2;
   }

   //builds the server's Internet address
   struct sockaddr_in serveraddr;
   bzero((char *) &serveraddr, sizeof(serveraddr));
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serveraddr.sin_port = htons(port);
   serveraddr.sin_family = AF_INET;

   bcopy((char *)server_he->h_addr, (char *)&serveraddr.sin_addr.s_addr, server_he->h_length);
   serveraddr.sin_port = htons(port);

   //creates a connection with the server
   if(connect(socketfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
      perror("Cannot connect to the server\n");
      exit(0);
   }else
      printf("Connected to the server\n");

   //sends the test message to the server
   char *msg = "THis is a test message from client.";
   int bytes_sent;
   bytes_sent = send(socketfd, msg, strlen(msg), 0);

   //acknowledges if the message was echoed back
   char buffer[1024];
   int byte_received;
   bzero(buffer, 1024);
   byte_received = recv(socketfd, buffer, 1024, 0);
   if(byte_received < 0)
      perror("ERROR reading from socket\n");
   printf("Message received: %s\n", buffer);

   return 0;*/
}
