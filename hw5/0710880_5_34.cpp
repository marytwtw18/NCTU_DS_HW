#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<windows.h>
using namespace std;

typedef struct node
{
    int stock_code;
    string stock_name;
    double gain_or_loss;
    struct node* code_next;
    struct node* code_before;
    struct node* gain_next;
    struct node* gain_before;
}Stock_node;

typedef struct{
    int count;
    Stock_node* code_head;
    Stock_node* code_tail;
    Stock_node* gain_head;
    Stock_node* gain_tail;
}List;

List* createlist()
{
    List* list = new List;
    list->count = 0;
    list->code_head = NULL;
    list->code_tail = NULL;
    list->gain_head = NULL;
    list->gain_tail = NULL;

    return list;
}

void inlist(List* list,Stock_node* datain)
{
    Stock_node* newnode =new Stock_node;
    newnode->stock_name = datain->stock_name;
    newnode->stock_code = datain->stock_code;
    newnode->gain_or_loss = datain->gain_or_loss;
    newnode->code_before = NULL;
    newnode->code_next = NULL;
    newnode->gain_before = NULL;
    newnode ->gain_next = NULL;

    Stock_node* search_node =new Stock_node;
    Stock_node* pre_node = new Stock_node;
    search_node = list->code_head;
    pre_node = NULL;

    if(list->count == 0)
    {
        list->code_head = newnode;
        list->code_tail = newnode;
        list->gain_head = newnode;
        list->gain_tail = newnode;
        newnode->code_before = NULL;
        newnode->code_next = NULL;
        newnode->gain_before = NULL;
        newnode ->gain_next = NULL;
        //cout<<list->code_tail->stock_name<<endl;
    }
    else
    {
        //cout<<newnode->stock_name<<endl;
        while(newnode->stock_code>search_node->stock_code && search_node!=NULL)
        {
            pre_node = search_node;
            search_node = search_node->code_next;
            if(search_node==NULL) break;
            //cout<<pre_node->stock_name<<endl;
            //cout<<search_node->stock_name<<endl;
        }
        //cout<<newnode->stock_name<<endl;

        if(search_node==NULL)
        {
           // cout<<list->code_tail->stock_name<<endl;
            list->code_tail->code_next = newnode;
            newnode->code_before = list->code_tail;
            list->code_tail = newnode;
            newnode->code_next = NULL;
            //cout<<newnode->stock_name<<endl;
        }
        else if(pre_node==NULL)
        {
            newnode->code_next = list->code_head;
            list->code_head->code_before =newnode;
            list->code_head = newnode;
            newnode->code_before = NULL;
            //cout<<newnode->stock_name<<endl;
        }
        else
        {
            newnode->code_next = search_node;
            search_node->code_before = newnode;
            newnode->code_before = pre_node;
            pre_node->code_next = newnode;
            //cout<<newnode->stock_name<<endl;
        }
        //cout<<newnode->stock_name<<endl;
        //cout<<newnode->code_next->stock_name<<endl;

        search_node = list->gain_head;
        pre_node = NULL;

        while(newnode->gain_or_loss>search_node->gain_or_loss&& search_node!=NULL)
        {
            pre_node = search_node;
            search_node = search_node->gain_next;
            if(search_node==NULL) break;
        }
        if(search_node ==NULL)
        {
            list->gain_tail->gain_next = newnode;
            newnode->gain_before = list->gain_tail;
            list->gain_tail = newnode;
            newnode->gain_next = NULL;
        }
        else if(pre_node==NULL)
        {
            newnode->gain_next = list->gain_head;
            list->gain_head->gain_before =newnode;
            list->gain_head = newnode;
            newnode->gain_before = NULL;
        }
        else
        {
            newnode->gain_next = search_node;
            search_node->gain_before = newnode;
            newnode->gain_before = pre_node;
            pre_node->gain_next = newnode;
        }

    }
    list->count++;
}

void printlist(List* list,int choice)
{
    Stock_node* temp =new Stock_node;

    if(choice==1)
    {
        temp = list->code_head;

         while(temp!=NULL)
         {
            cout<<temp->stock_code<<"\t"<<temp->stock_name<<"\t";
            cout<<temp->gain_or_loss<<"\t"<<endl;
            temp = temp->code_next;
        }
    }
    else if(choice==2)
    {
         temp = list->gain_head;

         while(temp!=NULL)
         {
            cout<<temp->stock_code<<"\t"<<temp->stock_name<<"\t";
            cout<<temp->gain_or_loss<<"\t"<<endl;
            temp = temp->gain_next;
         }
    }
    else if(choice==3)
    {
        temp = list->code_tail;
        while(temp!=NULL)
        {
            cout<<temp->stock_code<<"\t"<<temp->stock_name<<"\t";
            cout<<temp->gain_or_loss<<"\t"<<endl;
            temp = temp->code_before;
        }
    }
    else if(choice==4)
    {
        temp = list->gain_tail;
        while(temp!=NULL)
        {
            cout<<temp->stock_code<<"\t"<<temp->stock_name<<"\t";
            cout<<temp->gain_or_loss<<"\t"<<endl;
            temp = temp->gain_before;
        }
    }

    delete temp;
}


string UTF8ToGB(const char* str)
{
     string result;
     WCHAR *strSrc;
     LPSTR szRes;

     //獲得臨時變數的大小
     int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
     strSrc = new WCHAR[i+1];
     MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

     //獲得臨時變數的大小
     i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
     szRes = new CHAR[i+1];
     WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

     result = szRes;
     delete []strSrc;
     delete []szRes;

     return result;
}


int main()
{
    //_stock_code name current_value  amount invert number of stock
    double current_price;
    double buytime_price;
    double amount_invested;
    int stock_num;
    char txt[100];
    int choice;

    ifstream infile;
    infile.open("0710880_5_34.txt");
    if(!infile)
    {
        cout<<"file open fail"<<endl;
    }

    List* stock_list = createlist();

    while(!infile.eof())
    {
        Stock_node* new_stock = new Stock_node;

        infile >> new_stock->stock_code;
        infile >> txt;
        infile >> current_price;
        infile >> buytime_price;
        infile >> stock_num;
        new_stock->stock_name = UTF8ToGB(txt);
        amount_invested = (double)buytime_price*stock_num;
        new_stock->gain_or_loss = (double)current_price*stock_num-amount_invested;
        inlist(stock_list,new_stock);
        //cout<<new_stock->stock_code<<"\t"<<new_stock->stock_name<<"\t";
        //cout<<new_stock->gain_or_loss<<"\t"<<endl;
    }

    cout<<"menu\n"<<"1.stock code backward(small->big)" << endl;
    cout<<"2.stock gain backward(small->big)" << endl;
    cout<<"3.stock code forward(big->small)" << endl;
    cout<<"4.stock gain forward(big->small)" << endl;
    cout<<"---------------------------------"<<endl;
    cin >> choice;

    cout<<endl;
    printlist(stock_list,choice);

    return 0;
}
