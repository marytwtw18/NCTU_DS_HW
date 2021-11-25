#include<iostream>
#include<fstream>
using namespace std;
#include<stdbool.h>

typedef struct node
{
    int part_number;
    int quantity;
    bool collision;
    struct node *nextPtr;

}Data;

void Searching(Data* input[],int address_num,int search_num)
{
    //Data *final_dat = new Data;
    Data * temp_dat = new Data;

    for(int i=0;i<address_num;++i)
    {
        //final_dat = input[i];
        temp_dat = input[i];
        while(temp_dat->nextPtr != nullptr)
        {
            if(temp_dat->part_number == search_num)
            {
                cout << "Found part number "<<search_num
                <<" at home address "<<i<<",quantity: "<<temp_dat->quantity<<endl;
                return;
            }
            temp_dat = temp_dat->nextPtr;
        }
        if(temp_dat->part_number == search_num)
        {
            cout << "Found part number "<<search_num
            <<" at home address "<<i<<",quantity: "<<temp_dat->quantity<<endl;
            return;
        }
    }
    cout<<"Could not find part number "<< search_num << endl ;
    return;
}

void print_list(Data* input[],int address_num)
{
    Data * temp_dat = new Data;

    cout<<"Home addr\tPrime Area\tOverflow List"<<endl;

    for(int i=0;i<address_num;++i)
    {
        int repeat = 0;
        temp_dat = input[i];
        cout <<"\t"<<i<<"\t";
        while(temp_dat->nextPtr != nullptr)
        {
            if(temp_dat->part_number== -1)
            {
                cout<<" ";
            }
            else
            {
                cout<<temp_dat->part_number<<"/"<<temp_dat->quantity;
            }

            if(repeat == 0)
            {
                cout<<"\t\t ";
            }
            else if(repeat>0)
            {
                cout<<",";
            }

            repeat++;
            temp_dat = temp_dat->nextPtr;
        }
        if(temp_dat->part_number== -1)
        {
            cout<<" ";
        }
        else
        {
            cout<<temp_dat->part_number<<"/"<<temp_dat->quantity<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}

void efficiency(Data* input[],int address_num)
{
    int no_use = 0;
    int over_long,max_over_long,total_long,num;
    total_long = 0;
    num = 0;
    over_long = 0;
    max_over_long = 0;
    cout<<"Efficiency:"<<endl;
    Data * temp_dat = new Data;
    for(int i=0;i<address_num;++i)
    {
        over_long = 0;
        temp_dat = input[i];
        if(temp_dat->part_number == -1) no_use++;

        while(temp_dat->nextPtr != nullptr)
        {
            if(over_long == 0) num++;
            over_long++;
            temp_dat = temp_dat->nextPtr;
        }
        total_long += over_long;
        if(over_long > max_over_long)
        {
            max_over_long = over_long;
        }
    }

    cout<<"Percentage of Prime Area Filled:"<<(float)(address_num-no_use)/address_num*100<<"%"<<endl;
    cout<<"Average nodes in linked lists: "<<(float)total_long/num<<endl;
    cout<<"Longest linked list: "<<max_over_long<<endl;
}

int main()
{
    ifstream infile;
    infile.open("13_19_input.txt");
    int address_num = 12;

    if (!infile)
    {
        cout << "fail!\n" << endl;
        exit(1);
    }
    //read in
    Data *new_data[30];

    //after hashing
    Data *hash_data[address_num];

    //initialize
    for(int i=0;i<address_num;++i)
    {
        hash_data[i] = new Data;
        hash_data[i]->collision = 0;
        hash_data[i]->part_number = -1;
        hash_data[i]->quantity = -1;
        hash_data[i]->nextPtr = nullptr;

    }

    //the data in the file
    int part_num,quantity,i,hash_num;

    int command,search_num; //list input
    i = 0;

    while(infile>>part_num>>quantity)
    {
        //read in data in order
        new_data[i] = new Data;
        new_data[i]->part_number = part_num;
        new_data[i]->quantity = quantity;
        new_data[i]->nextPtr =nullptr;
        //modulo  hashing method
        hash_num = (new_data[i]->part_number) % address_num;

        if(!hash_data[hash_num]->collision)
        {
            hash_data[hash_num]->part_number = new_data[i]->part_number;
            hash_data[hash_num]->quantity = new_data[i]->quantity;
            hash_data[hash_num]->collision = 1;
        }
        else
        {
            hash_data[hash_num]->collision+=1;

            Data *insert_point = new Data;
            insert_point = hash_data[hash_num];
            Data *new_hashdata = new Data;
            new_hashdata->part_number = new_data[i]->part_number;
            new_hashdata->quantity = new_data[i]->quantity;
            //cout << new_data[i]->part_number  <<"\t"<< new_data[i]->quantity << endl;
            while(insert_point->nextPtr != NULL)
            {
                 insert_point = insert_point->nextPtr;
                 //cout << hash_num << "\t" << insert_point->part_number
                 //<<"\t"<<insert_point->quantity<<endl;

            }
            insert_point->nextPtr = new_hashdata;
            new_hashdata->nextPtr = nullptr;
        }
        //cout << new_data[i]->part_number  <<"\t"<< new_data[i]->quantity << endl;
        Data *insert_point = new Data;
        insert_point = hash_data[hash_num];

        while(insert_point->nextPtr != nullptr)
        {
            //cout << hash_num << "\t" << insert_point->part_number
            //<<"\t"<<insert_point->quantity<<endl;
            insert_point = insert_point->nextPtr;
        }
        //cout << hash_num << "\t" << insert_point->part_number
        //    <<"\t"<<insert_point->quantity<<endl<<endl;

        //cout <<hash_num <<"\t"<<hash_data[hash_num]->collision<<"\t"<< hash_data[hash_num]->part_number<<"\t" << hash_data[hash_num]->quantity << endl <<endl;
        ++i;
    }
    cout << "1.searching 2.Print efficiency 3.print entire content 4.Exit" << endl;
    cout << "Please input command: ";
    cin >> command;

    while(command!=4)
    {
        if(command == 1)
        {
            cout << "Searching: ";
            cin >> search_num;
            Searching(hash_data,address_num, search_num);
        }
        else if(command == 3)
        {
            print_list(hash_data,address_num);
        }
        else if(command == 2)
        {
            efficiency(hash_data,address_num);
        }

        cout << "1.searching 2.Print efficiency 3.print entire content 4.Exit" << endl;
        cout << "Please input command: ";
        cin >> command;
    }


    return 0;
}
