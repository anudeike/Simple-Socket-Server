#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>


// set up global variables
struct sockaddr_in serv_socket;
int file_descriptor; // ids the socket
int connection; // ids the connection

char message[100] = ""; // store messages sent to the server

int main(void) {

  serv_socket.sin_family = AF_INET;
  serv_socket.sin_port = htons(9000); // this defines what port it lives at  

  // open a new socket, return info about socket
  file_descriptor = socket(AF_INET, SOCK_STREAM
  , 0);

  // add if cond that checks whteher the fd is greater than 0 if it isn't prompt error
  printf("Hello World\n");
  return 0;
}