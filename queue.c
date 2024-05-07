#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct node Node;
typedef struct queue Queue;


struct node 
{
	int data;
	Node* prev;
	Node* next;
};

struct queue
{
	int size;
	Node* head;
	Node* tail; 
};

QUEUE queue_innit_default(void)
{
	Queue* pQ = (Queue*)malloc(sizeof(Queue));
	if (pQ != NULL)
	{
		pQ->head = NULL;
		pQ->tail = NULL;
		pQ->size = 0;
	}
	return (QUEUE)pQ;
}
Status queue_insert(QUEUE hQ, int value) 
{
	Queue* pQ = (Queue*)hQ; 
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}
	temp->data = value;
	temp->prev = NULL;
	temp->next = NULL;
	if (pQ->tail == NULL)
	{
		pQ->head = pQ->tail = temp; 
	}
	else
	{
		pQ->tail->next = temp; 
		temp->prev = pQ->tail;
		pQ->tail = temp;
	}
	pQ->size++; 
	return SUCCESS;
}
Status queue_service(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	if (queue_is_empty(hQ))
	{
		return FAILURE;
	}
	Node* temp;
	temp = pQ->head;
	if (pQ->head == pQ->tail) 
	{
		pQ->head = pQ->tail = NULL;
	}
	else 
	{
		pQ->head = pQ->head->next; 
		pQ->head->prev = NULL; 
	}
	free(temp); 
	pQ->size--; 
	return SUCCESS; 
}
int queue_front(QUEUE hQ, Status* pStatus)
{
	Queue* pQ = (Queue*)hQ; 
	if (queue_is_empty(hQ)) 
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return -1337;
	}
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pQ->head->data; 
}
Boolean queue_is_empty(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;

	return (pQ->size <= 0) ? TRUE : FALSE; 
}

void queue_destroy(QUEUE* phQ)
{
	Queue* pQ = (Queue*)*phQ;
	Node* temp;
	while (pQ->head != NULL)
	{
		temp = pQ->head;
		pQ->head = pQ->head->next;
		free(temp);
	}
	free(pQ);
	*phQ = NULL;
}