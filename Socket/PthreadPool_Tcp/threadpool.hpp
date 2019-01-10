#include "tcp_socket.hpp"

class ThreadPool
{
public:
  ThreadPool(int nums)
    :_nums(nums)
  {
    pthread_cond_init(&_cond, NULL);
    pthread_mutex_init(&_mutex, NULL);
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
  pthread_cond_t _cond;
  pthread_mutex_t _mutex;
};
