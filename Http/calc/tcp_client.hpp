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
  void Recv(Respon_t& buf)
  {
    recv(sock.Getfd(), &buf, sizeof(buf)-1, 0);
  }
  void Send(Request_t& buf)
  {
    send(sock.Getfd(), &buf, sizeof(buf), 0);
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
