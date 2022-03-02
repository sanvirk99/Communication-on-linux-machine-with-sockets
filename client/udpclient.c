#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

//resource https://github.com/nikhilroxtomar/UDP-Client-Server-Program-in-C.git
#include<netdb.h>

#define MSG_MAX_LEN 1024
#define PORT 22110

typedef struct
{
  int port;
  int port_other;
  int sockfd;
  char *name;
} _process_data;



//https://www.binarytides.com/c-program-to-get-ip-address-from-interface-name-on-linux/
//https://github.com/unimonkiez/c-linux-example/blob/master/src/nslookup.c

void test1(int argc,char **argv);
void threads(int argc,char **argv);
struct sockaddr_in *getIP(char *peer_name);
void *recieveTx(void *xata);
void *sendTx(void *xata);




int main(int argc,char** argv){

 
 //test1(argc,argv);

threads(argc,argv);

}


void test1(int argc,char **argv){

 printf("arguments (%d) are: ",argc);
    for( int i=0; i < argc; i++){

        printf("Arg %d: %s \n",i,argv[i]);
    }

   if(argc != 4){
    printf("Usage: %s <port>\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);
  char* server_name=argv[2];
  int port_ser=atoi(argv[3]);
  int sockfd;
  struct sockaddr_in si_me,serverAddr;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  memset(&serverAddr, '\0', sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port_ser);
  serverAddr.sin_addr.s_addr = getIP(server_name)->sin_addr.s_addr;
  int counts=0;
 

    strcpy(buffer, "Hello S-talk\n");
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("[+]Data Send: %s", buffer);
   
  

  //new code

  
  int new_soc=socket(AF_INET, SOCK_DGRAM, 0);
  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr =  htonl(INADDR_ANY);


  bind(new_soc, (struct sockaddr*)&si_me, sizeof(si_me));

  
  
  addr_size = sizeof(serverAddr);
  int count=0;


  recvfrom(new_soc, buffer, 1024, 0, (struct sockaddr*)& serverAddr, &addr_size);
  printf("[+]Data Received: %s", buffer);

  
 

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




struct sockaddr_in* getIP(char* peer_name){


  struct addrinfo* res;
  char* peeraddr;
  struct sockaddr_in* saddr;
  
  
  if (0 != getaddrinfo(peer_name, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving peer_name %s\n", peer_name);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr;
  peeraddr = inet_ntoa(saddr->sin_addr);

  printf("Address for %s is %s\n", peer_name, peeraddr);

  return saddr;

}
