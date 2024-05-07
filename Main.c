/**********************************************************************
Program: <Ferry Loading>
Author: <Mark Daoud>
Date: <02/24/24>
Time spent: <An hour thirty>
Purpose: The purpose of this program is to be able to undersatnd how we can use a queue with a linked list to help solve
problems such as getting cars across a river in a ferry. 
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


void convert_metric(double* plmcar, int* plccar); 

int simulate_ferry_crossings(int l, int m, QUEUE lHq, QUEUE rHq);

int main(int argc, char* argv[])
{
	QUEUE rhQ;
	QUEUE lhQ;

	rhQ = queue_innit_default(); 
	lhQ = queue_innit_default(); 

	if (rhQ == NULL || lhQ == NULL) 
	{
		printf("Failed to allocate space for Queues \n");
		exit(1);
	}

	int c;
	int i;
	int l;
	int m;
	int lcar;
	int j;
	char d[6]; 
	int number_of_crossings;
	Status status; 
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
			scanf("%d ", &lcar); 

			fgets(d, sizeof(d), stdin);  

			if ((strlen(d) > 0) && (d[strlen(d) - 1] == '\n'))
			{
				d[strlen(d) - 1] = '\0';
			}

			if (strcmp(d, "right") == 0)
			{
				status = queue_insert(rhQ, lcar);
				if (status == FAILURE) 
				{
					printf("Failed to insert into Right Queue \n");
					break;
				}
			}
			else if (strcmp(d, "left") == 0)
			{
				status = queue_insert(lhQ, lcar);
				if (status == FAILURE) 
				{ 
					printf("Failed to insert into Left Queue \n");
					break;
				}
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
    int current_bank = 0; // 0 for left bank, 1 for right bank
    double ferry_length = 0.0;

    // Simulate ferry crossings
    while (!queue_is_empty(rhQ) || !queue_is_empty(lhQ)) 
	{
        int car_count = 0; 

        QUEUE chQ = (current_bank == 0) ? lhQ : rhQ; //Check which bank we are currently at 

        
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
        current_bank = 1 - current_bank; //Switch banks 
        ferry_length = 0;  //Empty the fairy by resetting its length 
    }

    return crossings; 
}
