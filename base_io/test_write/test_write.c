#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
  int fd=open("myfile",O_WRONLY|O_CREAT,0664);
  if(fd<=0){
    perror("use open");
    exit(1);
  }

  const char* msg="hello,xikeda\n";
  int count=5;
  while(count--){
    write(fd,msg,strlen(msg));
  }
  close(fd);
  return 0;
}
