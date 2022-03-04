#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "list.h"

void *input(void *data);


static pthread_t threadIN;

static pthread_cond_t syncAddToList;

List *list_Tx;

void Input_init(List *list)
{
    list_Tx=list;

    //_process_data recTx;
    //accept mutex sender 
    //accept list sender

    pthread_create(&threadIN, NULL, input, NULL);
 
 
  
    
}


void Input_shutdown()
{
    pthread_join(threadIN, NULL);
}

void *input(void *data)
{

    char buffer[1024];
  
    while (1)
    {

        fgets(buffer, 1024, stdin);

      
    }

 return NULL;
  
}





