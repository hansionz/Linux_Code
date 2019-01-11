#include "tcp_socket.hpp"

#include <queue>
#include <pthread.h>

using namespace std;



class ThreadPool
{
public:
  ThreadPool(int nums)
    :_nums(nums)
  {
    pthread_cond_init(&_cond, NULL);
    pthread_mutex_init(&_mutex, NULL);
  }

  void LockQueue()
  {
    pthread_cond_lock(&_cond);
  }
  void UnlockQueue()
  {

  }
  void InitPool()
  {}
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
