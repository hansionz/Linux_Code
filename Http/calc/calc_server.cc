#include "tcp_server.hpp"
#include "comm.hpp"
#include <unordered_map>

//unordered_map<string, string> dict;
//void Translate(string& req, string* res)
//{
//  auto it = dict.find(req);
//  if(it == dict.end())
//  {
//    *res = "词典中没有该单词";
//    return;
//  }
//  *res = it->second;
//}

void Operator(Reqest req, Respnose& pres)//op(+-*/%--->12345)
{
  switch(req.op)
  {
    case 1:
      pres.res = req.x + req.y;
      break;
    case 2:
      pres.res = req.x - req.y;
      break;
    case 3:
      pres.res = req.x * req.y;
      break;
    case 4:
      if(req.y == 0)
      {
        pres.status = 1;
      }
      pres.res = req.x / req.y;
      break;
    case 5:
      pres.res = req.x % req.y;
      break;
    default:
      cout << "Usage:[左操作数][运算符][右操作数]" << endl;
      break;
  }
}
int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    cout << "Usage: ./tcp_server [ip][port]" << endl;
    return 1;
  }

  //初始化词典
  //dict.insert(make_pair("book","书"));
  //dict.insert(make_pair("tree", "树"));
  //dict.insert(make_pair("dream","梦想"));

  TcpServer server(argv[1],atoi(argv[2])); 
  server.Start(Operator);

  return 0;
}
