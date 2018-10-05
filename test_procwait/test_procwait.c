#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

    pid_t pid=fork();
    if(pid==-1){
        perror("use fork");
        exit(1);
    }
    else if(pid==0){//child
        printf("I am [%d] parent is[%d]\n", getpid(),getppid());
        sleep(20);
        exit(10);
    }
    else{//parent
        
        int st;//status
        int ret=wait(&st);

        if(ret>0&&(st&0X7F)==0)//normal exit
            printf("child exit code is [%d]\n",(st>>8)&0XFF);
        else//abnormal exit
            printf("sign code is[%d]\n",st&0X7F);
    }
}
