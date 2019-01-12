#include "tcp_server.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "Usage: ./tcp_server [ip][port]" << endl;
    return 1;
  }


  string ip(argv[1]);
  TcpServer server(ip,atoi(argv[2])); 
  server.Start();

  return 0;
}
