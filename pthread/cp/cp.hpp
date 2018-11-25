#ifndef __CP_HPP__
#define __CP_HPP__ 

#include <iostream>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

class BlockQueue{

private:
  void LockQueue()
  {
    pthread_mutex_lock(&lock);
  }
  void UnlockQueue()
  {
    pthread_mutex_unlock(&lock);
  }

  bool IsFull()
  {
    return q.size() == (unsigned int)cap ? true : false;
  }
  bool IsEmpty()
  {
    return q.size() == 0 ? true : false;
  }

  void ProductWait()
  {
    pthread_cond_wait(&p_cond, &lock);
  }
  void ConsumeWait()
  {
    pthread_cond_wait(&c_cond, &lock);
  }

  void SignalProduct()
  {
    pthread_cond_signal(&p_cond);
  }
  void SignalConsume()
  {
    pthread_cond_signal(&c_cond);
  }
  bool IsHighLine()
  {
    return q.size() > (unsigned int)high_line ? true : false;
  }
  bool IsLowLine()
  {
    return q.size() < (unsigned int)low_line ? true : false;
  }
public:
  BlockQueue(int _cap)
    :cap(_cap)
    ,high_line((_cap*2)/3)
    ,low_line((_cap*1)/3)
  {
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&p_cond, NULL);
    pthread_cond_init(&c_cond, NULL);
  }

  void PushData(int& data)
  {
    LockQueue();//互斥锁实现互斥

    while(IsFull())
    {
      ProductWait();
    }
    if(IsHighLine())
    {
      SignalConsume();//条件变量实现同步
    }
    q.push(data);

    UnlockQueue();
  }
  void PopData(int& data)//输出型参数，通过参数带回返回值
  {
     LockQueue();
     while(IsEmpty())
     {
       ConsumeWait();
     }
     if(IsLowLine())
     {
       SignalProduct();
     }
     data = q.front();
     q.pop();

     UnlockQueue();
  }
  ~BlockQueue()
  {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&p_cond);
    pthread_cond_destroy(&c_cond);
  }
private:
  queue<int> q;
  int cap;
  
  int high_line;
  int low_line;
  pthread_mutex_t lock;
  pthread_cond_t p_cond;//队空,生产者生产
  pthread_cond_t c_cond;//队满,消费者消费
};
#endif //__CP_HPP__
