#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// resource https://github.com/nikhilroxtomar/UDP-Client-Server-Program-in-C.git
#include <netdb.h>

// threads
#include <pthread.h>

#include <sys/ioctl.h>
#include <net/if.h>

//modules
#include "functions.h"
#include "console.h"
#include "input.h"
#include "output.h"
#include "sender.h"
#include "receiver.h"
#include "list.h"


#define MSG_MAX_LEN 1024
#define PORT 22110

// typedef struct
// {
//   int port;
//   int port_other;
//   int sockfd;
//   char *name;
// } _process_data;



//routines
void test1(int argc,char **argv);
void threads(int argc,char **argv);
void threads_user();
void app_test1(int argc, char **argv);

//fuunction/threads
//struct sockaddr_in *getIP(char *peer_name);
void *recieveTx(void *xata);
void *sendTx(void *xata);
void *input(void *data);
void *output(void *data);


int main(int argc, char **argv)
{
  //mutex locks distrubuted here
  //test1(argc,argv);

  //testes and ran physially on computer
  //threads(argc,argv);

  //threads_user();
  app_test1(argc,argv);
 
  
}



void app_test1(int argc, char **argv){

  List *recive_list=List_create();
  List *sender_list=List_create();

   pthread_cond_t syncOKToPrint = PTHREAD_COND_INITIALIZER;
   pthread_mutex_t syncOKToPrintMutex = PTHREAD_MUTEX_INITIALIZER;



  Input_init(sender_list);
  Output_init(recive_list);
  Receiver_init(argc,argv,recive_list);
  Sender_init(argc,argv,sender_list);

  Receiver_shutdown();
  Sender_shutdown();
  Output_shutdown();
  Input_shutdown();


}

// sockid does it need to be same yes i guess cause bind is nesscary but on client side create two sockets
// need to printo screen and recieve from screen threads wrting to memory
// test using net cat
// testing csil machine adrress conversion
// use the orginal assgin 3 program to
//sperated recieve aand post threads
//
void threads_user(){

  
  //console_init();

  //console_wait();




}
void threads(int argc, char** argv){


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

  int port = atoi(argv[1]);
  char *other_name = argv[2];
  int port_other = atoi(argv[3]);

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  pthread_t threadPID,threadSD;
  _process_data recTx;
  recTx.port=port;
  recTx.sockfd=sockfd;
  recTx.port_other=port_other;
  recTx.name=other_name;

  //call recieve fucntion here
  pthread_create(&threadPID,NULL,recieveTx,&recTx);

  pthread_create(&threadSD,NULL,sendTx,&recTx);
  pthread_join(threadSD,NULL);
  pthread_join(threadPID,NULL);
}

void *recieveTx(void *xata)
{
  _process_data *data = xata;
  int sockfd = data->sockfd;
  int port = data->port;

  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(sockfd, (struct sockaddr *)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);

  while (1)
  {

    // memset(buffer, ' ', 1024);//clear write space

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, &addr_size);
    printf("[+]Data Received: %s\n", buffer);

    if (buffer[0] == '!')
    {

      break;
    }
  }

  return NULL;
}

void *sendTx(void *xata)
{

  _process_data *data = xata;
  int sockfd = data->sockfd;
  int port_other = data->port_other;
  char *other_name = data->name;
  char buffer[1024];
  struct sockaddr_in si_other;
  memset(&si_other, '\0', sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(port_other);
  si_other.sin_addr.s_addr = getIP(other_name)->sin_addr.s_addr;

  int count=0;
  while(count<5){
  sleep(1);
  strcpy(buffer, "Hello other main client here\n");
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



void test1(int argc,char **argv){


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

  int port = atoi(argv[1]);
  char *other_name = argv[2];
  int port_other = atoi(argv[3]);

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);


  struct sockaddr_in si_me, si_other;
  char buffer[1024];
  socklen_t addr_size;

  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  //si_me.sin_addr.s_addr = localIP()->sin_addr.s_addr;
  si_me.sin_addr.s_addr =htonl(INADDR_ANY) ;

  bind(sockfd, (struct sockaddr *)&si_me, sizeof(si_me));
  addr_size = sizeof(si_other);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, &addr_size);
  printf("[+]Data Received: %s", buffer);

  // newcode

  memset(&si_other, '\0', sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(port_other);
  si_other.sin_addr.s_addr = getIP(other_name)->sin_addr.s_addr;

  strcpy(buffer, "Hello other\n");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, sizeof(si_other));
  printf("[+]Data Send: %s", buffer);


}


//can be modiefied to iclude port number but will need to be testes
// struct sockaddr_in *getIP(char *peer_name)
// {

//   struct addrinfo *res;
//   char *peeraddr;
//   struct sockaddr_in *saddr;

//   if (0 != getaddrinfo(peer_name, NULL, NULL, &res))
//   {
//     fprintf(stderr, "Error in resolving peer_name %s\n", peer_name);
//     exit(1);
//   }

//   saddr = (struct sockaddr_in *)res->ai_addr;
//   peeraddr = inet_ntoa(saddr->sin_addr);

//   printf("Address for %s is %s\n", peer_name, peeraddr);

//   return saddr;
// }

