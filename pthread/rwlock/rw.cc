#include <iostream>
#include <unistd.h>

using namespace std;

int book = 0;
pthread_rwlock_t rwlock;

//可以存在任意多个线程同时读
void *read_routine(void *arg)
{
  while(1)
  {
    pthread_rwlock_rdlock(&rwlock);
    
    cout << "my tid is:" << pthread_self() << ".read book data is:" << book << endl;

    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  }
}
//任意时刻只能有一个写者线程在写(在写的时候不能有读者读)
void *write_routine(void *arg)
{
  while(1)
  {
    pthread_rwlock_wrlock(&rwlock);

    ++book;
    cout << "my tid is:"<< pthread_self() << ".write book data is:" << book << endl;
    
    pthread_rwlock_unlock(&rwlock);
    sleep(2);
  }
}
int main()
{
  //初始化读写锁变量
  pthread_rwlock_init(&rwlock, NULL);

  pthread_t r1,r2,w1,w2;//创建两个读者和写者线程
  pthread_create(&r1, NULL, read_routine, NULL);
  pthread_create(&r2, NULL, read_routine, NULL);
  pthread_create(&w1, NULL, write_routine, NULL);
  pthread_create(&w2, NULL, write_routine, NULL);

  pthread_join(r1, NULL);
  pthread_join(r2, NULL);
  pthread_join(w1, NULL);
  pthread_join(w2, NULL);

  //销毁读写锁
  pthread_rwlock_destroy(&rwlock);
  return 0;
}
