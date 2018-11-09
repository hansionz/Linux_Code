#include <stdio.h>
#include <signal.h>

volatile int flag = 0;

void handler(int signo)
{
  flag = 1;
  printf("change flag to 1\n");
}

int main()
{
  struct sigaction act;
  sigisemptyset(&act.sa_mask);
  act.sa_handler = handler;
  sigaction(2,&act,NULL);
  //signal(SIGINT,handler);
  while(!flag);
  printf("proc done...\n");
  return 0;
}
