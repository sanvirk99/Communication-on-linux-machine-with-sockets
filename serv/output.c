#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "list.h"
#include "receiver.h"
#include "functions.h"

void *output(void *data);

static pthread_t threadOu;


List *list_Rx;

void Output_init(List *list)
{
 
    list_Rx = list;

    pthread_create(&threadOu, NULL, output, NULL);
}

void Output_shutdown()
{
    pthread_cancel(threadOu);
    pthread_join(threadOu, NULL);
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
                    cancel_all();
                    free(ms);
                    return NULL;
                }

            }

      free(ms);

    }

    return NULL;
}
