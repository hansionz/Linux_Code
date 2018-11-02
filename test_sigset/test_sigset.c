#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void printsigset(sigset_t *set)
{
  int i=0;
  for(;i<32;i++)
  {
    if(sigismember(set,i)){//判断指定信号是否在目标集合中
      putchar('1');
    }
    else{
      putchar('0');
    }
  }
  puts("");
}
int main()
{
  sigset_t s,p;
  sigemptyset(&s);//初始化信号集
  sigaddset(&s,SIGINT);
  sigprocmask(SIG_BLOCK,&s,NULL);//设置阻塞信号集，阻塞SIGINT信号
  while(1)
  {
    sigpending(&p);//获取未决信号集
    printsigset(&p);
    sleep(1);
  }
  return 0;
}
