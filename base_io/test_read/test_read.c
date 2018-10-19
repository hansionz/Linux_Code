#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main()
{
  int fd =open("myfile",O_RDONLY);
  if(fd<0){
    perror("use open");
    exit(1);
  }
  char buf[1024];
  const char *msg="hello\n";
  while(1){
    ssize_t s=read(fd,buf,strlen(msg));
    if(s>0){
      buf[s]=0;
      printf("%s",buf);
    }
    else{
      break;
    }
  }
  close(fd);
  return 0;
}
