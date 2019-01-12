#include "tcp_socket.hpp"

#include <queue>
#include <pthread.h>

using namespace std;

typedef void (*Handler_t)(TcpSocket);

class Task
{
public:
  Task(TcpSocket newsock, Handler_t handler = NULL)
    :_sock(newsock)
    ,_handler(handler)
  {}

  void Run()
  {
    _handler(_sock);
  }
private:
  TcpSocket _sock;
  Handler_t _handler;

};

class ThreadPool
{
public:
  ThreadPool(int nums)
    :_nums(nums)
    ,idle_nums(0)
  {
    pthread_cond_init(&_cond, NULL);
    pthread_mutex_init(&_mutex, NULL);
  }

  void LockQueue()
  {
    pthread_mutex_lock(&_mutex);
  }
  void UnlockQueue()
  {
    pthread_mutex_unlock(&_mutex);
  }

  void IdlePthread()
  {
    pthread_cond_wait(&_cond, &_mutex);
  }

  void NotiyPthread()
  {
    pthread_cond_signal(&_cond);
  }

  bool IsEmpty()
  {
    return q.size() == 0; 
  }

  Task PopTask()
  {
    Task t = q.front();
    q.pop();
    return t;
  }

  static void* ThreadRoutine(void* arg)
  {
    ThreadPool* tp = reinterpret_cast<ThreadPool*>(arg);
    pthread_detach(pthread_self());//分离线程
    while(1)
    {
      tp->LockQueue();
      while(tp->IsEmpty())//使用while轮询防止假唤醒
      {
        tp->IdlePthread();
      }
      Task t = tp->PopTask();
      tp->UnlockQueue();

      t.Run();
    }
  }
  void InitPool()
  {
    pthread_t pid;
    for(int i = 0; i < _nums; i++)
    {
      pthread_create(&pid, NULL, ThreadRoutine, this);
    }
  }
  void AddTask(const Task& t)
  {
    LockQueue();
    q.push(t);
    NotiyPthread();
    UnlockQueue();
  }
  ~ThreadPool()
  {
    pthread_cond_destroy(&_cond);
    pthread_mutex_destroy(&_mutex);
  }
private:
  TcpSocket _sock;
  int _nums;
  int idle_nums;
  queue<Task> q;
  pthread_cond_t _cond;
  pthread_mutex_t _mutex;
};
