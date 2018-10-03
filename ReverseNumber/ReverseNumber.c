#include<stdio.h>
#include<limits.h>
#include<math.h>

int ReverseNumber(int x){
    
    int num=x;
    int n=0;
    while(num!=0){
        num/=10;
        ++n;
    }
    int i=0;
    long long result=0;
    num=x;
    for(i=n;i>0;i--){
        int m=num%10;
        num/=10;
        result+=(m*(pow(10,i-1)));
    }
    if(result>INT_MAX||result<INT_MIN);
        return 0;
    return result;
}
int main(){
    int x=0;
    scanf("%d",&x);

    printf("%d\n",ReverseNumber(x));
    return 0;
}
