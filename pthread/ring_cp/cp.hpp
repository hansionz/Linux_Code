#ifndef __CP_HPP__
#define __CP_HPP__ 

#include <iostream>
#include <queue>
#include <mutex>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

template<class T>
class RingQueue{
private:
 //等待信号量，信号量减1
 void P(sem_t& sem)
 {
   sem_wait(&sem);
 }
 //发布信号量，信号量加1
 void V(sem_t& sem)
 {
   sem_post(&sem);
 }
public:
  //构造函数，在构造中必须先将vector初始化一定长度代表空格信号量的个数
  RingQueue(int cap)
    :_cap(cap)
    ,ring(cap)
  {
    c_step = p_step = 0;
    sem_init(&blank_sem, 0, _cap);
    //数据信号量初始为0
    sem_init(&data_sem, 0, 0);
  }
  //向队列中入一个数据,要保证同步与互斥
  void PushData(const T& data)
  {
    P(blank_sem);

    ring[p_step] = data;
    p_step++;
    p_step %= _cap;

    V(data_sem);
  }
  //从循环队列出一个数据
  void PopData(int& data)
  {
    P(data_sem);

    data = ring[c_step];
    c_step++;
    c_step %= _cap;

    V(blank_sem);
  }
  ~RingQueue()
  {
    sem_destroy(&blank_sem);
    sem_destroy(&data_sem);
  }
private:
  vector<T> ring; //vector模拟实现环形队列
  int _cap; //队列的长度 

  sem_t blank_sem;
  sem_t data_sem;

  int c_step;//消费者步伐
  int p_step;//生产者步伐
};

#endif //__CP_HPP__
