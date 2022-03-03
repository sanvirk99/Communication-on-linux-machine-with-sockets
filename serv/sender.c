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

typedef struct
{
  int port;
  int port_other;
  int sockfd;
  char *name;
} process_data;


static pthread_t threadTx;

void *senderTx(void *xata);



void Sender_init(int argc, char** argv){


  int port = atoi(argv[1]);
  char *other_name = argv[2];
  int port_other = atoi(argv[3]);

   printf("arguments (%d) are: ", argc);
  for (int i = 0; i < argc; i++)
  {

    printf("Arg %d: %s \n", i, argv[i]);
  }
  if (argc != 4)
  {
    printf("Usage: %s <port>\n", argv[0]);
    exit(0);
  }

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  process_data recTx;
  recTx.port=port;
  recTx.sockfd=sockfd;
  recTx.port_other=port_other;
  recTx.name=other_name;

   printf("before going in thread send %s \n",recTx.name);
   //printf("before goin in port other %d\n",recTx.port_other);
   pthread_create(&threadTx,NULL,senderTx,&recTx);

}


void Sender_shutdown(){
    

    pthread_join(threadTx,NULL);


}


void *senderTx(void *xata)
{

  process_data *data = xata;
  int sockfd = data->sockfd;
  int port_other = data->port_other;
  char *other_name = data->name;
 
  char buffer[1024];
  struct sockaddr_in si_other;
  memset(&si_other, '\0', sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(port_other);


  printf("before going in getip send %s \n",other_name);
//printf("before goin in port other %d\n",port_other);

  si_other.sin_addr.s_addr = getIP(other_name)->sin_addr.s_addr;

  int count=0;
//   while(count<5){
//   sleep(1);
//   strcpy(buffer, "Hello other main stalk here\n");
//   sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, sizeof(si_other));
//   printf("[+]Data Send: %s\n", buffer);

//   count++;
//   if(count==5){

//     strcpy(buffer, "!\n");
//     sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, sizeof(si_other));
//     printf("[+]Data Send: %s", buffer);

//     }


//   }
  return NULL;
  
}