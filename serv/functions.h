
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_


typedef struct
{
  int port;
  int port_other;
  int sockfd;
  char *name;
} _process_data;


struct sockaddr_in *getIP(char *peer_name);
void cancel_all();
void wait();

void (*freeLists)(void*);
void freeListData(void *data);




#endif



