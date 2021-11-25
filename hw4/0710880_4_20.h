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
//===========================================================

//operator or not===================================
bool isOperator(int token){
    if(token=='+'-'0'||token=='-'-'0'||token=='*'-'0'||token=='/'-'0'){
        return true;
    }
    else{
        return false;
    }
}

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


//========================================================

//print queue===========================
void printQueue(QUEUE* queue){
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p = queue->front;
    while(p!=NULL){
        if(*(int*)p->dataPtr == '+'-'0') printf("+");
        else if(*(int*)p->dataPtr == '-'-'0') printf("-");
        else if(*(int*)p->dataPtr == '*'-'0') printf("*");
        else if(*(int*)p->dataPtr == '/'-'0') printf("/");
        else printf("%d",*(int*)p->dataPtr);

        if(p->next != NULL) printf(" -> ");
        p = p->next;
    }
    printf("\n");
    free(p);
}
void printQueue2(QUEUE* queue){
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p = queue->front;
    while(p!=NULL){
        if(*(int*)p->dataPtr == '+'-'0') printf("+");
        else if(*(int*)p->dataPtr == '-'-'0') printf("-");
        else if(*(int*)p->dataPtr == '*'-'0') printf("*");
        else if(*(int*)p->dataPtr == '/'-'0') printf("/");
        else
        {
            if(*(float*)p->dataPtr!=*(int*)p->dataPtr)
                printf("%f",*(float*)p->dataPtr);
            else
                 printf("%d",*(int*)p->dataPtr);
        }
        if(p->next != NULL) printf(" -> ");
        p = p->next;
    }
    printf("\n");
    free(p);
}

int calPrefix(QUEUE* queue){
    //find operator follow by two operand
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    NODE* del_1 = (NODE*)malloc(sizeof(NODE));
    NODE* del_2 = (NODE*)malloc(sizeof(NODE));
    temp = queue->front;
    int value=0;

    int operand1,operand2;
    while(queue->count>=3){
        if(isOperator(*(int*)temp->dataPtr)){

            //check if next two character are operand or not
            if(!isOperator(*(char*)temp->next->dataPtr) && !isOperator(*(char*)temp->next->next->dataPtr)){
               operand1 = (*(int*)temp->next->dataPtr);
               operand2 = (*(int*)temp->next->next->dataPtr);
               //printf("%d\t%d\n",operand1,operand2);
               if(*(int*)temp->dataPtr == '+'-'0') value = (operand1+operand2);
               else if(*(int*)temp->dataPtr == '-'-'0') value = (operand1-operand2);
               else if(*(int*)temp->dataPtr == '*'-'0') value = (operand1*operand2);
               else if(*(int*)temp->dataPtr == '/'-'0') value = (operand1/operand2);

               //dequeue replace operator with value
               *(int*)temp->dataPtr = value;
               del_1 = temp->next;
               del_2 = del_1->next;
               temp->next = temp->next->next->next;
               temp = queue->front;

               //delete node
               free(del_1);
               free(del_2);
               queue->count -= 2;
              // printQueue(queue);
            }
            else{
                temp = temp->next;
            }
        }
        else{
            temp = temp->next;
        }
    }
    return value;
}

float cal_Prefix(QUEUE* queue){
    //find operator follow by two operand
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    NODE* del_1 = (NODE*)malloc(sizeof(NODE));
    NODE* del_2 = (NODE*)malloc(sizeof(NODE));
    temp = queue->front;

    float value=0.0;

    float operand1,operand2;
    int op3,op4;
    while(queue->count>=3){
        if(isOperator(*(int*)temp->dataPtr)){

            //check if next two character are operand or not
            if(!isOperator(*(char*)temp->next->dataPtr) && !isOperator(*(char*)temp->next->next->dataPtr)){
               if((*(float*)temp->next->dataPtr)!=(*(int*)temp->next->dataPtr))
               {
                    operand1 = (*(float*)temp->next->dataPtr);
               }
               else
               {
                   op3 = (*(int*)temp->next->dataPtr);
               }
               if(*(float*)temp->next->next->dataPtr!=*(int*)temp->next->next->dataPtr)
               {
                   operand2 = (*(float*)temp->next->next->dataPtr);
               }
               else
               {
                   op4 = (*(int*)temp->next->next->dataPtr);
               }

               if(*(int*)temp->dataPtr == '+'-'0') value = (float)(operand1+operand2+8);
               else if(*(int*)temp->dataPtr == '-'-'0') value = (float)((float)operand1-(float)operand2);
               else if(*(int*)temp->dataPtr == '*'-'0') value = operand1*operand2;
               else if(*(int*)temp->dataPtr == '/'-'0') value = (float)((float)operand1/(float)operand2);


               if(value>(int)value||value<(int)value)
               {
                   *(float*)temp->dataPtr = value;
               }
               else
               {
                   *(int*)temp->dataPtr = value;
               }


               del_1 = temp->next;
               del_2 = del_1->next;
               temp->next = temp->next->next->next;
               temp = queue->front;

               //delete node
               free(del_1);
               free(del_2);
               queue->count -= 2;
               //printQueue2(queue);
            }
            else{
                temp = temp->next;
            }
        }
        else{
            temp = temp->next;
        }
    }
    return value;
}
