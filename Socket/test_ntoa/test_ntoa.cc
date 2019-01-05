#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
int main()
{
  struct sockaddr_in addr1;
  struct sockaddr_in addr2;

  addr1.sin_addr.s_addr = 0x0;
  addr2.sin_addr.s_addr = 0xffffffff;
  char* p1 = inet_ntoa(addr1.sin_addr);
  char* p2 = inet_ntoa(addr2.sin_addr);

  cout << p1 << endl << p2 << endl;
  return 0;
}
