#include "tcp_server.hpp"
#include <unordered_map>

unordered_map<string, string> dict;
void Translate(string& req, string* res)
{
  auto it = dict.find(req);
  if(it == dict.end())
  {
    *res = "词典中没有该单词";
    return;
  }
  *res = it->second;
}
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "Usage: ./tcp_server [ip][port]" << endl;
    return 1;
  }

  //初始化词典
  dict.insert(make_pair("book","书"));
  dict.insert(make_pair("tree", "树"));
  dict.insert(make_pair("dream","梦想"));

  TcpServer server(argv[1],atoi(argv[2])); 
  server.Start(Translate);

  return 0;
}
