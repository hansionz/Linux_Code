#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<sys/times.h>
#include<wait.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    //最后输入的字符是`\n`,把`\n`覆盖掉
    //fgets(buf,BUFNUM,stdin);
    //buf[strlen(buf)-1]=0;
    /*系统调用接口实现*/
    ssize_t s=read(0,buf,sizeof(buf)-1);
    if(s>0){//返回值大于0说明读成功，为实际读到的字符个数
      buf[s-1]=0;//把最后一个读到的\n覆盖掉
    }
    //解析命令，把命令分隔成单个字符串放入到myargv中
    char* myargv[COUNT];
    int index=0;
    myargv[index++]=strtok(buf," ");
    char* ret=NULL;
    //巧用strtok,strtok第一次读完会记住读到的位置，所以后边读的第一个参数为NULL
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
      //实现重定向功能
      int i=0;
      for(;i<index;i++){
        //如果遇到重定向符号，则字符串为重定向的文件，前面是命令，把1号标准输出关了，把文件打开就实现了重定向
        if(strcmp(myargv[i],">")==0){
          char* file=myargv[i+1];
          myargv[i]=NULL;

          close(1);
          open(file,O_WRONLY|O_CREAT,0777);
          break;
        }
      }
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
