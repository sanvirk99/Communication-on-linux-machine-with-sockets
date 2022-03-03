#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>



void *output(void *data);

static pthread_t threadIN;

static pthread_cond_t syncAddToList;

void Output_init()
{


    //accept mutex reciever
    //accept list reciever

    pthread_create(&threadIN, NULL, output, NULL);
 
 
  
    
}


void Output_shutdown()
{
    pthread_join(threadIN, NULL);
}


void *output(void *data)
{

    // char buffer[1024];
    int count=0;

    while (1)
    {
       //////
    }
    return NULL;
}
