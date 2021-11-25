#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    void *dataPtr;  //  a void pointer points to anywhere
    struct node *nextPtr;
} NODE;

typedef struct data
{
    int id;
    float gpa;
}DATA;

NODE* createNode(void* itemPtr)
{
    NODE* nodePtr;
    nodePtr = (NODE*) malloc(sizeof(NODE));
     nodePtr->dataPtr = itemPtr;
     nodePtr->nextPtr = NULL;
     return nodePtr;
     free(nodePtr);
}

void sortlinkedlist(NODE **node1);
void display(NODE **node1);

int main()
{
    FILE *fp;
    NODE* head,*current_node;
    int temp_id;
    float temp_gpa;

    fp = fopen("input.txt","r");
    fscanf(fp,"%d",&temp_id);
    fscanf(fp,"%f",&temp_gpa);

    DATA* new_data,*show_data;

    new_data = malloc(sizeof(DATA));
    new_data->id = temp_id;
    new_data->gpa = temp_gpa;

    head = createNode(new_data);
    current_node = head;

    //first bulid the list
    for(int i=1;i<=9;++i)
    {
        fscanf(fp,"%d",&temp_id);
        fscanf(fp,"%f",&temp_gpa);

        new_data = malloc(sizeof(DATA));
        new_data->id = temp_id;
        new_data->gpa = temp_gpa;
        current_node->nextPtr =  createNode(new_data);
        current_node = current_node->nextPtr;
    }

    //display(&head);
    //sorting
    sortlinkedlist(&head);
    display(&head);

    free(new_data);
    return 0;
}

//bubble sort
void sortlinkedlist(NODE **node1)
{
    NODE *temp1=NULL,*temp2=NULL;
    DATA *tempdata1,*tempdata2,*temp;

    for(temp1=*node1;temp1!=NULL;temp1=temp1->nextPtr)
    {
        for(temp2=temp1->nextPtr;temp2!=NULL;temp2=temp2->nextPtr)
        {
            tempdata1 = (DATA*)(temp1->dataPtr);
            tempdata2 = (DATA*)(temp2->dataPtr);
            if(tempdata1->gpa<tempdata2->gpa) //switch DATA
            {
                temp = (DATA*)(temp1->dataPtr);
                temp1->dataPtr = tempdata2;
                temp2->dataPtr = temp;
            }
        }
    }
}
void display(NODE **node1)
{
	NODE *temp;
	DATA *showdata;//=malloc(sizeof(DATA));
	temp=*node1;
	int i=1;
	while(temp!=NULL)
	{
	    showdata =(DATA*)(temp->dataPtr);
		printf("student %d: id = %d,gpa = %.1f\n",i,showdata->id,showdata->gpa);
		temp=temp->nextPtr;
		++i;
	}
	printf("\n");
}
