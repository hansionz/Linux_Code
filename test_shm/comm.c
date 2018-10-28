#include "comm.h"

static int commShm(int size,int flags)
{
  key_t key=ftok(".",0X6666);
  if(key<0){
    perror("use ftok");
    exit(1);
  }

  int shmid=shmget(key,size,flags);
  if(shmid<0){
    perror("use shmget");
    exit(1);
  }
  return shmid;
}

int createShm(int size)
{
  return commShm(size,IPC_CREAT | IPC_EXCL | 0666);
}

int destroyShm(int shmid)
{
  int ret=shmctl(shmid,IPC_RMID,NULL);
  if(ret<0){
    perror("use shmctl");
    exit(1);
  }
}

int getShm(int size)
{
  return commShm(size,IPC_CREAT);
}
