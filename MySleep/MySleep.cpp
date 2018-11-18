#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;
// handler只需要捕捉它不需要使用它实现功能
void handler(int no)
{
  //什么也不需要做
}
int MySleep(unsigned int second)
{
  struct sigaction act,oact;
  sigset_t newmask,oldmask;
  act.sa_handler =handler;
  sigemptyset(&act.sa_mask);
  sigaction(SIGALRM,&act,&oact);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGALRM); //1.屏蔽SIGALRM信号
  sigprocmask(SIG_BLOCK, &newmask, &oldmask);

  alarm(second);

  sigdelset(&oldmask, SIGALRM);//2.解除旧的信号屏蔽字对信号SIGALRM的屏蔽

  sigsuspend(&oldmask);//3.解除对信号SIGALRM信号的屏蔽并挂起进程

  // 因为前边调用了自定义处理动作，但是如果后边再次使用alarm函数
  // 它的处理动作却是别人自定义的，所以这个调用完成之后要改归来
  sigaction(SIGALRM, &oact, NULL);
  // 在second秒内可能被提前唤醒
  int ret = alarm(0); //取消闹钟，返回值为剩余的秒数

  return ret;
}
int main()
{
  while(1)
  {
       MySleep(1);
       cout << "wake up done" << endl;
  }
  return 0;
}
