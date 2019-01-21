#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

//设置该文件描述符为非阻塞
void SetNoBlock(int fd)
{
  int f = fcntl(fd, F_GETFL);
  if(f < 0){
    perror("use fcntl");
    return;
  }
  fcntl(fd, F_SETFL | O_NONBLOCK);
}

int main()
{
  SetNoBlock(0);//设置标准输入为非阻塞式
  while(1)
  {
    char buf[1024] = {0};
    ssize_t rs = read(0, buf, sizeof(buf) - 1);
    if(rs <= 0){
      perror("use read");
      sleep(1);
      continue;
    }

    cout << buf << endl;
  }
  return 0;
}
