#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "list.h"
#include "receiver.h"

void *output(void *data);

static pthread_t threadIN;


List *list_Rx;

void Output_init(List *list)
{
 
    list_Rx = list;

    pthread_create(&threadIN, NULL, output, NULL);
}

void Output_shutdown()
{
    pthread_join(threadIN, NULL);
}


void *output(void *data)
{

    int count = 0;

    while (1)
    {
      
            char *ms = getmsglistRx();
            //printf("printer3\n");
            //printf("address = %p\n", ms);

            if(ms!=NULL){

                printf("[+]Data Received: %s\n", ms);
               
                if (strcmp("!\n",ms)==0)
                {

                    free(ms);
                    return NULL;
                }

            }

      free(ms);

    }

    return NULL;
}
