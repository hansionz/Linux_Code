#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__ 

#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>

using namespace std;

//函数指针,指向任务的处理方法
typedef int (*call)(int,int);

//封装一个任务处理类
class Task 
{
public:
  Task(int x, int y, call handler)
    :_x(x)
    ,_y(y)
    ,_z(0)
    ,_handler(handler)
  {}
  //执行处理方法，保存结果
  void Run()
  {
    _z = _handler(_x,_y);
  }
  //打印结果 for test 
  void Show()
  {
    cout << "thread:" << pthread_self() << ". Result is:" << _z << endl; 
  }

private:
  int _x;
  int _y;
  int _z;//用来保存任务处理的结果
  call _handler;
};

//线程池
class ThreadPool 
{
private:
  int thread_nums;//线程个数
  queue<Task> t_queue;//任务队列
  pthread_mutex_t lock;//互斥锁,保护临界资源
  pthread_cond_t cond;//条件变量,实现同步
  bool is_stop;//标志该线程池是否要停止

private:
 
  static void *thread_routine(void *arg)
  {
    ThreadPool* tp = (ThreadPool*)arg; 
    //分离该线程,完成任务后不用join
    pthread_detach(pthread_self());
    while(1)
    {
      //使用互斥锁保护临界资源t_queue
      tp -> LockQueue();
      //使用while进行二次判断，防止假唤醒
      while(tp -> IsEmpty())
        tp -> IdleThread();

      Task t = tp -> GetTask();
      tp -> UnlockQueue();

      t.Run();
      t.Show();
    }
  }
  //唤醒条件变量等待下的一个线程
  void NotifyOneThread()
  {
    pthread_cond_signal(&cond);
  }
  //唤醒条件变量等待下的所有线程
  void NotifyAllThread()
  {
    pthread_cond_broadcast(&cond);
  }

public:
  ThreadPool(int num)
    :thread_nums(num)
    ,is_stop(false)
  {}
  //初始化线程池
  void InitThread()
  {
    //初始化条件变量和互斥锁
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    //创建一批线程
    for(int i = 0;i < thread_nums;i++)
    {
      pthread_t tid;
      pthread_create(&tid, NULL, thread_routine, (void*)this);
    }
  }
  //使用互斥量锁住任务队列
  void LockQueue()
  {
    pthread_mutex_lock(&lock);
  }
  //解锁
  void UnlockQueue()
  {
    pthread_mutex_unlock(&lock);
  }
  //判断任务队列是否为空
  bool IsEmpty()
  {
    return t_queue.size() == 0 ? true : false;
  }
  //使得线程在条件变量下等待
  void IdleThread()
  {
    if(is_stop)
    {
      UnlockQueue();
      thread_nums--;
      pthread_exit((void*)0);
      
      cout << "thread:" << pthread_self() << "quit!" << endl;
      return;
    }
    pthread_cond_wait(&cond, &lock);
  }
  //停止线程池
  void Stop()
  {
    LockQueue();
    is_stop = true;
    UnlockQueue();
    //线程的熟练如果大于0说明还存在线程在阻塞唤醒所有线程并停止
    if(thread_nums > 0)
    {
      NotifyAllThread();
    }
  }
  //向任务队列中添加任务
  void AddTask(Task& t)
  {
    LockQueue();
    if(is_stop)
    {
      UnlockQueue();
      return;//本线程退出
    }
    t_queue.push(t);
    NotifyOneThread();//实现同步
    UnlockQueue();
  }
  //从任务队列中拿出一个任务
  Task GetTask()
  {
    Task t = t_queue.front();
    t_queue.pop();
    return t;
  }
  //销毁条件变量和互斥量
  ~ThreadPool()
  {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
  }
};

#endif //__T__THREAD_POOL_H__
