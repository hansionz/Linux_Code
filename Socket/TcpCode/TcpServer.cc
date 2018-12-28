#include <iostream>

class TcpServer
{
public:
  TcpServer()
  {}
  ~TcpServer()
  {
    close(sock);
  }
private:
  int sock;
};
