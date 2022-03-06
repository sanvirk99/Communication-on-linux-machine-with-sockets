#include "functions.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>


//static pthread_t threadRx;
static pthread_cond_t proceed = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t cancel = PTHREAD_MUTEX_INITIALIZER;




struct sockaddr_in *getIP(char *peer_name)
{

  struct addrinfo *res;
  char *peeraddr;
  struct sockaddr_in *saddr;

  if (0 != getaddrinfo(peer_name, NULL, NULL, &res))
  {
    fprintf(stderr, "Error in resolving peer_name %s\n", peer_name);
    freeaddrinfo(res);
    exit(1);
  }

  saddr = (struct sockaddr_in *)res->ai_addr;
  peeraddr = inet_ntoa(saddr->sin_addr);

  printf("Address for %s is %s\n", peer_name, peeraddr);
  freeaddrinfo(res);

  return saddr;
}

void (*freeLists)(void*)=&freeListData;
void freeListData(void *data){

  free(data);
}


//singnal fucntion 

void cancel_all(){



    pthread_mutex_lock(&cancel);
    {
      
      pthread_cond_signal(&proceed);
    }
    pthread_mutex_unlock(&cancel);



}






//wait for all 

void wait(){



    pthread_mutex_lock(&cancel);
    {
      
      pthread_cond_wait(&proceed,&cancel);
    }
    pthread_mutex_unlock(&cancel);




}