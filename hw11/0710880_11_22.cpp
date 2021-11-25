#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//	Stack ADT Type Defintions
typedef struct node2
{
    void*        dataPtr;
    struct node2* link;
} STACK_NODE;

typedef struct stack_def
{
    int         count;
    STACK_NODE* top;
} STACK;

STACK* createStack (void)
{
//	Local Definitions
	STACK* stack;

//	Statements
	stack = (STACK*) malloc( sizeof (STACK));
	if (stack)
	   {
	    stack->count = 0;
	    stack->top   = NULL;
	   } // if
	return stack;
}	// createStack

/*	================= pushStack ================
	This function pushes an item onto the stack.
	   Pre     stack is a pointer to the stack
	           dataPtr pointer to data to be inserted
	   Post    Data inserted into stack
	   Return  true  if successful
	           false if underflow
*/
bool pushStack (STACK* stack, void* dataInPtr)
{
//	Local Definitions
	STACK_NODE* newPtr;

//	Statements
	newPtr = (STACK_NODE* ) malloc(sizeof( STACK_NODE));
	if (!newPtr)
	    return false;

	newPtr->dataPtr = dataInPtr;

	newPtr->link    = stack->top;
	stack->top      = newPtr;

	(stack->count)++;
	return true;
}	// pushStack

/*	=================== popStack ==================
	This function pops item on the top of the stack.
	   Pre  stack is pointer to a stack
	   Post Returns pointer to user data if successful
	                NULL if underflow
*/
void* popStack (STACK* stack)
{
//	Local Definitions
	void*       dataOutPtr;
	STACK_NODE* temp;

//	Statements
	if (stack->count == 0)
	    dataOutPtr = NULL;
	else
	   {
	    temp       = stack->top;
	    dataOutPtr = stack->top->dataPtr;
	    stack->top = stack->top->link;
	    free (temp);
	    (stack->count)--;
	   } // else
	return dataOutPtr;
}	// popStack

bool emptyStack (STACK* stack)
{
//	Statements
	return (stack->count == 0);
}	// emptyStack
STACK* destroyStack (STACK* stack)
{
//	Local Definitions
	STACK_NODE* temp;

//	Statements
	if (stack)
	   {
	    // Delete all nodes in stack
	    while (stack->top != NULL)
	       {
	        // Delete data entry
	        free (stack->top->dataPtr);

	        temp = stack->top;
	        stack->top = stack->top->link;
	        free (temp);
	       } // while

	    // Stack now empty. Destroy stack head node.
	    free (stack);
	   } // if stack
	return NULL;
}	// destroyStack


typedef struct
{
    int            count;
    struct vertex* first;
    int (*compare) (void* argu1, void* argu2);
} GRAPH;

typedef struct vertex
{
	 struct vertex*  last;
	 int  pathway;
	 bool            inTree;
	 struct vertex*  pNextVertex;
	 void*           dataPtr;
	 int             inDegree;
	 int             outDegree;
	 short           processed;
	 struct arc*     pArc;
} VERTEX;

typedef struct arc
{
	 bool inTree;
	 int  weight;
	 struct vertex*  destination;
	 struct arc*     pNextArc;
} ARC;

GRAPH* graphCreate (int  (*compare) (void* argu1, void* argu2))
{
    GRAPH * new_graph = new GRAPH;
    new_graph->compare=compare;
    new_graph->count=0;
    new_graph->first=NULL;
    return new_graph;
}

