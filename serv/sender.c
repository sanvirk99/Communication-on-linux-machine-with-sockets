#include "sender.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "functions.h"
#include "list.h"


static char *peer=NULL;
static int port_other=NULL;
static int sockfd=NULL;

static pthread_t threadTx;

void *senderTx(void *xata);
List *list_Tx;

void Sender_init(int argc, char** argv,List *list){

  list_Tx=list;

  //copy to shared data instead of using void pointer to pass data
  
  peer = argv[2];
  port_other = atoi(argv[3]);

  //  printf("arguments (%d) are: ", argc);
  // for (int i = 0; i < argc; i++)
  // {

  //   printf("Arg %d: %s \n", i, argv[i]);
  // }
  // if (argc != 4)
  // {
  //   printf("Usage: %s <port>\n", argv[0]);
  //   exit(0);
  // }

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);


   //printf("before goin in port other %d\n",recTx.port_other);
   pthread_create(&threadTx,NULL,senderTx,NULL);

  //gives time for get ip to get the data in send
   //sleep(1);

}


void Sender_shutdown(){
    

    pthread_join(threadTx,NULL);


}


void *senderTx(void *xata)
{

  printf("sender peer = %s \n",peer);
  printf("sender peer port= %d\n",port_other);

 
  char buffer[1024];
  struct sockaddr_in si_other;
  memset(&si_other, '\0', sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(port_other);

  si_other.sin_addr.s_addr = getIP(peer)->sin_addr.s_addr;

  int count=0;
  while(count<5){
  sleep(1);
  strcpy(buffer, "Hello other main stalk here\n");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, sizeof(si_other));
  printf("[+]Data Send: %s\n", buffer);

  count++;
  if(count==5){

    strcpy(buffer, "!\n");
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
    printf("[+]Data Send: %s", buffer);

    }


  }
  return NULL;
  
}