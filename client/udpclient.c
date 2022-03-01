#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


//resource https://github.com/nikhilroxtomar/UDP-Client-Server-Program-in-C.git
#include<netdb.h>

#define MSG_MAX_LEN 1024
#define PORT 22110

//https://www.binarytides.com/c-program-to-get-ip-address-from-interface-name-on-linux/
//https://github.com/unimonkiez/c-linux-example/blob/master/src/nslookup.c


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






int main(int argc,char** argv){

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
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  strcpy(buffer, "Hello Server\n");
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("[+]Data Send: %s", buffer);

  //new code

  
  int new_soc=socket(AF_INET, SOCK_DGRAM, 0);
  memset(&si_me, '\0', sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(port);
  si_me.sin_addr.s_addr =  getIP(server_name)->sin_addr.s_addr;

  bind(new_soc, (struct sockaddr*)&si_me, sizeof(si_me));

  
  addr_size = sizeof(serverAddr);
  recvfrom(new_soc, buffer, 1024, 0, (struct sockaddr*)& serverAddr, &addr_size);
  printf("[+]Data Received: %s", buffer);



}
