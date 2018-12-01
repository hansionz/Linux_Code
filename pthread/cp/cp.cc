#include "cp.hpp"

const int num = 10;

void *consume_routine(void *arg)
{
  BlockQueue<int>* pbq = (BlockQueue<int>*)arg;
  int data;
  for(;;)
  {
    pbq -> PopData(data);
    cout << "consume done, data is " << data << endl;
    sleep(1);
  }
}
void *product_routine(void *arg)
{
  BlockQueue<int>* pbq = (BlockQueue<int>*)arg;
  srand((unsigned long)time(NULL));
  for(;;)
  {
    int data = rand() % 100 + 1;
    pbq -> PushData(data);
    cout << "product done,data is " << data << endl;
    sleep(1);
  }
}
int main()
{
  BlockQueue<int> *pbq = new BlockQueue<int>(num);
  pthread_t p,c;//product(生产者)、consume(消费者)

  pthread_create(&c, NULL, consume_routine, (void*)pbq);
  pthread_create(&p, NULL, product_routine, (void*)pbq);


  pthread_join(p, NULL);
  pthread_join(c, NULL);

  delete pbq;

  return 0;
}
