#include "commen.h"

int main()
{

  int msgid=createMsgQueue();
  char *str="hello msgqueue";

  sendMsg(msgid,SERVER_TYPE,str);
  sleep(1);
  sendMsg(msgid,SERVER_TYPE,str);
  sleep(1);
  sendMsg(msgid,SERVER_TYPE,str);
  sleep(1);
  sendMsg(msgid,SERVER_TYPE,str);
  sleep(1);
  sendMsg(msgid,SERVER_TYPE,str);
  sleep(1);
  
  char buf[64];
  recevMsg(msgid,SERVER_TYPE,buf);
  printf("%s\n",buf);
  destoryMsgQueue(msgid);
  return 0;
}
