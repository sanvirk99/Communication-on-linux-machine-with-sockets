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


struct sockaddr_in *getIP(char *peer_name)
{

  struct addrinfo *res;
  char *peeraddr;
  struct sockaddr_in *saddr;

  if (0 != getaddrinfo(peer_name, NULL, NULL, &res))
  {
    fprintf(stderr, "Error in resolving peer_name %s\n", peer_name);
    exit(1);
  }

  saddr = (struct sockaddr_in *)res->ai_addr;
  peeraddr = inet_ntoa(saddr->sin_addr);

  printf("Address for %s is %s\n", peer_name, peeraddr);

  return saddr;
}
