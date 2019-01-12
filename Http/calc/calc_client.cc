#include "tcp_client.hpp"
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "Usage: ./dict_client [ip][port]" << endl;
    return 1;
  }

  TcpClient client(argv[1], atoi(argv[2]));
  client.Connect();

  Request_t req;
  Respon_t res;
  while(1)
  {
    memset(&req, 0 ,sizeof(req));
    memset(&res, 0, sizeof(res));

    cout << "请输入[左操作数][右操作数]:"; 
    cin >> req.x >> req.y;
    cout << "请输入操作符[12345--->+-*/%]:";
    cin >> req.op;

    client.Send(req);
    client.Recv(res);
    cout << "结果是否正确:" << res.flag << endl;
    cout << "运算结果:" << res.res << endl;
  }
  return 0;
}
