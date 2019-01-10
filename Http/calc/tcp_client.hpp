#pragma once 

#include "tcp_socket.hpp"

class TcpClient
{
public:
  TcpClient(string ip, uint16_t port)
    :_ip(ip)
     ,_port(port)
  {
    sock.Socket();
  }
  void Connect()
  {
    sock.Connect(_ip, _port);
  } 
  void Recv(string* buf)
  {
    sock.Recv(buf);
  }
  void Send(const string& buf)
  {
    sock.Send(buf);
  }
  ~TcpClient()
  {
    sock.Close();
  }
private:
  TcpSocket sock;
  string _ip;
  uint16_t _port;
};
