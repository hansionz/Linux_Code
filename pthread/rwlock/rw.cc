#include <iostream>
#include <unistd.h>

using namespace std;

int book = 0;
pthread_rwlock_t rwlock;

void *read_routine(void *arg)
{
  while(1)
  {
    pthread_rwlock_rdlock(&rwlock);
    
    cout << "read book data is:" << book << endl;

    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  }
}

void *write_routine(void *arg)
{
  while(1)
  {
    pthread_rwlock_wrlock(&rwlock);

    ++book;
    cout << "write book data is:" << book << endl;
    
    pthread_rwlock_unlock(&rwlock);
    sleep(2);
  }
}
int main()
{
  pthread_rwlock_init(&rwlock, NULL);

  pthread_t r1,r2,w1,w2;
  pthread_create(&r1, NULL, read_routine, NULL);
  pthread_create(&r2, NULL, read_routine, NULL);
  pthread_create(&w1, NULL, write_routine, NULL);
  pthread_create(&w2, NULL, write_routine, NULL);

  pthread_join(r1, NULL);
  pthread_join(r2, NULL);
  pthread_join(w1, NULL);
  pthread_join(w2, NULL);

  pthread_rwlock_destroy(&rwlock);
  return 0;
}
