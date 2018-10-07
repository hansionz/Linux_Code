#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

//int main(){
//
//    pid_t id=fork();
//    if(id<0){
//        perror("use fork");
//        exit(1);
//    }
//    else if(id==0){//child
//        printf("child is run,pid is [%d]\n",getpid());
//        sleep(5);
//        exit(37);
//    }
//    else{//parent
//        int st;//status
//        pid_t ret=waitpid(-1,&st,0);
//        printf("this is test for waitpid\n");
//        if(WIFEXITED(st)&&ret==id)
//            printf("wait child 5s success,child return code is [%d]\n",WEXITSTATUS(st));
//        else{
//            printf("wait child failed,return.\n");
//            return 1;
//        }
//    }
//    return 0;
//}
int main(){
    pid_t id=fork();
    
    if(id<0){
        perror("use fork");
        exit(1);
    }
    else if(id==0){//child
        printf("child is run,pid is [%d]\n",getpid());
        sleep(5);
        exit(1);
    }
    else{//parent
        int st;//status
        pid_t ret=0;
        do{
            ret=waitpid(-1,&st,WNOHANG);
            if(ret==0){
                printf("child is running\n");
            }
            sleep(1);
        }while(ret==0);
        if(WIFEXITED(st)&&ret==id)
            printf("wait child 5s success,child return code is [%d]\n",WEXITSTATUS(st));
        else
            printf("wait child failed,return.\n");
            return 1;
    }
    return 0;
}
