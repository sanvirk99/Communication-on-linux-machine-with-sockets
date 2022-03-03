#include "receiver.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


static pthread_t threadRx;

void *recieverTx(void *xata);


//should also except the shared mutex and list 
void Receiver_init(int argc, char** argv){

  int port = atoi(argv[1]);
  char *other_name = argv[2];
  int port_other = atoi(argv[3]);

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  
  _process_data recTx;
  recTx.port=port;
  recTx.sockfd=sockfd;
  recTx.port_other=port_other;
  recTx.name=other_name;
  printf("before going in thread rec %s \n",recTx.name);
  pthread_create(&threadRx,NULL,recieverTx,&recTx);

}




void Receiver_shutdown(){

     pthread_join(threadRx,NULL);

}



void *recieverTx(void *xata)
{
  _process_data *data = xata;
  int sockfd = data->sockfd;
  int port = data->port;

  printf("before going in getIP rec %s \n",data->name);
  //printf("before goin in port other %d\n",port_other);


  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd, (struct sockaddr *)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);

//   while (1)
//   {

//     // memset(buffer, ' ', 1024);//clear write space

//     recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, &addr_size);
//     printf("[+]Data Received: %s\n", buffer);

//     if (buffer[0] == '!')
//     {

//       break;
//     }
//   }

  return NULL;
}
