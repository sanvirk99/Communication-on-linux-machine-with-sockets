#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "list.h"


void *output(void *data);

static pthread_t threadIN;

static pthread_cond_t syncAddToList;

List *list_Rx;

void Output_init(List *list)
{

    list_Rx=list;
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
    char buffer[1024];
    char *msg;
    while (1)
    {
       //////

       if(List_count(list_Rx)!=0){

        msg=List_trim(list_Rx);

       // strcpy(buffer, msg); 

        printf("test : %s\n",msg);

        //printf("[+]Data Received: %s\n", buffer);

        

        break;
       

       }
       
    }
    
    printf("exit output\n");
    free(msg);
    return NULL;
}
