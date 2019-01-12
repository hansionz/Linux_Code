#pragma once 

#include "tcp_socket.hpp"
#include "threadpool.hpp"
#include <string.h>
#include "comm.hpp"

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

//typedef void (*Handler)(string& req, string* res);

class TcpServer
{
public:
  TcpServer(string ip, uint16_t port)
    :_pool(5)
    ,_ip(ip)
     ,_port(port)
  {}

  static void service(TcpSocket sock)
  {

    Request_t requ;
    Respon_t resp;
    for(;;){
    
    memset(&requ, 0 ,sizeof(requ));
    memset(&resp, 0, sizeof(resp));
    sock.Recv(requ);
    resp.flag = 0;
    switch(requ.op){
      case 1:
        resp.res = requ.x + requ.y;
        break;
      case 2:
        resp.res = requ.x - requ.y;
        break;
      case 3:
        resp.res = requ.x * requ.y;
        break;
      case 4:
        {
          if(requ.y == 0){
            resp.flag = 1;
          }else{
            resp.res = requ.x / requ.y;
          }
        }
        break;
      case 5:
        resp.res = requ.x % requ.y;
        break;
      default:
        resp.flag = 2;
        cout << "[左操作数][运算符(12345--->+-*/%)][右操作数]" << endl;
        break;
    }
    sock.Send(resp);
    }
    sock.Close();
  }
  void Start()
  {
    //1.创建socket
    listen_sock.Socket();
    //2.绑定ip和端口号
    listen_sock.Bind(_ip, _port);
    //3.监听
    listen_sock.Listen(5);
    //初始化线程池
    _pool.InitPool();
    while(1)
    {
      TcpSocket new_sock;
      string ip;
      uint16_t port;
      //4.接收连接
      listen_sock.Accept(&new_sock, &ip,&port); 
      cout <<"client:" << ip.c_str() << " connect" << endl;

      Task t(new_sock, service);
      _pool.AddTask(t);
    }
  }
private:
  TcpSocket listen_sock;
  ThreadPool _pool;
  string _ip;
  uint16_t _port;
};
