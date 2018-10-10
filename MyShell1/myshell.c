#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/times.h>
#include<wait.h>

#define MAX 16
#define BUF 1024

int main(){
  //
  char* myargv[MAX];
  char buf[BUF];
  while(1){
    printf("[zsc@localhost myshell]* ");
    fgets(buf,MAX,stdin);
    buf[strlen(buf)-1]=0;

    int index=0;
    myargv[index++]=strtok(buf," ");
    char* ret=NULL;
    while(ret=strtok(NULL," ")){
      myargv[index++]=ret;
    }
    myargv[index]=NULL;

    pid_t id=fork();
    if(id<0){
      perror("use malloc");
      exit(1);
     }
    else if(id==0){//child
      execvp(myargv[0],myargv);
      exit(0);
    }
    else{//parent
      waitpid(id,NULL,0);
   }
 }
  return 0;
}
