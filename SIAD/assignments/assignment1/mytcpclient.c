/*Logan Holbrook Assignment 1*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[]){
   char *url = argv[1];
   char path[100];
   char host[100];
   sscanf(url, "http://%[^/]/%s", host, path);

   printf("Client program\n");
   if(argc > 2){
      printf("Usage: %s <url>\n", argv[0]);
      exit(0);
   }
   //port = atoi(argv[2]);
   printf("URL = %s, host = %s, path = /%s\n", url, host, path);

   int socketfd;
   socketfd = socket(AF_INET, SOCK_STREAM, 0);
   if(socketfd < 0){
      perror("ERROR opening socket");
      close(socketfd);
   }

   struct hostent *server_he;
   if((server_he = gethostbyname(host)) == NULL){
      perror("ERROR in gethostbyname\n");
      return 2;
   }

   struct sockaddr_in serveraddr;
   bzero((char *) &serveraddr, sizeof(serveraddr));
   serveraddr.sin_family = AF_INET;

   bcopy((char *)server_he->h_addr, (char *)&serveraddr.sin_addr.s_addr, server_he->h_length);
   serveraddr.sin_port = htons(80);

   if(connect(socketfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
      perror("Cannot connect to the server\n");
      exit(0);
   }else
      printf("Connected to the server\n");

   char request[255];
   if (path == NULL){
      sprintf(request, "GET / HTTP/1.0\r\nHost: %s\r\n\r\n", host);
   }else{
      sprintf(request, "GET /%s HTTP/1.0\r\nHOST: %s\r\n\r\n", path, host);
   }

   //char *msg = "GET / HTTP/1.0\r\n\r\n";
   int bytes_sent;
   bytes_sent = send(socketfd, request, strlen(request), 0);

   char buffer[10000];
   int byte_received;
   bzero(buffer, 10000);
   byte_received = recv(socketfd, buffer, 10000, 0);

   char* endOfHeader = strstr(buffer, "\r\n\r\n");
   int headerLength = endOfHeader - buffer;
   int lengthOfData = byte_received - (headerLength + 4);

   char *ext;
   const char ch = '.';
   ext = strrchr(buffer, ch);
   printf("The data part is: %d\n", lengthOfData);

   FILE *outfile;
   outfile = fopen("file.ext", "w+");
   fwrite(endOfHeader + 4, lengthOfData, 1, outfile);
   int recv_count;
   while((recv_count = recv(socketfd, buffer, 10000, 0)) != 0){
      fwrite(buffer, recv_count, 1, outfile);
   }
   fclose(outfile);

   if(byte_received < 0)
      perror("ERROR reading from socket\n");
   printf("Message received: %s\n", buffer);

   return 0;
}
