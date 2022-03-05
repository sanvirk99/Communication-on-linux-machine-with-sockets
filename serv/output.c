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

    list_Rx = list;
    // accept mutex reciever
    // accept list reciever

    pthread_create(&threadIN, NULL, output, NULL);
}

void Output_shutdown()
{
    pthread_join(threadIN, NULL);
}

void *output(void *data)
{

    // char buffer[1024];
    int count = 0;
    char *msg;
    while (1)
    {
        //////

        if (List_count(list_Rx) != 0)
        {

            msg = getmsglistRx();

            // strcpy(buffer, msg);

            printf("[+]Data Received: %s\n", msg);

            // printf("[+]Data Received: %s\n", buffer);
            if (msg[0] == '!')
            {

                free(msg);
                break;
            }

            free(msg);
        }

        printf("exit output\n");

        return NULL;
    }
}
