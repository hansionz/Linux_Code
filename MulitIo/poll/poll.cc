#include <iostream>
#include <poll.h>

// 监控标准输入
int main()
{
  struct pollfd poll_fd;
  poll_fd.fd = 0;
  poll_fd.events = POLLIN;
  poll_fd.revents = 0;
  int timeout = -1;

  while (1)
  {
    switch(poll(&poll_fd, 1, timeout))
    {
      case -1:
        std::cerr << "poll error..." << std::endl;
        break;
      case 0:
        std::cout << "timeout..." << std::endl;
        break;
      default:
        // 读就绪,从标准输入去读
        if (poll_fd.revents & POLLIN)
        {
          std::string s;
          std::cin >> s;
          std::cout <<  "echo# " << s << std::endl;
        }
        break;
    }
  }
  return 0;
}

