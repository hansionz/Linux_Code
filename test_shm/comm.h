#ifndef __COMM_H__
#define __COMM_H__ 

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>

int createShm(int size);
int destroyShm(int shmid);
int getShm(int size);

#endif //__COMM_H__
