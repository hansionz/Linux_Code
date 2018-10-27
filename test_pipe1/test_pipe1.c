#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main()
{
  int fds[2];
  //1.父进程创建匿名管道
  int ret=pipe(fds);
  if(ret<0){
    perror("use pipe");
    exit(1);
  }
  //2.fork子进程
  pid_t id=fork();
  if(id<0){
    perror("use fork");
    exit(1);
  }
  //3.子进程关闭读端，打开写端，向管道中写数据
  else if(id==0){//child
    close(fds[0]);
    write(fds[1],"hello",5);
    close(fds[1]);
    exit(0);
  }
  //4.父进程关闭写端，打开读端，从管道中读取数据
  else{//parent
    close(fds[1]);
    char buf[64]={'\0'};
    ssize_t s=read(fds[0],buf,sizeof(buf));
    if(s>0){
      printf("%s\n",buf);
    }
  }
  return 0;
}
