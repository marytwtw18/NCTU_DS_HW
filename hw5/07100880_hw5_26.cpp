//done
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
using namespace std;

//score node
typedef struct node{
    void* dataPtr;
    struct node* next;
}scoreNode;

//student node
typedef struct name{
    struct name *next_name;
    void* dataPtr;
    scoreNode* head;
    scoreNode* tail;
    int count;      //count there are how many score node
}nameNode;

typedef struct{
    int count;
    nameNode* head;
    nameNode* tail;
}List;

List* genNewList(){
    List *list = new List;
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void genNewStu(List* list,void *name){
    nameNode* new_name = new nameNode;
    new_name->dataPtr = name;
    new_name->next_name = NULL;
    if(list->count == 0){
        list->head = new_name;
        list->tail = new_name;
    }
    else{
        list->tail->next_name = new_name;
        list->tail = new_name;
    }
    new_name->head = NULL;
    new_name->tail = NULL;
    new_name->count = 0;
    list->count++;
}

void enScore(List* list,void *score,int num){
    //find that person
    nameNode *per = new nameNode;
    per = list->head;
    for(int i=0;i<num;i++)
    {
        per = per->next_name;
    }
    //create new score node
    scoreNode *new_score = new scoreNode;
    new_score->dataPtr = score;
    new_score->next = NULL;
    if(per->count==0){
        per->head = new_score;
        per->tail = new_score;
    }
    else{
        per->tail->next = new_score;
        per->tail = new_score;
    }
    per->count++;
}

//================================================
//print===========================================
void printList(List* list){
    int total=0,num;
    float avg = 0.0;
    nameNode *n = new nameNode;
    scoreNode *s = new scoreNode;
    n = list->head;

    while(n!=NULL){
        cout<<setw(10)<<*(string*)n->dataPtr<<":\t";
        s = n->head;
        num = n->count;
        while(s!=NULL){
            if(s->next == NULL){
                cout<<*(int*)s->dataPtr;
                total += *(int*)s->dataPtr;
            }
            else{
                cout<<*(int*)s->dataPtr<<"->";
                total += *(int*)s->dataPtr;
            }
            s = s->next;
        }
        avg = (float)total/num;
        n = n->next_name;

        cout<<endl<<setw(10)<<"Average:";
        cout<<"\t"<<avg<<endl<<endl;
        total = 0;
        avg = 0;
    }
}

int main()
{
    ifstream infile;
    infile.open("input.txt");

    if(!infile)
    {
        cout<<"file open fail"<<endl;
    }

    List* list1;
    list1 = genNewList();
    string input;
    int stu_num = 0;
    int data;

    while(!infile.eof())
    {
        string *newname = new string;
        infile >> input;
        *newname = input;
        genNewStu(list1,newname);
        ++stu_num;
       // cout<< *newname<<endl;
    }
   // printList(list1);

    nameNode *n = new nameNode;
    n = list1->head;

    for(int i=0;i<stu_num;++i)
    {
        cout<<"Input "<<*(string *)(n->dataPtr)<<"'s scores:";

        while(1)
        {
            scanf("%d",&data);
            int* score =(int*)malloc(sizeof(int));
            *score = data;
            enScore(list1,score,i);

            if( getchar() == '\n')
            {
                break;
            }
        }
        n = n->next_name;
    }
    cout<<endl;
    printList(list1);

    return 0;
}
