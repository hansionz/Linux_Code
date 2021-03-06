#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<sys/times.h>
#include<wait.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>

#define MAX 128
#define NUM 128
#define BUFNUM 1024
#define COUNT 16
//获取用户名
void GetLoginname(){
  struct passwd* pwd=getpwuid(getuid());
  printf("[%s",pwd->pw_name);
}
//获取主机名
void Gethostname(){
  char name[MAX];
  gethostname(name,sizeof(name));
  printf("@%s",name);
}
//获取当前文件的路径
void Getpath(){
  char buf[NUM];
  getcwd(buf,sizeof(buf));
  char* p=buf+strlen(buf)-1;
  while(*p!='/'){
    --p;
  }
  ++p;
  printf(" %s]$ ",p);
}

int main(){

  while(1){
    //打印[zsc@localhost MyShell]
    GetLoginname();
    Gethostname();
    Getpath();
    fflush(stdout);//不刷新缓冲区会影响下边
    //输入命令
    char buf[BUFNUM];
    fgets(buf,BUFNUM,stdin);
    buf[strlen(buf)-1]=0;
    //解析命令，把命令分隔成单个字符串放入到myargv中
    char* myargv[COUNT];
    int index=0;
    myargv[index++]=strtok(buf," ");
    char* ret=NULL;
    while(ret=strtok(NULL," ")){
      myargv[index++]=ret;
    }
    myargv[index]=NULL;

    pid_t id=fork();
    if(id<0){//error
      perror("use fork");
      exit(1);
    }
    //子进程进行程序替换，执行程序
    else if(id==0){//child
      execvp(myargv[0],myargv);
      exit(1);
    }
    //父进程只要等待即可
    else{//parent
      waitpid(id,NULL,0);
    }
  }
  return 0;
}
