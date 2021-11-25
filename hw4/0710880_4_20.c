#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"0710880_4_20.h"


int main()
{
    int count = 1;
    int k=0;
    char token;

    int result1;
    float result2;

    FILE *fp;
    char str[40];

    fp = fopen("4_20.txt","r");


    if(!fp)
    {
        printf("error input\n");
        return 1;
    }

     QUEUE *q1 = createQueue();
     QUEUE *q2 = createQueue();

    for(int i=0;i<2;++i)
    {
        int* dataPtr1;
        int* dataPtr2;

        while((token=fgetc(fp))!='\n')
        {

            if(token!=' ')
            {


                if(count==1)
                {
                    dataPtr1 = (NODE*)malloc(sizeof(NODE));
                    *dataPtr1 =token-'0';
                    //printf("%c ",token);
                    enqueue(q1, dataPtr1);
                }
                else if(count==2)
                {
                     dataPtr2 = (NODE*)malloc(sizeof(NODE));
                    *dataPtr2 =token-'0';
                    //printf("%c ",token);
                    enqueue(q2, dataPtr2);
                }
            }
           // if(count==2&&token==' '&&token+1==' ')  break;
        }
        //1by1 case
        if(count==1)
        {
            result1 = calPrefix(q1);
            printf("case%d: %d\n",count,result1);
        }
        else if(count==2)
        {
            result2 = cal_Prefix(q2);
            printf("case%d: %.2f\n",count,result2);
        }
        count++;

    }

    fclose(fp);
    return 0;
}
