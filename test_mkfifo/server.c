#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  umask(0);
  mkfifo("mypipe",0644);
  int fd=open("mypipe",O_RDONLY);
  if(fd<0){
    perror("use open file");
    exit(1);
  }
  char buf[1024];
  while(1)
  {
    printf("please wait....\n");
    ssize_t s=read(fd,buf,sizeof(buf)-1);
    if(s>0){
      buf[s-1]=0;
      printf("client say$ %s\n",buf);
    }
    else if(s==0){
      printf("client quit me quit\n");
      exit(1);
    }
    else{
      exit(1);
    }
  }
  close(fd);
  return 0;
}
