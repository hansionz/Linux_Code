#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int g_val=0;
int main(){
    pid_t id=fork();
    if(id<0){
        perror("use fork");
        exit(1);
    }
    else if(id==0){//child
        g_val=100;
        printf("I am child:[%d],%d,%p\n",getpid(),g_val,&g_val);
    }
    else{//parent
        printf("I am parent:[%d],%d,%p\n",getpid(),g_val,&g_val);
    }
    sleep(1);
    return 0;
}
