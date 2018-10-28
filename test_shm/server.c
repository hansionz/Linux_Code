#include "comm.h"

int main()
{
  int shmid=createShm(4096);//按照一页4kb=4096个字节开辟内存空间
  
  // 将地址空间挂接到共享内存
  char* addr=shmat(shmid,NULL,0);
  sleep(2);
  int i=0;
  while(i++<26){
    printf("client say$ %s\n",addr);
    sleep(1);
  }
  //脱离挂接
  shmdt(addr);
  sleep(2);
  //销毁共享内存
  destroyShm(shmid);
  return 0;
}
