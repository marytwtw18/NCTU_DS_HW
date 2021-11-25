#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define ROW 10
#define COL 12

//可以變成.h檔
//Stack ADT definition
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

typedef struct
{
    int row;
    int col;
}position;

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

void* stackTop(STACK* stack)
{
    if(stack->count == 0)
        return NULL;
    else
        return stack->top->dataPtr;
}  //stackTop

bool emptyStack(STACK* stack)
{
    return (stack->count == 0);
}

bool fullStack(STACK* stack)
{
    //local definition
    STACK_NODE* temp;

    //statememt
    if((temp=(STACK_NODE*)malloc(sizeof(*(stack->top)))))
    {
       free(temp);
       return false;
    }
    //malloc failed
    return true;
    //fullStack
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

void print(STACK* stack,int un,position goal)
{
    STACK_NODE* temp = stack->top;
    while(temp!=NULL)
    {
        printf("(%d,%d)\n",((position*)temp->dataPtr)->row,((position*)temp->dataPtr)->col);
        temp = temp->link;
    }
    if(un==1) printf("unable to reach\n");
    else  printf("(%d,%d)\n",goal.row,goal.col);
}

STACK* reverse(STACK* stack)
{
    STACK* rev;
    rev = createStack();
    STACK_NODE* temp = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    while(temp = popStack(stack))
    {
        pushStack(rev,temp);
    }
    return rev;
}

void show_map(int map[][COL])
{
    for(int i=0;i<ROW;++i)
    {
        for(int j=0;j<COL;++j)
        {
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}


int main()
{
      int pos[10][12] = {{1,1,1,1,1,1,1,1,1,1,1,1},
                       {1,0,0,0,1,1,0,1,0,1,0,1},
                       {1,1,1,0,1,0,0,0,0,0,0,1},
                       {1,1,0,0,0,0,1,1,1,1,0,1},
                       {1,1,0,1,1,1,1,1,1,1,0,0},
                       {1,1,0,1,0,1,1,1,1,1,1,1},
                       {1,1,0,0,0,1,1,1,1,1,1,1},
                       {1,1,1,1,0,1,1,1,0,1,0,1},
                       {1,1,0,0,0,0,0,1,0,0,0,1},
                       {1,1,1,1,1,1,1,1,1,1,1,1},
    };

    STACK *stack;

    stack = createStack();

    show_map(pos);


    position *inpos,*current_pos,*add_pos;
    inpos = (position*) malloc(sizeof(position));

    position goal =
    {
        goal.row = 4,
        goal.col = 11
    };

    int unable = 0;


    do
    {
        printf("please enter entrance spot:");
        scanf("%d %d",&(inpos->row),&(inpos->col));
    }while(pos[inpos->row][inpos->col]==1 || inpos->row>ROW || inpos->row<0 || inpos->col<0 || inpos->col>COL);

    current_pos = (position *) malloc(sizeof(position));
    current_pos->row = inpos->row;
    current_pos->col = inpos->col;
    pos[inpos->row][inpos->col] = 2;
    pushStack(stack,inpos);
    printf("(%d,%d)\n",current_pos->row,current_pos ->col);

    //四個方向都要判斷
    while(current_pos->col!=goal.col || current_pos->row!=goal.row)
    {

        //開始走迷宮
        //y--

        if(pos[current_pos->row][current_pos->col-1]==0)
        {
            --(current_pos->col);
            add_pos = (position*)malloc(sizeof(position));
            add_pos->row = current_pos->row;
            add_pos->col = current_pos ->col;
            printf("(%d,%d)\n",add_pos->row,add_pos->col);
            pushStack(stack,add_pos);
            pos[current_pos->row][current_pos->col] = 2;//表示走過了
        }

        //y++ direction
        else if(pos[current_pos->row][current_pos->col+1]==0)
        {
            add_pos = (position*)malloc(sizeof(position));
            ++(current_pos->col);
            add_pos->row = current_pos->row;
            add_pos->col = current_pos ->col;
            printf("(%d,%d)\n",add_pos->row,add_pos->col);
            pushStack(stack,add_pos);
            pos[current_pos->row][current_pos->col] = 2;//表示走過了
        }
        else if(pos[current_pos->row+1][current_pos->col]==0)
        {
             add_pos = (position*)malloc(sizeof(position));
            ++(current_pos->row);
            add_pos->row = current_pos->row;
            add_pos->col = current_pos ->col;
            printf("(%d,%d)\n",add_pos->row,add_pos->col);
            pushStack(stack,add_pos);
            pos[current_pos->row][current_pos->col] = 2;//表示走過了
        }

        else if(pos[current_pos->row-1][current_pos->col]==0)
        {
             add_pos = (position*)malloc(sizeof(position));
            --(current_pos->row);
            add_pos->row = current_pos->row;
            add_pos->col = current_pos ->col;
            printf("(%d,%d)\n",add_pos->row,add_pos->col);
            pushStack(stack,add_pos);
            pos[current_pos->row][current_pos->col] = 2;//表示走過了
        }
        //走投無路時
        else if(current_pos->row==inpos->row&&current_pos->col==inpos->col)
        {
            printf("unable to reach\n");
            unable = 1;
            break;
        }

        else
        {
            //add_pos = (position*)malloc(sizeof(position));
            add_pos = (position*)popStack(stack);
            free(add_pos);
            current_pos->row = ((position*)stackTop(stack))->row;
            current_pos->col = ((position*)stackTop(stack))->col;
            printf("(%d,%d)\n",current_pos->row,current_pos->col);
        }


    }

     //if(unable==0) printf("(%d,%d)\n",goal.row,goal.col);
    //reverse stack,and print
    //stack = reverse(stack);
    //print(stack,unable,goal);


    return 0;
}
