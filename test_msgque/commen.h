#ifndef __COMMENT_H__
#define __COMMENT_H__ 

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include<unistd.h>
#include<stdlib.h>

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf{
  long mtype;
  char mtext[1024];
};

int createMsgQueue();
int getMsgQueue();
int destoryMsgQueue(int msgid);
int sendMsg(int msgid,int type,char *msg);
int recevMsg(int msgid,int receType,char out[]);


#endif //_COMMENT_H__
