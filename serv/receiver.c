#include "receiver.h"
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

static pthread_t threadRx;
static pthread_cond_t syncOKToPrint;
static pthread_mutex_t syncOKToPrintMutex;

static int port=NULL;
static int sockrd=NULL;
static char *peer=NULL;
static int port_other=NULL;

void *recieverTx(void *data);

List *list_Rx;
//should also except the shared mutex and list 
void Receiver_init(int argc, char** argv,List *list){

  list_Rx=list;
  port = atoi(argv[1]);
  peer = argv[2];
  port_other = atoi(argv[3]);
  sockrd = socket(AF_INET, SOCK_DGRAM, 0);


 
  pthread_create(&threadRx,NULL,recieverTx,NULL);

}




void Receiver_shutdown(){

    if(pthread_join(threadRx,NULL)!=0){

       perror("reciever join error");

    };

}



void *recieverTx(void *data)
{
  
  //printf("before goin in port other %d\n",port_other);
  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);


  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(port_other);
  si_other.sin_addr.s_addr = getIP(peer)->sin_addr.s_addr;

  bind(sockrd, (struct sockaddr *)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);

  // while (1)
  // {

  //   // memset(buffer, ' ', 1024);//clear write space

  //   recvfrom(sockrd, buffer, 1024, 0, (struct sockaddr *)&si_other, &addr_size);
  //   printf("[+]Data Received: %s\n", buffer);

  //   if (buffer[0] == '!')
  //   {

  //     break;
  //   }
  // }


  // int count=0;
  // int strlenght;
  //  while(count<1)
  // {

    // memset(buffer, ' ', 1024);//clear write space
    // printf("wating on message\n");

    // int lenght=recvfrom(sockrd, buffer, 1024, 0, (struct sockaddr *)&si_other, &addr_size);

     

    // strlenght=strlen(buffer);

    // printf("recieved string lenght: %d\n",strlenght);

    
    // buffer[strlenght]=0;
    // char *str =(char*)malloc(strlenght);
    // strcpy(str,buffer);

    // printf("ptr string:%s",str);

    
    
    // if(List_prepend(list_Rx,ptr)==0){

    //   printf("sucess\n");
    // }


    //printf("[+]Data Received: %s\n", buffer);
  //   if (buffer[0] == '!')
  //   {
  //     break;
  //   }

     

  //     count++;

  //     free(str);

  // }
  
  return NULL;
}
