#include<stdio.h>


void fib_recur(int n)
{
    int fib[n+1];
    for(int i=0;i<=n;++i)
    {
        fib[i]=0;
    }

    if(n<0)
    {
        printf("Error!!!\n");
        return;
    }
    for(int i=0;i<=n;++i)
   {
       if(i==0||i==1)
       {
           fib[i]=1;
           printf("%d\t%d\n",i,fib[i]);
       }
       else if(i>1)
       {
           fib[i]=fib[i-1]+fib[i-2];
           printf("%d\t%d\n",i,fib[i]);
       }
   }
}

int main()
{
    int n;
    printf("Enter n:");
    scanf("%d",&n);
    fib_recur(n);

    return 0;
}
