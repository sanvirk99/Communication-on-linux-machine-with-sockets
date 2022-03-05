#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "list.h"

void Reciever_init(int argc, char** argv,List *list);
void Reciever_shutdown();
char *getmsglistRx();


#endif