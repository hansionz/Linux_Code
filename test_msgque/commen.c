#include "commen.h"

static int commenMsgQueue(int flag)
{
  key_t key=ftok(".",0x6666);
  if(key<0){
    perror("ftok fail");
    exit(1);
  }
  int msgid=msgget(key,flag);
  if(msgid<0){
    perror("use msgget");
    exit(1);
  }
  return msgid;
}
int createMsgQueue()
{
  return commenMsgQueue(IPC_CREAT|IPC_EXCL);
}
int getMsgQueue()
{
  return commenMsgQueue(IPC_CREAT);
}

int destoryMsgQueue(int msgid)
{
  int r=msgctl(msgid,IPC_RMID,NULL);
  if(r<0){
    perror("use msgctl");
    return -1;
  }
  return 0;
}
int sendMsg(int msgid,int type,char *msg)
{
  struct msgbuf buf;
  buf.mtype=type;
  strcpy(buf.mtext,msg);

  int r=msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0);
  if(r<0){
    perror("use msgsend");
    return -1;
  }
  return 0;
}
int recevMsg(int msgid,int receType,char out[])
{
  struct msgbuf buf;
  int r=msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),receType,0);
  if(r<0){
    perror("use msgrcv");
    return -1;
  }
  strcpy(out,buf.mtext);
  return 0;
}
