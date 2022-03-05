#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "list.h"
#include "receiver.h"

void *input(void *data);

static pthread_t threadIN;

static pthread_cond_t sendSigTx = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t SendMutTx = PTHREAD_MUTEX_INITIALIZER;

List *list_Tx;

void Input_init(List *list)
{
    list_Tx = list;

    //_process_data recTx;
    // accept mutex sender
    // accept list sender

    pthread_create(&threadIN, NULL, input, NULL);
}

void Input_shutdown()
{
    pthread_join(threadIN, NULL);
}

void *input(void *data)

{
    int lenght;
    while (1)
    {
        char buffer[1024];

        fgets(buffer, 1024, stdin);

        lenght = strlen(buffer);

        char *str = (char *)malloc(lenght);
      
        strcpy(str, buffer);
        
        pthread_mutex_lock(&SendMutTx);

        {
            //printf("[+]Data Send: %s", buffer);
            if (List_prepend(list_Tx, str) != 0)
            {

                printf("adding to list error\n");
            }

            pthread_cond_signal(&sendSigTx);
        }
        pthread_mutex_unlock(&SendMutTx);

        // temp
        if (strcmp("!\n",str)==0)

        {
            
            
            
            return NULL;
            
        }
    }

    return NULL;
}


char *getInputListTx()
{

  char *input;

 

  pthread_mutex_lock(&SendMutTx);
  {
    

      if(List_count(list_Tx)==0){

        pthread_cond_wait(&sendSigTx, &SendMutTx);
      }

       
      input=List_trim(list_Tx);
      
    
  }
  pthread_mutex_unlock(&SendMutTx);
 
  return input;

}


void terminateInputListTx()
{

       char buffer[1024];

       


        char *str = (char *)malloc(10);
      
        strcpy(str, "!\n");
        

 

  pthread_mutex_lock(&SendMutTx);
  {
    
    if (List_prepend(list_Tx, str) != 0)
            {

                printf("adding to list error\n");
            }

            pthread_cond_signal(&sendSigTx);
       
     
  }
  pthread_mutex_unlock(&SendMutTx);
 
  

}



