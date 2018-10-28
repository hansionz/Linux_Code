#include "comm.h"

static int commSemSet(int nums,int flag)
{
  key_t key=ftok(".",0x6666);
  if(key<0){
    perror("use ftok");
    exit(1);
  }
  int semid=semget(key,nums,flag);

  return semid;
}
int createSemSet(int nums)
{
  return commSemSet(nums,IPC_CREAT | IPC_EXCL | 0666);
}
int initSem(int semid,int nums,int initVal)
{
  union semnu _un;
  _un.val=initVal;
  int ret=semctl(semid,nums,SETVAL,_un);
  if(ret<0){
    perror("use semctl");
    exit(1);
  }
  return 0;
}
int getSemSet(int nums)
{
  return commSemSet(nums,IPC_CREAT);
}
static int commPV(int semid,int who,int op)
{
  struct sembuf _sf;
  _sf.sem_num=who;
  _sf.sem_op=op;
  _sf.sem_flg=0;

  int ret = semop(semid,&_sf,1);
  if(ret<0){
    perror("use semop");
  }
  return 0;
}
int P(int semid,int who)
{
  return commPV(semid,who,-1);
}
int V(int semid,int who)
{
  return commPV(semid,who,1);
}
int destroySemSet(int semid)
{
  semctl(semid,0,IPC_RMID);
}
