

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <netdb.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <net/if.h>


// modules
#include "functions.h"
#include "console.h"
#include "input.h"
#include "output.h"
#include "sender.h"
#include "receiver.h"
#include "list.h"

// resource https://github.com/nikhilroxtomar/UDP-Client-Server-Program-in-C.git




int main(int argc, char **argv)
{
  

    List *recive_list = List_create();
  List *sender_list = List_create();

  pthread_cond_t syncOKToPrint = PTHREAD_COND_INITIALIZER;
  pthread_mutex_t syncOKToPrintMutex = PTHREAD_MUTEX_INITIALIZER;

  Input_init(sender_list);
  Output_init(recive_list);
  Receiver_init(argc, argv, recive_list);
  Sender_init(argc, argv, sender_list);

  wait();

  Sender_shutdown();

  Input_shutdown();

  Output_shutdown();

  Receiver_shutdown();

  List_free(recive_list, (*freeLists));
  List_free(sender_list, (*freeLists));


}


 
