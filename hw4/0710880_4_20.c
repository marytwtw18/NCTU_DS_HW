#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"0710880_4_20.h"

int main()
{
    int count = 1;

    char *dataPtr;
    char token;

    FILE *fp;

    fp = fopen("4_20.txt","r");


    if(!fp)
    {
        printf("error input\n");
        exit(1);
    }

    QUEUE *q1 = createQueue();


    while((token=fgetc(fp))!='\n')
    {
        if(token!=' ')
        {
            dataPtr = (char*)malloc(sizeof(char));
            *dataPtr =token;
            enqueue(q1, dataPtr);
            //printf("%c", token);
        }
    }

    dequeue(q1,&dataPtr);
    printf("case%d: %d\n",count,(int)cal_prefix(q1 ,*dataPtr));

    count++;

    while((token=fgetc(fp))!=EOF)
    {
         if(token!=' ')
         {
            dataPtr = (char*)malloc(sizeof(char));
            *dataPtr =token;
            enqueue(q1, dataPtr);
            //printf("%c", token);
         }
    }

    dequeue(q1,&dataPtr);
    printf("case%d: %.4f\n",count,cal_prefix(q1 ,*dataPtr));

    fclose(fp);
    return 0;
}
