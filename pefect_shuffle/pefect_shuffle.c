#include<stdio.h>
#include<stdlib.h>
//完美洗牌算法1---位置置换
#define N 100
//1 2 3 4 5 6 --> 4 1 5 2 6 3 
void pefect_shuffle1(int* num,int numsize){
  if(num == NULL || numsize < 0){
    return;
  }
  int n2=2*numsize,i=1;
  int tmp[N];
  for(;i<=n2;i++){
    tmp[(2*i)%(n2+1)]=num[i];
  }
  for(i=1;i<=n2;i++){
    num[i]=tmp[i];
  }
}
int main(){
  int nums[] = {-1,1,2,3,4,5,6};
  int size = (sizeof(nums)/sizeof(nums[0]))>>1;
  pefect_shuffle1(nums,size);
  //pefect_shuffle2();
  //pefect_shuffle3();
  //打印数组
  int i=1;
  for(;i<=(2*size);i++){
    printf("%d ",nums[i]);
  }
  printf("\n");
  return 0;
}
