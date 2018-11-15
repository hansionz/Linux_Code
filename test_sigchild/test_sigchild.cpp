#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void handler(int sign)
{
  pid_t id;
  while((id = waitpid(-1, NULL, WNOHANG)) > 0)
  {
    std::cout << "wait child success:" << id << std::endl;
  }
  std::cout << "child is quit! pid is:" << getpid() << std::endl;
}
int main()
{
  pid_t id;
  id = fork();
  if(id < 0){
    exit(1);
  }
  else if(id == 0){//child
    std::cout << "i am child, my pid is:" << getpid() << std::endl;
    sleep(3);
  }
  else{//parent
    signal(SIGCHLD, handler);
    while(1)
    {
      std::cout << "parent proc is doing thing" << std::endl;
      sleep(1);
    }
  }
  return 0;
}
