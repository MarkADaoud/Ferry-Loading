#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum status { FAILURE, SUCCESS };
typedef enum status Status;


enum boolean { FALSE, TRUE };
typedef enum boolean Boolean;

typedef void* QUEUE;

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

QUEUE queue_innit_default(void);

Status queue_insert(QUEUE hQ, int value);

Status queue_service(QUEUE hQ);

int queue_front(QUEUE hQ, Status* pStatus);

Boolean queue_is_empty(QUEUE hQ);


void queue_destroy(QUEUE* phQ);


void convert_metric(double* plmcar, int* plccar);

int simulate_ferry_crossings(int l, int m, QUEUE lHq, QUEUE rHq);

int main(int argc, char* argv[])
{
	QUEUE rhQ;
	QUEUE lhQ;

	rhQ = queue_innit_default();
	lhQ = queue_innit_default();

	int c;
	int i;
	int l;
	int m;
	int lcar;
	int j;
	char d[6];
	int number_of_crossings;
	scanf("%d", &c);

	for (i = 0; i < c; i++)
	{
		scanf("%d %d", &l, &m);
		while (!(queue_is_empty(rhQ)))
		{
			queue_service(rhQ);
		}
		while (!(queue_is_empty(rhQ)))
		{
			queue_service(rhQ);
		}
		for (j = 0; j < m; j++)
		{
			scanf("%d %s", &lcar, d);
			if (strcmp(d, "right") == 0)
			{
				queue_insert(rhQ, lcar);
			}
			else if (strcmp(d, "left") == 0)
			{
				queue_insert(lhQ, lcar);
			}
		}
		number_of_crossings = simulate_ferry_crossings(l, m, lhQ, rhQ);
		printf("%d\n", number_of_crossings);
	}

	queue_destroy(&rhQ);
	queue_destroy(&lhQ);

	return 0;
}
void convert_metric(double* plmcar, int* plccar)
{
	*plmcar = (double)(*plccar) / 100.0;
}
int simulate_ferry_crossings(int l, int m, QUEUE lhQ, QUEUE rhQ)
{
	int crossings = 0;
	int current_bank = 0; 
	double ferry_length = 0.0;

	
	while (!queue_is_empty(rhQ) || !queue_is_empty(lhQ))
	{
		int car_count = 0;

		QUEUE chQ = (current_bank == 0) ? lhQ : rhQ; 


		while (!queue_is_empty(chQ) && car_count < m)
		{
			int car_length_cm = queue_front(chQ, NULL);
			double car_length_m = 0.0;
			convert_metric(&car_length_m, &car_length_cm);
			if (ferry_length + car_length_m > l || car_count >= m)
			{
				break;
			}

			ferry_length += car_length_m;
			queue_service(chQ);
			car_count++;
		}

		crossings++;
		current_bank = 1 - current_bank; 
		ferry_length = 0;  
	}

	return crossings;
}
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