#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct node{
    void* dataPtr;
    struct node* next;
}NODE;

typedef struct{ //queue head
    int count;
    NODE* front;
    NODE* rear;
}QUEUE;

//create queue head==============================================
QUEUE* createQueue(){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    if(q){
        q->count = 0;
        q->front = NULL;
        q->rear = NULL;
    }
    return q;
}

QUEUE* destroyQueue (QUEUE* queue)
{
//	Local Definitions
	NODE* deletePtr;

//	Statements
	if (queue)
	   {
	    while (queue->front != NULL)
	       {
	        free (queue->front->dataPtr);
	        deletePtr    = queue->front;
	        queue->front = queue->front->next;
	        free (deletePtr);
	       } // while
	    free (queue);
	   } // if
	return NULL;
}	// destroyQueue

//enqueue==============================================
void enqueue(QUEUE* queue,void* dataInPtr){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->dataPtr = dataInPtr;
    newNode->next = NULL;
    if(queue->count == 0){
        queue->front = newNode;
        queue->rear = newNode;
    }
    else{
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->count++;
}

int queueCount(QUEUE* queue)
{
//	Statements
	return queue->count;
}	// queueCount


bool dequeue (QUEUE* queue, void** itemPtr)
{
//	Local Definitions
	NODE* deleteLoc;

//	Statements
	if (!queue->count)
	    return false;

	*itemPtr  = queue->front->dataPtr;
	deleteLoc = queue->front;
	if (queue->count == 1)
	   // Deleting only item in queue
	   queue->rear  = queue->front = NULL;
	else
	   queue->front = queue->front->next;
	(queue->count)--;
	free (deleteLoc);

	return true;
}	// dequeue


bool emptyQueue (QUEUE* queue)
{
//	Statements
	return (queue->count == 0);
}	// emptyQueue


float cal_prefix(QUEUE* queue,char op)
{
	float num1, num2;
	char* dataPtr;

	if(op == '+')
	{
		dequeue(queue, &dataPtr);

		num1 =  cal_prefix(queue, *dataPtr);

		dequeue(queue, &dataPtr);

		num2 =  cal_prefix(queue, *dataPtr);

		return num1 + num2;
	}
	else if(op == '-')
	{
		dequeue(queue, &dataPtr);

		num1 =  cal_prefix(queue, *dataPtr);

		dequeue(queue, &dataPtr);

		num2 =  cal_prefix(queue, *dataPtr);

		return num1 - num2;
	}
	else if(op == '*')
	{

		dequeue(queue, &dataPtr);

		num1 =  cal_prefix(queue, *dataPtr);

		dequeue(queue, &dataPtr);

		num2 =  cal_prefix(queue, *dataPtr);

		return num1 * num2;
	}
	else if(op == '/')
	{

		dequeue(queue, &dataPtr);

		num1 =  cal_prefix(queue, *dataPtr);

		dequeue(queue, &dataPtr);

		num2 =  cal_prefix(queue, *dataPtr);

		return num1 / num2;
	}
	else
	{
		return  (float)op - 48;
	}
}
