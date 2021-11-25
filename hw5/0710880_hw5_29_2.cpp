#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<sstream>
using namespace std;


typedef struct
{
    int coeff;
    int exp;
}Poly;

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

List* createlist()
{
    List* list = (List*)malloc(sizeof(List));
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void inlist(List* list,void* datain)
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

void printlist(List* list)
{
    NODE* temp = (NODE*)malloc(sizeof(NODE));
    temp = list->head;

    while(temp!=NULL)
    {
        printf("%d\t%d\n",((Poly*)(temp->dataPtr))->coeff,((Poly*)(temp->dataPtr))->exp);
        temp = temp->next;
    }
    free(temp);
}

List* cal_poly(List* list1,List* list2,int choice)
{
    List* result;
    result = createlist();


    NODE* head1 = (NODE*) malloc(sizeof(NODE));
    NODE* head2 = (NODE*) malloc(sizeof(NODE));
    head1 = list1->head;
    head2 = list2->head;

    while(head1!=NULL && head2!=NULL)
    {
        if(((Poly*)(head1->dataPtr))->exp ==((Poly*)(head2->dataPtr))->exp)
        {
            Poly* datain = (Poly*)malloc(sizeof(Poly));
            datain->exp = ((Poly*)(head1->dataPtr))->exp;
            if(choice==1)
            {
                 datain->coeff = ((Poly*)(head1->dataPtr))->coeff+((Poly*)(head2->dataPtr))->coeff;
            }
            else if(choice==2)
            {
                datain->coeff = ((Poly*)(head1->dataPtr))->coeff-((Poly*)(head2->dataPtr))->coeff;
            }

            if(datain->coeff!=0) inlist(result,datain);

            head1 = head1->next;
            head2 = head2->next;
        }
        else if(((Poly*)(head1->dataPtr))->exp >((Poly*)(head2->dataPtr))->exp)
        {
            Poly* datain = (Poly*)malloc(sizeof(Poly));
            datain->exp = ((Poly*)(head1->dataPtr))->exp;
            datain->coeff = ((Poly*)(head1->dataPtr))->coeff;

            inlist(result,datain);
            head1 = head1->next;
        }
        else if(((Poly*)(head1->dataPtr))->exp <((Poly*)(head2->dataPtr))->exp)
        {
            Poly* datain = (Poly*)malloc(sizeof(Poly));
            if(choice==1)
            {
                datain->exp = ((Poly*)(head2->dataPtr))->exp;
                datain->coeff = ((Poly*)(head2->dataPtr))->coeff;
            }
            else if(choice ==2)
            {
                datain->exp = ((Poly*)(head2->dataPtr))->exp;
                datain->coeff = -((Poly*)(head2->dataPtr))->coeff;
            }

            inlist(result,datain);
            head2 = head2->next;
        }

        if(head1==NULL || head2==NULL) break;
    }

    while(head1!=NULL && head2==NULL)
    {
        Poly* datain = (Poly*)malloc(sizeof(Poly));
        datain->exp = ((Poly*)(head1->dataPtr))->exp;
        datain->coeff = ((Poly*)(head1->dataPtr))->coeff;

        inlist(result,datain);
        head1 = head1->next;
    }

    while(head1==NULL && head2!=NULL)
    {
         Poly* datain = (Poly*)malloc(sizeof(Poly));
         datain->exp = ((Poly*)(head2->dataPtr))->exp;
         datain->coeff = ((Poly*)(head2->dataPtr))->coeff;

         inlist(result,datain);
         head2 = head2->next;
    }


    free(head1);
    free(head2);
    return result;
}


vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;

	char * strs = new char[str.length() + 1] ;
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p;
		res.push_back(s);
		p = strtok(NULL, d);
	}

	return res;
}


int main()
{
    ifstream infile;
    infile.open("test.txt");
    if(!infile)
    {
        cout<<"file open fail"<<endl;
    }

    List* list1,*list2,*result;
    list1 = createlist();
    list2 = createlist();
    result = createlist();
    int countn = 0;

    string str = "polynomial 1";
    string str2 = "polynomial 2";
    string inputs;
    string coeffs,exps;

    while(!infile.eof())
    {
        while(getline(infile,inputs))
        {
           Poly* dataPtr = new Poly;
         //  cout<<inputs<<endl;
           if(inputs == "polynomial 1")
           {
               countn=1;
           }
           if(inputs == "polynomial 2")
           {
                countn=2;
           }
           else if(countn==1&&inputs != "polynomial 1")
           {
               std::vector<string> res = split(inputs, "\t");
              // cout<<res[0]<<" "<<res[1]<<endl;
               dataPtr->coeff = stoi(res[0]);
               dataPtr->exp = stoi(res[1]);
               inlist(list1,dataPtr);
           }
           else if(countn==2&&inputs != "polynomial 2")
           {
               std::vector<string> res = split(inputs, "\t");
             //  cout<<res[0]<<" "<<res[1]<<endl;
               dataPtr->coeff = stoi(res[0]);
               dataPtr->exp = stoi(res[1]);
               inlist(list2,dataPtr);
           }
        }
     }
  //  printlist(list1);
 //   printlist(list2);

    int input;

    printf("select (1) Add or (2)Subtracts:");
    scanf("%d",&input);


    //result part
    result = cal_poly(list1,list2,input);
    if(input==1) printf("Add result:\n");
    if(input==2) printf("Sub result:\n");
    printlist(result);

    return 0;
}
