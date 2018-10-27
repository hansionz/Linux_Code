#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
  int fds[2];

  int ret=pipe(fds);
  if(ret!=0){
    perror("use pipe");
    exit(1);
  }
  char buf[1024];
  int s=0;
  while(s=read(0,buf,sizeof(buf)-1)){
    if(s>0){
      //写入管道
      write(fds[1],buf,s);
    }
    else{
      break;
    }
    memset(buf,'\0',sizeof(buf));
    //从管道中读取
    ret=read(fds[0],buf,100);
    if(ret<0){
      perror("use read");
      exit(1);
    }
    //从管道中读到的内容打印到显示屏
    write(1,buf,ret);
  }


  return 0;
}
