#include "udp_server.hpp"
#include <unordered_map>

std::unordered_map<std::string, std::string> dict;

void Translate(const std::string& req, std::string* res)
{
  //std::cout << "translate" << std::endl;
  auto it = dict.find(req);
  if(it == dict.end())
  {
    *res = "词典中没有该词汇";
    return;
  }
  *res = it->second;
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << "Usage:./dict_server[port]" << std::endl;
    return 1;
  }

  dict.insert(std::make_pair("sport","运动"));
  dict.insert(std::make_pair("computer","电脑"));
  dict.insert(std::make_pair("english","英语"));
  dict.insert(std::make_pair("math","数学"));

  UdpServer server;
  //std::string ip(argv[1]);
  server.Start(atoi(argv[1]), Translate);

  return 0;
}
