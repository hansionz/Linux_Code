/**
 * udp服务端程序:udp回显服务器
 *    1.创建socket            socket 
 *    2.为socket绑定地址信息  bind
 *    3.接收发送数据          sendto/recvfrom
 *    4.关闭socket            close
 */  
#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main()
{
  int socketfd;
  struct sockaddr_in addr;//IPV_4
  int ret;
  socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if( socketfd < 0) {
    perror("socket create fail!");
    exit(1);
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9000);//从主机字节序转为网络字节序,小端就转换，大端就不用转换
  addr.sin_addr.s_addr =  inet_addr("192.168.207.130"); //将一个字符串地址转换为网络主机地址
  //0xffffffff 255.255.255.255 广播地址
  //0x00000000  any ,表示网卡的所有地址
  socklen_t len = sizeof(struct sockaddr_in);
  ret = bind(socketfd, (struct sockaddr*)&addr, len);
  if(ret < 0){
    perror("bind");
    exit(1);
  }
 while(1)
 {
    while(1)
    {
      char buf[1024]={0};
      struct sockaddr_in peer_addr;
     ssize_t slen =  recvfrom(socketfd, buff, 1023, 0, (struct sockaddr*)&peer_addr, &len);
     printf(" recv buff:[%ld-%s], from:[%s:%d]",rlen,buff,inet_ntoa(peer_addr.sin_addr.s_addr), ntohs(peer_addr.sin_addr.s_addr);
    }
 }
  return 0;
}
