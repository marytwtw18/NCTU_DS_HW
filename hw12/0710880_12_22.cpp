#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>

using namespace std;

void shellsort(int list1[],int last)
{
    int hold;
    int incre;
    int walker;
    int divisor = 2;
    incre = (last+1) / divisor;
    cout<<"increment = "<<(last+1)<<" / 2"<<" = "<<(int)(incre)<<endl;
    int repeat = 0;

    while(incre!=0&& repeat!=2)
    {
        for(int curr=incre;curr<=last;++curr)
        {
            hold = list1[curr];
            walker = curr - incre;

            while(walker >= 0 && hold < list1[walker])
            {
                list1[walker+incre] = list1[walker];
                walker = (walker - incre);
            }

            list1[walker + incre] = hold;
        }
        for(int i=0;i<10;++i)
        {
            //initialize
            cout<<list1[i]<<"  ";
        }
        cout<<endl;
        cout<<endl;
        divisor++;
        incre = (last+1) / divisor;
        if(incre == 1) repeat++;
        if(repeat == 2) break;
        cout<<"increment = "<<(last+1)<<" / "<<divisor<<" = "<<(int)(last+1)/divisor<<endl;

    }
    return;
}
int main()
{
    ifstream infile;
    int input[10];
    infile.open("12_22_input.txt");

    if (!infile)
    {
        cout << "fail!\n" << endl;
        exit(1);
    }

    for(int i=0;i<10;++i)
    {
        //initialize
        input[i] = 0;
    }
    int i = 0;
    while(!infile.eof())
    {
        infile>>input[i];
        //cout<<input[i]<<" ";
        i++;
    }
    //cout<<endl;
    //cout<<endl;

    shellsort(input,9);

   // cout<<endl;
    //cout<<endl;

    for(int i=0;i<10;++i)
    {
        //initialize
        //cout<<input[i]<<" ";;
    }
   // cout<<endl;

    return 0;
}
