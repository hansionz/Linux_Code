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

void GetLoginname(){
  struct passwd* pwd=getpwuid(getuid());
  printf("[%s",pwd->pw_name);
}

void Gethostname(){
  char name[MAX];
  gethostname(name,sizeof(name));
  printf("@%s",name);
}

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
    
    GetLoginname();
    Gethostname();
    Getpath();
    fflush(stdout);

    char buf[BUFNUM];
    fgets(buf,BUFNUM,stdin);
    buf[strlen(buf)-1]=0;

    char* myargv[COUNT];
    int index=0;
    myargv[index++]=strtok(buf," ");
    char* ret=NULL;
    while(ret=strtok(NULL," ")){
      myargv[index++]=ret;
    }
    myargv[index]=NULL;

    pid_t id=fork();
    if(id<0){
      perror("use fork");
      exit(1);
    }
    else if(id==0){//child
      execvp(myargv[0],myargv);
      exit(1);
    }
    else{//parent
      waitpid(id,NULL,0);
    }
  }
  return 0;
}
