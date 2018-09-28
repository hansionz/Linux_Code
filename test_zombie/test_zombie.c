#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t id=fork();
    if(id==-1){
        perror("use fork");
        exit(1);
    }
    else if(id>0){//parent
        printf("parent:[%d],I am sleeping...\n",getpid());
        sleep(30);
    }
    else{//chile
        printf("child:[%d],I become Z...\n",getpid());
        sleep(5);
        exit(0);
    }
    return 0;
}