void graphInsVrtx (GRAPH* graph, void* dataInPtr)
{
//	Local Definitions
	VERTEX* newPtr;
	VERTEX* locPtr;
	VERTEX* predPtr;

//	Statements
	newPtr = new VERTEX;
	if (newPtr)
	   {
	    newPtr->pNextVertex  = NULL;
	    newPtr->dataPtr      = dataInPtr;
	    newPtr->inDegree     = 0;
	    newPtr->outDegree    = 0;
	    newPtr->processed    = 0;
	    newPtr->pArc         = NULL;
	    (graph->count)++;
	   } // if malloc
	 else
	   {
	    printf("Overflow error 100\a\n");
	    exit (100);
	   }
	// Now find insertion point
	locPtr = graph->first;
	if (!locPtr)
	    // Empty graph. Insert at beginning
	    graph->first = newPtr;
	else
	   {
	    predPtr = NULL;
	    while (locPtr && (graph->compare
	                     (dataInPtr, locPtr->dataPtr) > 0))
	       {
	        predPtr = locPtr;
	        locPtr  = locPtr->pNextVertex;
	       } // while
	    if (!predPtr)
	        // Insert before first vertex
	        graph->first = newPtr;
	    else
	        predPtr->pNextVertex = newPtr;
	    newPtr->pNextVertex = locPtr;
	   } // else
	return;
}  // graphInsVrtx

 int graphDltVrtx (GRAPH* graph, void* dltKey)
{
//	Local Definitions
	VERTEX* predPtr;
	VERTEX* walkPtr;

//	Statements
	if (!graph->first)
	    return -2;

	// Locate vertex to be deleted
	predPtr = NULL;
	walkPtr = graph->first;
	while (walkPtr
	       && (graph->compare(dltKey, walkPtr->dataPtr) > 0))
	   {
	    predPtr = walkPtr;
	    walkPtr = walkPtr->pNextVertex;
	   } // walkPtr &&
	if (!walkPtr
	  || graph->compare(dltKey, walkPtr->dataPtr) != 0)
	   return -2;

	// Found vertex. Test degree
	if ((walkPtr->inDegree > 0) || (walkPtr->outDegree > 0))
	    return -1;

	// OK to delete
	if (!predPtr)
	    graph->first         = walkPtr->pNextVertex;
	else
	    predPtr->pNextVertex = walkPtr->pNextVertex;
	--graph->count;
	free(walkPtr);
	return 1;
}  // graphDltVrtx

int graphInsArc (GRAPH* graph, void* pFromKey, void* pToKey,int dis)
{
//	Local Definitions
	ARC*    newPtr;
	ARC*    arcPredPtr;
	ARC*    arcWalkPtr;
	VERTEX* vertFromPtr;
	VERTEX* vertToPtr;

//	Statements
	newPtr = (ARC*)malloc(sizeof(ARC));
	newPtr->weight = dis;
	if (!newPtr)
	   return (-1);

	// Locate source vertex
	vertFromPtr = graph->first;
	while (vertFromPtr && (graph->compare(pFromKey,
	                       vertFromPtr->dataPtr) > 0))
	   {
	    vertFromPtr = vertFromPtr->pNextVertex;
	   } // while vertFromPtr &&
	if (!vertFromPtr || (graph->compare(pFromKey,
	                     vertFromPtr->dataPtr) != 0))
	   return (-2);

	// Now locate to vertex
	vertToPtr   = graph->first;
	while (vertToPtr
	       && graph->compare(pToKey, vertToPtr->dataPtr) > 0)
	   {
	    vertToPtr   = vertToPtr->pNextVertex;
	   } // while vertToPtr &&
	if (!vertToPtr
	|| (graph->compare(pToKey, vertToPtr->dataPtr) != 0))
	   return (-3);

	// From and to vertices located. Insert new arc
	++vertFromPtr->outDegree;
	++vertToPtr  ->inDegree;
	newPtr->destination = vertToPtr;
	if (!vertFromPtr->pArc)
	   {
	    // Inserting first arc for this vertex
	    vertFromPtr->pArc = newPtr;
	    newPtr-> pNextArc = NULL;
	    return 1;
	   } // if new arc

	// Find insertion point in adjacency (arc) list
	arcPredPtr = NULL;
	arcWalkPtr = vertFromPtr->pArc;
	while (arcWalkPtr
	       && graph->compare(pToKey,
	                 arcWalkPtr->destination->dataPtr) >= 0)
	   {
	    arcPredPtr = arcWalkPtr;
	    arcWalkPtr = arcWalkPtr->pNextArc;
	   } // arcWalkPtr &&

	if (!arcPredPtr)
	    // Insertion before first arc
	    vertFromPtr->pArc    = newPtr;
	else
	    arcPredPtr->pNextArc = newPtr;
	newPtr->pNextArc = arcWalkPtr;
    return 1;
}	// graphInsArc
int graphDltArc (GRAPH* graph,
                 void* fromKey, void* toKey)
{
//	Local Definitions
	VERTEX* fromVertexPtr;
	VERTEX* toVertexPtr;
	ARC*    preArcPtr;
	ARC*    arcWalkPtr;

//	Statements
	if (!graph->first)
	    return -2;

	// Locate source vertex
	fromVertexPtr = graph->first;
	while (fromVertexPtr && (graph->compare(fromKey,
	                         fromVertexPtr->dataPtr) > 0))
	    fromVertexPtr = fromVertexPtr->pNextVertex;

	if (!fromVertexPtr || graph->compare(fromKey,
	                          fromVertexPtr->dataPtr) != 0)
	   return -2;

	// Locate destination vertex in adjacency list
	if (!fromVertexPtr->pArc)
	    return -3;

	preArcPtr = NULL;
	arcWalkPtr = fromVertexPtr->pArc;
	while (arcWalkPtr && (graph->compare(toKey,
	               arcWalkPtr->destination->dataPtr) > 0))
	   {
	    preArcPtr  = arcWalkPtr;
	    arcWalkPtr = arcWalkPtr->pNextArc;
	   } // while arcWalkPtr &&
	if (!arcWalkPtr || (graph->compare(toKey,
	               arcWalkPtr->destination->dataPtr) != 0))
	    return -3;
	toVertexPtr = arcWalkPtr->destination;

	// from, toVertex & arcPtr located. Delete arc
	--fromVertexPtr->outDegree;
	--toVertexPtr -> inDegree;
	if (!preArcPtr)
	    // Deleting first arc
	    fromVertexPtr->pArc  = arcWalkPtr->pNextArc;
	else
	    preArcPtr->pNextArc = arcWalkPtr->pNextArc;
	free (arcWalkPtr);
	return 1;
}  // graphDltArc

