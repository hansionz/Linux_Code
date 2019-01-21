#include <iostream>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define FILE "/dev/input/mouse0"

int main()
{
  fd_set read_fds;
  struct timeval time;
  time.tv_sec = 10; //设置阻塞超时时间为10秒钟
  time.tv_usec = 0;
  char buf [10];

  //打开设备文件
  int fd = open(FILE, O_RDONLY);
  if(fd < 0){
    perror("use open");
    exit(-1);
  }

  FD_ZERO(&read_fds);
  FD_SET(0, &read_fds);
  FD_SET(fd, &read_fds);
  cout <<">";
  int ret = select(fd+1, &read_fds, NULL, NULL, &time);
  if(ret < 0){
    perror("use select");
    exit(-1);
  }
  else if(0 == ret){
    cout << "等待超时" << endl;
  }
  else{
    if(FD_ISSET(0, &read_fds)){
      memset(buf, 0 ,sizeof(buf)-1);
      read(0, buf, sizeof(buf)-1);
      cout << buf << endl;
    }
    if(FD_ISSET(1, &read_fds))
    {
      memset(buf, 0 ,sizeof(buf)-1);
      read(1, buf, sizeof(buf)-1);
      cout << buf << endl;
    }
  }
  close(fd);
  return 0;
}
