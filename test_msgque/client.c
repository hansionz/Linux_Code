#include "commen.h"

int main()
{
  int msgid=getMsgQueue();

  char buf[1024];
  
  recevMsg(msgid,SERVER_TYPE,buf);
  printf("Sever$ %s\n",buf);

  return 0;
}