void* graphDpthFrst (GRAPH* graph,void *num_to_find)
{
 // Local Definitions
	bool    success;
	VERTEX* walkPtr;
	VERTEX* vertexPtr;
	VERTEX* vertToPtr;
	STACK * stack;
	ARC*    arcWalkPtr;

// Statements
	if (!graph->first)
	    return NULL;

	// Set processed flags to not processed
	walkPtr = graph->first;
	while (walkPtr)
	   {
	    walkPtr->processed = 0;
	    walkPtr            = walkPtr->pNextVertex;
	   } // while

	// Process each vertex in list
	stack = createStack ();
	walkPtr = graph->first;
	while (walkPtr)
	  {
	   if (walkPtr->processed < 2)
	     {
	      if (walkPtr->processed < 1)
	        {
	         // Push & set flag to pushed
	         success = pushStack (stack, walkPtr);
	         if (!success)
	             printf("\aStack overflow 100\a\n"),
	                   exit (100);
	         walkPtr->processed = 1;
	        } // if processed < 1
	     } // if processed < 2
	   // Process descendents of vertex at stack top
	   while (!emptyStack (stack))
	     {
	      vertexPtr = (VERTEX*)popStack(stack);
	      //process (vertexPtr->dataPtr);
          if(*(int*)(vertexPtr->dataPtr) == *(int *)num_to_find)
          {
              //cout<<"re,don't need to add again\n";

              return vertexPtr->dataPtr;
          }
	      vertexPtr->processed = 2;

	      // Push all vertices from adjacency list
	      arcWalkPtr = vertexPtr->pArc;
	      while (arcWalkPtr)
	        {
	         vertToPtr = arcWalkPtr->destination;
	         if (vertToPtr->processed == 0)
	           {
	            success = pushStack(stack, vertToPtr);
	            if (!success)
	              printf("\aStack overflow 101\a\n"),
	                  exit (101);
	            vertToPtr->processed = 1;
	           } // if vertToPtr
	         arcWalkPtr = arcWalkPtr->pNextArc;
	        } // while pWalkArc

	     } // while !emptyStack
	   walkPtr = walkPtr->pNextVertex;
	  } // while walkPtr
	destroyStack(stack);
	return NULL;
} // graphDpthFrst



int compareint(void* num1,void* num2)
{
    int key1;
    int key2;
    key1 = *(int*)num1;
    key2 = *(int*)num2;
    if(key1<key2)
        return -1;
    if(key1==key2)
        return 0;
    return +1;
}

