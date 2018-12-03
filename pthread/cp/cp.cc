#include "cp.hpp"

const int num = 10;

pthread_mutex_t c_lock;
pthread_mutex_t p_lock;

void *consume_routine(void *arg)
{
  BlockQueue<int>* pbq = (BlockQueue<int>*)arg;
  int data;
  for(;;)
  {
    pthread_mutex_lock(&c_lock);
    pbq -> PopData(data);
    cout << pthread_self() <<":consume done, data is " << data << endl;
    pthread_mutex_unlock(&c_lock);
    sleep(1);
  }
}
void *product_routine(void *arg)
{
  BlockQueue<int>* pbq = (BlockQueue<int>*)arg;
  srand((unsigned long)time(NULL));
  for(;;)
  {
    pthread_mutex_lock(&p_lock);
    int data = rand() % 100 + 1;
    pbq -> PushData(data);
    cout << pthread_self()<<":product done,data is " << data << endl;
    pthread_mutex_unlock(&p_lock);
    //sleep(1);
  }
}
int main()
{
  BlockQueue<int> *pbq = new BlockQueue<int>(num);
  pthread_t p1,p2,c1,c2;//product(生产者)、consume(消费者)

  pthread_mutex_init(&c_lock, NULL);
  pthread_mutex_init(&p_lock, NULL);

  pthread_create(&c1, NULL, consume_routine, (void*)pbq);
  pthread_create(&c2, NULL, consume_routine, (void*)pbq);
  pthread_create(&p1, NULL, product_routine, (void*)pbq);
  pthread_create(&p2, NULL, product_routine, (void*)pbq);


  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(c1, NULL);
  pthread_join(c2, NULL);

  pthread_mutex_destroy(&p_lock);
  pthread_mutex_destroy(&c_lock);

  delete pbq;

  return 0;
}
