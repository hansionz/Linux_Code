#pragma once
#include "udp_sockect.hpp"

typedef void (*Handler)(const std::string& req, std::string* res);
class UdpServer{

public:
  UdpServer()
  {
    //创建套接字
    bool flag = _sock.Sockect();
    assert(flag);
  }

  /* 1.创建套接字
   * 2.绑定端口号
   * 3.开始循环读取客户端请求
   * 4.读取到请求后做请求处理
   * 5.得到响应
   * 6.向客户端发回响应
   **/
  //开启服务器
  bool Start(std::string& ip, uint16_t port, Handler handler)
  {
    bool ret = _sock.Bind(ip, port);
    if(!ret)
    {
      return false;
    }
    while(1)
    {
      //不断读取客户端的请求
      std::string req;
      std::string re_ip;
      uint16_t re_port;
      bool flag = _sock.ReceFrom(&req, &re_ip, &re_port);
      if(!flag)
        continue;

      //处理请求得到响应结果
      std::string res;
      handler(req, &res);

      //返回响应给客户端
      _sock.SendTo(res, re_ip, re_port);
      std::cout << "ip: " << re_ip << "port: "<< re_port << "req: " << req << "res: " << res <<std::endl; 
    } 
    _sock.Close();
    return true;
  }
private:
  UdpSockect _sock;
};
