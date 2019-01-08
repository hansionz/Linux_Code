#include "tcp_client.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "Usage: ./dict_client [ip][port]" << endl;
    return 1;
  }

  TcpClient client(argv[1], atoi(argv[2]));
  client.Connect();

  while(1)
  {
    cout << "请输入查询的单词:" << endl;
    string word;
    cin >> word;

    if(word == "quit")
      break;

    client.Send(word);
    
    string res;
    client.Recv(&res);

    cout << "意思是:" << res << endl;
  }
  return 0;
}
