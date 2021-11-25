//大數運算
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    void* dataPtr;
    struct node* next;
}NODE;

typedef struct
{
    NODE* head;
    NODE* tail;
    int count;
}List;

typedef struct
{
    int digit;
    int carry; //相加超過10進位1,把digit-10
}Digit;

List* createlist()
{
    List* list = (List*)malloc(sizeof(List));
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

//reverse linked list
void reverse(List* list)
{
    NODE* current = (NODE*)malloc(sizeof(NODE));
    NODE* pre = NULL;
    NODE* next = NULL;
    current = list->head;

    //change head and tail
    list->head = list->tail;
    list->tail = current;

    while(current!=NULL)
    {
        next = current->next;
        current->next = pre;

        //next node
        pre = current;
        current = next;
    }

}

//input tranform to linkedlist
void num_to_list(List* list,void* datain)
{
    NODE* newnode =(NODE*)malloc(sizeof(NODE));
    newnode->next =NULL;
    newnode->dataPtr = datain;

    if(list->count == 0)
    {
        list->head = newnode;
        list->tail = newnode;
    }
    else
    {
        list->tail->next = newnode;
        list->tail = newnode;
    }
    list->count++;
}

//print linked list
void printlist(List* list)
{
    NODE* temp;
    temp = (NODE*)malloc(sizeof(NODE));
    reverse(list);  //print 前先 transform
    temp = list->head;

    while(temp!=NULL)
    {
        printf("%d",((Digit*)temp->dataPtr)->digit);
        temp = temp->next;
    }
    reverse(list);
    printf("\n");
}


//reverse char
void reverse_char(char str[])
{
    int i=0,j=0;
    char c;

    for(i=0,j=strlen(str)-1;i<j;++i,--j)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

//calculate func
List* cal_bignum(List* list1,List* list2)
{
    List* result = (List*)malloc(sizeof(List));
    result = createlist();

    NODE* head1 = (NODE*) malloc(sizeof(NODE));
    NODE* head2 = (NODE*) malloc(sizeof(NODE));
    head1 = list1->head;
    head2 = list2->head;

    //計算兩數都還有直的情況
    int carry = 0;
    while(head1!=NULL && head2!=NULL)
    {
        Digit* newdigit = (Digit*)malloc(sizeof(Digit));
        newdigit->digit = (((Digit*)head1->dataPtr)->digit+ ((Digit*)head2->dataPtr)->digit+carry)%10;
        carry = (((Digit*)head1->dataPtr)->digit+ ((Digit*)head2->dataPtr)->digit+carry)/10;
        num_to_list(result,newdigit);

        head1 = head1->next;
        head2 = head2->next;
        if(head1==NULL || head2==NULL) break;
    }

    while(head1!=NULL && head2==NULL)
    {
         Digit* newdigit = (Digit*)malloc(sizeof(Digit));
         newdigit->digit = ((Digit*)head1->dataPtr)->digit+carry;
         num_to_list(result,newdigit);
         head1 = head1->next;
         carry = 0;
    }

    while(head1==NULL && head2!=NULL)
    {
         Digit* newdigit = (Digit*)malloc(sizeof(Digit));
         newdigit->digit = ((Digit*)head2->dataPtr)->digit+carry;
         num_to_list(result,newdigit);
         head2 = head2->next;
         carry = 0;
    }

    //最後進位的狀況
    if(carry!=0)
    {
         Digit* newdigit = (Digit*)malloc(sizeof(Digit));
         newdigit->digit = carry;
         num_to_list(result,newdigit);
    }

    return result;
}


int main()
{
    //wrong!!!!
    //int num1,num2;
    //scanf("%d %d",&num1,&num2);

    List* list1,*list2,*result;
    list1 = createlist();
    list2 = createlist();
    result = createlist();

    //store in char
    char str1[50];
    char str2[50];

    //readin number
    scanf("%s",&str1);
    scanf("%s",&str2);

    //printf("\n%s\n%s\n\n",str1,str2);

    //由高位開始存
   // printf("%c%c%c\n",str1[0],str1[1],str1[2]);

    //reverse 後存到linked list
    reverse_char(str1);
    //printf("%c%c%c\n",str1[0],str1[1],str1[2]);

    reverse_char(str2);

    //開始存進linked list
    int i=0;
    while(str1[i]!='\0')
    {
        Digit* datain;
        datain =(Digit*)malloc(sizeof(Digit));
        datain->digit = str1[i] - 48;
        num_to_list(list1,datain);
       // printf("%d",datain->digit);
        ++i;
    }
   // printf("\n");
    i=0;
    while(str2[i]!='\0')
    {
        Digit* datain2;
        datain2 =(Digit*)malloc(sizeof(Digit));
        datain2->digit = str2[i] - 48;
        num_to_list(list2,datain2);
       // printf("%d",datain2->digit);
        ++i;
    }


    printf("\n");
    result = cal_bignum(list1,list2);
    printlist(result);

    return 0;
}
