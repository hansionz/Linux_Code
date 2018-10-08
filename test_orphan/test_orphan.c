#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    pid_t id=fork();
    if(id<0){
        perror("use fork");
        exit(1);
    }
    else if(id==0){//child
        printf("I am child [%d],My parent is [%d]\n",getpid(),getppid());
        sleep(10);
        exit(1);
    }
    else{//parent
        printf("I am parent [%d],My parent is [%d]\n",getpid(),getppid());
        sleep(2);
        exit(1);
    }
    return 0;
}
