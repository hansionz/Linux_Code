#include <iostream>
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <pthread.h>

using namespace std;

void* Routine1(void* arg)
{
  struct sockaddr_in* ptr = (struct sockaddr_in*)arg;
  while(1)
  {
    sleep(1);
    char* p = inet_ntoa(ptr->sin_addr);
    cout << "pthread 1:" << p << endl;
  }
  return NULL;
}
void* Routine2(void* arg)
{

  struct sockaddr_in* ptr = (struct sockaddr_in*)arg;
  while(1)
  {
    sleep(1);
    char* p = inet_ntoa(ptr->sin_addr);
    cout << "pthread 2:" << p << endl;
  }
  return NULL;
}
int main()
{
  struct sockaddr_in addr1;
  struct sockaddr_in addr2;
  addr1.sin_addr.s_addr = 0x0;
  addr2.sin_addr.s_addr = 0xffffffff;

  pthread_t t1;
  pthread_t t2;
  pthread_create(&t1, NULL, Routine1, (void*)&addr1);
  pthread_create(&t2, NULL, Routine2, (void*)&addr2);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
