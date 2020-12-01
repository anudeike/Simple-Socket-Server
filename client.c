#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>


// set up global variables
struct sockaddr_in serv_socket;
int file_descriptor; // ids the socket
int connection; // ids the connection

char message[100] = ""; // store messages sent to the server

int start(void){
  file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  serv_socket.sin_family = AF_INET;
  serv_socket.sin_port = htons(8096);

  inet_pton(AF_INET, "127.0.0.1", &serv_socket.sin_addr); //This binds the client to localhost

  connect(file_descriptor, (struct sockaddr *)&serv_socket, sizeof(serv_socket)); //This connects the client to the server.
  while(1) {
    printf("Enter a message: ");
    fgets(message, 100, stdin);
    send(file_descriptor, message, strlen(message), 0);
    //An extra breaking condition can be added here (to terminate the while loop)
  }
}