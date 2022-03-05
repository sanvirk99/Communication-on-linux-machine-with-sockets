#ifndef _INPUT_H_
#define _INPUT_H_

#include "list.h"

void Input_init(List *list);
void Input_shutdown();
char* getInputListTx();
void terminateInputListTx();

#endif