#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node
{
    void*   dataPtr;
    struct  node* link;
} STACK_NODE;

typedef struct
{
    int count;
    STACK_NODE* top;
} STACK;

STACK* createStack(void)
{
    //local definitions
    STACK* stack;

    //statements
    stack = (STACK*) malloc( sizeof(STACK));
    if(stack)
        {
        stack->count = 0;
        stack->top = NULL;
        }
    return stack;
}

bool pushStack(STACK* stack,void* dataInPtr)
{
    //local definition
    STACK_NODE* newPtr;

    //statements
    newPtr = (STACK_NODE*) malloc(sizeof(STACK_NODE ));
    if(!newPtr)
        return false;

    newPtr->dataPtr = dataInPtr;

    newPtr->link = stack->top;
    stack->top = newPtr;

    (stack->count)++;
    return true;
} //pushStack

void* popStack(STACK* stack)
{
    void* dataOutPtr;
    STACK_NODE* temp;

    //statements
    if(stack->count == 0)
        dataOutPtr = NULL;
    else
    {
        temp = stack->top;
        dataOutPtr = stack->top->dataPtr;
        stack->top = stack->top->link;
        free(temp);
        (stack->count)--;
    }
    return dataOutPtr;
}


bool emptyStack(STACK* stack)
{
    return (stack->count == 0);
}


int stackCount (STACK* stack)
{
    return stack->count;
}

STACK* destroyStack (STACK* stack)
{
    //local definition
    STACK_NODE* temp;

    //statements
    if(stack)
    {
        //delete all nodes in stack
        //先delete data,不然會出錯
        while(stack->top != NULL)
        {
            //delete all entry
            free(stack->top->dataPtr);

            temp = stack->top;
            stack->top = stack->top->link;
            free(temp);
        }
        //stack empty,now delete head node
        free(stack);
    }
    return NULL;
}

const char close[] = "close 括號 missing at line:";
const char open[] = "open 括號 missing at line:";

int main()
{
    STACK *stack;
    char token;
    char* dataPtr;

    char fileid[25];
    FILE *fp;
    int count = 1;
    int error = 0;

    stack = createStack();
    printf("enter file name for parsing:");
    scanf("%s",fileid);

    fp = fopen(fileid,"r");
    if(!fp)
    {
        printf("error input");
        return 1;
    }
    while((token = fgetc(fp))!= EOF)
    {
        if(token == '\n')
            count++;
        if(token == '{')
        {
            dataPtr = (char*)malloc(sizeof(char));
            pushStack(stack,dataPtr);
        }
        else
        {
            if(token == '}')
            {
                if(emptyStack(stack))
                {
                    printf("%s %d\n",open,count);
                    error++;
                }
                else
                {
                    popStack(stack);
                }

            }
        }
    }
    if(!emptyStack(stack))
    {
        printf("%s %d\n",close,count);
        error++;
    }
    destroyStack(stack);

    if(error==0) printf("valid\n");

    fclose(fp);
    return 0;
}
