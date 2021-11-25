#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"0710880_4_22.h"


int main()
{
    FILE *fin;
    QUEUE* queue;

    int call_num = 0; //every call++
    int arrival_time = 0;
    int wait_time = 0;
    int wait_num = 0; //等待被執行的call數
    int start_time = 0;
    int clock_time = 0;
    int *dataPtr;
    int total_idle = 120;
    int total_wait = 0;
    int total_ser = 0;
    int max_size =0;

    int call[120],ser_time[120];

    queue = createQueue();
    fin = fopen("4_22.txt","r");

    if(fin == NULL)
    {
        printf("fail to open\n");
        return -1;
    }

    for(int i=0;i<120;++i)
    {
        call[i] = 0;
        ser_time[i] = 0;
    }

    while(!feof(fin))
        //the file still have value
    {
        //將讀來的值存入array
        fscanf(fin,"%d",&call[arrival_time]);
        fscanf(fin,"%d",&ser_time[arrival_time]);

        arrival_time++;
    }

    int arrival_time2 = 0;
    for(int i=0;i<arrival_time-1;++i,arrival_time2++)
    {
        if(call[i]!=0)
        {
            ++call_num;
            start_time = arrival_time2+wait_time;
            clock_time = start_time + ser_time[i] -1;
            total_idle -= ser_time[i];
            //超過120m十
            if(start_time+ser_time[i]>120)
            {
                total_idle += start_time+ser_time[i]-120;
            }
            total_wait += wait_time;
            total_ser += ser_time[i];

            int k;
            k=arrival_time2;
            while(k!=start_time+ser_time[i])
            {
                if(call[++k]!=0)
                {
                     //wait進queue
                    dataPtr = malloc(sizeof(int));
                    *dataPtr = call[start_time];
                    enqueue(queue,dataPtr);
                }
            }

            if(queueCount(queue)> max_size)
            {
                max_size = queueCount(queue);
            }

            printf("clock time:%d,call number:%d,arrival time:%d,wait time:%d,start time:%d,service time:%d,queue size:%d\n",clock_time,call_num,arrival_time2,wait_time,start_time, ser_time[i],queueCount(queue));
        }

        //normal case
        if(!emptyQueue(queue))
        {
            dequeue(queue,dataPtr);
        }
        //special case
        if((call[i-2]!=0)&&(call[i-1]!=0)&&ser_time[i-2]==2&&ser_time[i-1]==1)
        {
            dequeue(queue,dataPtr);
        }



        wait_time += ser_time[i];

        //每過一秒的情形
        if(wait_time!=0) --wait_time;
    }

    //result
    printf("\n------------------------------------\n");
    printf("total calls:%d\n",call_num);
    printf("Total idle time:%d\n",total_idle);
    printf("Total wait time:%d\n",total_wait);
    printf("Total service time:%d\n",total_ser);
    printf("Maximun queue size:%d\n",max_size);
    printf("Average wait time:%.6f\n",(float)total_wait/call_num);
    printf("Average service time:%.6f\n",(float)total_ser/call_num);


    destroyQueue(queue);
    fclose(fin);

    return 0;
}
