#include <iostream>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


using namespace std;
int main()
{
  struct pollfd poll_fd;
  poll_fd.fd = 0;
  poll_fd.events = POLLIN;
  int time = 10000;

  while(1)
  {
    int ret = poll(&poll_fd, 1 ,time);
    if(ret < 0)
    {
      perror("use poll");
      continue;
    }
    else if(ret == 0){
      cout << "poll timeout!" << endl;
      continue;
    }
    else{
      char buf[100];
      read(0, buf, sizeof(buf));
      cout << buf << endl;
    }
  }
  return 0;
}
