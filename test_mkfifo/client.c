#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  int fd=open("mypipe",O_WRONLY);
  if(fd<0){
    perror("use open file");
    exit(1);
  }
  char buf[1024];
  while(1){

    printf("please Enter$ ");
    fflush(stdout);
    ssize_t s=read(0,buf,sizeof(buf)-1);
    if(s>0){
      buf[s-1]=0;
      write(fd,buf,s);
    }
    else{
      exit(1);
    }
  }
  close(fd);
  return 0;
}
