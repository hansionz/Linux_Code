#pragma once 

typedef struct Reqest{
  int x;//左操作数
  int y;//右操作数
  int op;//执行操作(+-*/%-->12345)
}Reqest_t;

typedef struct Respnose{
  bool status; //0 1 2
  int res;
}Respnose_t;

