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

  bool RecvFrom(std::string* buf)
  {
    return _sock.ReceFrom(buf);
  }

  bool SendTo(std::string& buf)
  {
    return _sock.SendTo(buf, _ip, _port);
  }
private:
  UdpSockect _sock;
  std::string _ip;
  uint16_t _port;
};
