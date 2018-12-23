#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t id = fork();
  if(id < 0){
    perror("use fork");
    exit(1);
  }
  else if(id == 0){//child
    while(1)
    {
      printf("child:%d is running!\n",getpid());
      sleep(1);
    }
  }
  else{//parent
    int i = 5;
    while(i)
    {
      printf("parent:%d is going done...%d\n",getppid(),i--);
      sleep(1);
    }
  }
  return 0;
}
