#pragma once 

#include "tcp_socket.hpp"
#include <functional>
#include <signal.h>

//typedef function<void (const string& req, string* res)> Handler;

typedef void (*Handler)(string& req, string* res);
class TcpProcServer
{
public:
  TcpProcServer(string& ip, uint16_t port)
    :_ip(ip)
     ,_port(port)
  {
    signal(SIGCHLD, SIG_IGN);
  }
  void ProcConnect(TcpSocket& newsock, string& ip, uint16_t port, Handler hanler)
  {
    pid_t id = fork();
    if(id < 0)
    {
      perror("use fork");
      exit(1);
    }
    else if(id == 0){//child
      while(1){
        string req;
        bool ret = newsock.Recv(&req);
        if(!ret){
          newsock.Close();
          return;
        }
        string res;
        hanler(req, &res);
        newsock.Send(res);
        cout << ip << "-" << port << " req:" << req << " | res:" << res <<endl; 
      }
    }
    else{//father
      //父进程直接结束即可，不需要wait子进程，因为已经将SIGCHILD信号捕捉为忽略
      //父进程也不能wait,如果wait不能再次快速调用accept
      //父进程需要关闭newsock
      newsock.Close();
      return;
    }
  }
  void Start(Handler handler)
  {
    listen_sock.Socket();
    listen_sock.Bind(_ip, _port);
    listen_sock.Listen(5);
    while(1)
    {
      TcpSocket newsock;
      string ip;
      uint16_t port;
      listen_sock.Accept(&newsock, &ip, &port);

      cout << "client:" << ip.c_str() << "-" << port << " connect" << endl;
      ProcConnect(newsock, ip, port, handler);
    }
  }

private:
  TcpSocket listen_sock;
  string _ip;
  uint16_t _port;
};
