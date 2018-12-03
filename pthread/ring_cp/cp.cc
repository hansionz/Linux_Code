#include "cp.hpp"

const int num = 10; 

void *consume_routine(void *prq)
{
  RingQueue<int>* q = (RingQueue<int>*)prq;
  int data;
  for(;;)
  {
    q -> PopData(data);
    cout << "consume done,data is:" << data << endl;
  }
}
void *product_routine(void *prq)
{
  RingQueue<int>* q = (RingQueue<int>*)prq;
  srand((unsigned long)time(NULL));
  for(;;)
  {
    int data = rand() % 100 + 1;
    q -> PushData(data);
    cout << "product done,data is:" << data << endl;
    sleep(1);
  }
}
int main()
{
  RingQueue<int>* prq = new RingQueue<int>(num);
  pthread_t p,c;

  pthread_create(&p, NULL, product_routine, (void*)prq);
  pthread_create(&c, NULL, consume_routine, (void*)prq);

  pthread_join(p, NULL);
  pthread_join(c, NULL);

  delete prq;
  prq = nullptr;

  return 0;
}
