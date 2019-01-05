/**
 * 英译汉词典客户端
 * @Hansionz
 */ 
#include "udp_client.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "Usage:./dict_client[ip][port]" << std::endl;
    return 1;
  }
  std::string ip(argv[1]);
  UdpClient client(ip, atoi(argv[2]));

  while(1)
  {
    std::string word;
    std::cout <<"请输入要查的单词：";
    std::cin >> word;
    if(word == "quit")
    {
      std::cout << "good bye" << std::endl;
      break;
    }
    client.SendTo(word);
    std::string res;
    client.RecvFrom(&res);
    std::cout << res << std::endl;
  }
  return 0;
}
