#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void CountSort(int* num,int len)
{
    if(num==NULL||len<=0)
        return;

    int min=num[0],max=num[0];
    int i=0;
    for(;i<len;i++)
    {
        if(num[i]<min)
            min=num[i];
        if(num[i]>max)
            max=num[i];
    }

    int range=max-min+1;
    int* tmp=(int*)malloc(sizeof(int)*range);
    if(tmp==NULL)
    {
        perror("use malloc");
        exit(1);
    }
    memset(tmp,0,sizeof(int)*range);
    for(i=0;i<len;i++)
    {
         tmp[num[i]-min]++;
    }
    int index=0;
    for(i=0;i<range;i++)
    {
        while((tmp[i]--)!=0)
        {
            num[index]=i+min;
            index++;
        }
    }
}
int main()
{
    int num[]={5,2,4,5,7,8,5,3,2,4,6,7};
    int len=sizeof(num)/sizeof(num[0]);
    CountSort(num,len);
    int i=0;
    for(;i<len;i++){
        printf("%d ",num[i]);
    }
    printf("\n");
    return 0;
}
