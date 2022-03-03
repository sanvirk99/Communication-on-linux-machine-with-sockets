#include "console.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


/////

//use only for output
//share mutex with recieve thread to acess the list
//share list

void *inputx(void *data);
void *outputx(void *data);

static pthread_t threadIN, threadOT,signallerThread;

static pthread_cond_t syncOKToPrint = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t syncOKToPrintMutex = PTHREAD_MUTEX_INITIALIZER;

void console_init()
{

    //_process_data recTx;

    pthread_create(&threadIN, NULL, inputx, NULL);
    pthread_create(&threadOT, NULL, outputx, NULL);
    

    
    
}

void console_wait()
{

    pthread_join(threadIN, NULL);
}

//only get messge when i press enter not when i am not typing

//dont stop mutec to get screen time let print the messafe
//come back to later
void *inputx(void *data)
{

    
  
    while (1)
    {
        // sleep(1);
        // strcpy(buffer, "Hello other main stalk here\n");
       
        // printf("enter something to send: \n");
        char buffer[1024];
            pthread_mutex_lock(&syncOKToPrintMutex);
            {

                fgets(buffer, 1024, stdin);

                pthread_cond_signal(&syncOKToPrint);
                

            }
            pthread_mutex_unlock(&syncOKToPrintMutex);

        sleep(0.5);
        // pressing on a key should ask for mutex of control over screen
        // get the input when user press enter
        // give back mutex to print to screen thread
        // sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&si_other, sizeof(si_other));
        // printf("[+]Data Send: %s\n", buffer);

        if (buffer[0] == '!')
        {

            break;
        }
    }

 return NULL;
  
}



//check if list empty

void *outputx(void *data)
{

    // char buffer[1024];
    int count=0;

    while (1)
    {

       pthread_mutex_lock(&syncOKToPrintMutex);

       {
         
             pthread_cond_wait(&syncOKToPrint,&syncOKToPrintMutex);
            while(count<5){

                printf("i\n");

                count++;

            }
           
              count=0;
             
             
        }
        pthread_mutex_unlock(&syncOKToPrintMutex);
       
    }
    return NULL;
}
