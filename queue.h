#ifndef QUEUE_H
#define QUEUE_H

#include "status.h"

typedef void* QUEUE;

QUEUE queue_innit_default(void);

Status queue_insert(QUEUE hQ, int value);

Status queue_service(QUEUE hQ);

int queue_front(QUEUE hQ, Status* pStatus); 

Boolean queue_is_empty(QUEUE hQ); 


void queue_destroy(QUEUE* phQ); 



#endif