void min_spanning_Tree(GRAPH*  spantree)
{
    VERTEX* ver =  spantree->first;
    while(ver)
    {
        ver->inTree = 0;
        ARC *arc = ver->pArc;
        while(arc)
        {
            arc->inTree = 0;
            arc = arc->pNextArc;
        }
        ver = ver->pNextVertex;
    }
    ver = spantree->first;
    ver->inTree=1;
    bool tree_complete = 0;
    while(!tree_complete)
    {
        tree_complete =1;
        int min_edge = 10000;
        ARC* min_edge_loc = NULL;
        ver = spantree->first;
        while(ver)
        {
            if(ver->inTree && ver->outDegree > 0)
            {
                ARC* arc = ver->pArc;
                while(arc)
                {
                    if(!arc->destination->inTree)
                    {
                        tree_complete = 0;
                        if(arc->weight<min_edge)
                        {
                            min_edge = arc->weight;
                            min_edge_loc = arc;
                        }
                    }
                    arc = arc->pNextArc;
                }
            }
            ver = ver->pNextVertex;
        }
        if(min_edge_loc != NULL)
        {
            min_edge_loc->inTree = 1;
            min_edge_loc->destination->inTree = 1;
        }
    }

}

int main()
{
    ifstream infile;
    string input_file;
    getline(cin,input_file);
    infile.open(input_file);

    if (!infile)
    {
        cout << "fail!\n" << endl;
        exit(1);
    }
    GRAPH *graph1;
    graph1 = graphCreate(compareint);

    int ver1_int,ver2_int,dis_int;
    while(infile>>ver1_int>>ver2_int>>dis_int)
    {
        int *ver1 = new int;
        int *ver2 = new int;
        int *dis = new int;
        *ver1 = ver1_int;
        *ver2 = ver2_int;
        *dis = dis_int;
        //cout<<*ver1<<" "<<*ver2<<" "<<*dis<<endl;

        //determine four case for insert(00,01,10,11)
        if(graphDpthFrst(graph1,ver1)==NULL)
        {
            graphInsVrtx(graph1,ver1);
            if(graphDpthFrst(graph1,ver2)==NULL)
            {
                 graphInsVrtx(graph1,ver2);
                 graphInsArc(graph1,ver1,ver2,*dis);
                 graphInsArc(graph1,ver2,ver1,*dis);
            }
            else
            {
                 graphInsArc(graph1,ver1,graphDpthFrst(graph1,ver2),*dis);
                 graphInsArc(graph1,graphDpthFrst(graph1,ver2),ver1,*dis);
                 //cout<<*(int*)graphDpthFrst(graph1,ver2)<<endl;
            }
        }
        else
        {
            if(graphDpthFrst(graph1,ver2)==NULL)
            {
                 graphInsVrtx(graph1,ver2);
                 graphInsArc(graph1,graphDpthFrst(graph1,ver1),ver2,*dis);
                 graphInsArc(graph1,ver2,graphDpthFrst(graph1,ver1),*dis);
                 //cout<<*(int*)graphDpthFrst(graph1,ver1)<<endl;
            }
            else
            {
                 graphInsArc(graph1,graphDpthFrst(graph1,ver1),graphDpthFrst(graph1,ver2),*dis);
                 graphInsArc(graph1,graphDpthFrst(graph1,ver2),graphDpthFrst(graph1,ver1),*dis);
                 //cout<<*(int*)graphDpthFrst(graph1,ver1)<<" "<<*(int*)graphDpthFrst(graph1,ver2)<<endl;
            }
        }
    }
    //after building graph,build spanning tree
    int min_dis = 0;
    //spanningTree(graph1);
    min_spanning_Tree(graph1);

    VERTEX * adjacency=graph1->first;
	while(adjacency) {
	    //printf("%c-",*(char*)adjacency->dataPtr);
	    ARC * adj=adjacency->pArc;
	    while(adj){
	    	if(adj->inTree)
            {
                min_dis+=adj->weight;
            }
	    	adj=adj->pNextArc;
	    }
	    adjacency=adjacency->pNextVertex;
	}

	cout<<min_dis<<endl;
	infile.close();

    return 0;
}
