#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"

#define PORT 5000
#define BUF_SIZE 2000
#define CLADDR_LEN 100

void * receiveMessage(void * socket) {
 int sockfd, ret; // get the socket file description

 char buffer[BUF_SIZE]; 

 sockfd = (int) socket;

 memset(buffer, 0, BUF_SIZE);  

// forever runnng while loop
 while (1) {
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  
  if (ret < 0) {  
   printf("Error receiving data\n");    
  } else {
   printf("client: ");
   fputs(buffer, stdout);
   //printf("\n");
  }  
 }
}

int main(void) {

  // set up tht addresses
 struct sockaddr_in addr, cl_addr;

 // file descriptors
 int sockfd, len, ret, newsockfd;
 char buffer[BUF_SIZE];

 // get the pid of the childprocess
 pid_t cpid;
 char clientAddr[CLADDR_LEN];
 pthread_t rThread;
 
 // create a socket 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");
 
 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY;
 addr.sin_port = PORT;
 
 ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Couldn't Bind!\n");
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection ===> \n");
 listen(sockfd, 5);


// directly handle connection
 len = sizeof(cl_addr);
 newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
 if (newsockfd < 0) {
  printf("Could not accept connection!\n");
  exit(1);
 } 

 // not sure what library I need to import for this
 inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
 printf("Connection accepted from %s...\n", clientAddr); 
 
 // reset the biffer size
 memset(buffer, 0, BUF_SIZE);
 printf("Enter your messages one by one and press return key!\n");

 //creating a new thread for receiving messages from the client
 ret = pthread_create(&rThread, NULL, receiveMessage, (void *) newsockfd);
 if (ret) {
  printf("ERROR: return code form p thread is %d\n", ret);
  exit(1);
 }


 while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
  ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);  
  if (ret < 0) {  
   printf("COULD NOT SEND DATA: Error sending data!\n");  
   exit(1);
  }
 }   
 
 close(newsockfd);
 close(sockfd);

 pthread_exit(NULL);
 return 0;
}