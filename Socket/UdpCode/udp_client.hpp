#pragma once
#include "udp_sockect.hpp"

class UdpClient{
public:
  UdpClient(std::string& ip, uint16_t port)
    :_ip(ip)
     ,_port(port)
  {
    //创建套接字
    _sock.Sockect();
  }

  ~UdpClient()
  {
    _sock.Close();
  }

  void RecvFrom(std::string* buf)
  {
     _sock.ReceFrom(buf);
  }

  void SendTo(std::string& buf)
  {
     _sock.SendTo(buf, _ip, _port);
  }
private:
  UdpSockect _sock;
  std::string _ip;
  uint16_t _port;
};
