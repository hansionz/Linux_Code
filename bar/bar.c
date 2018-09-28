#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main()
{
    char bar[102]={'\0'};
    int i=0;
    const char* lable="|/-\\";
    while(i<100)
    {
        bar[i++]='>';
        // printf("[%-100s][%d%%][%c]\r",bar,i,lable[i%4]);
        printf("\033[1;33;40m[%-100s]\033[1;33;40m[%d%%][%c]\r",bar,i,lable[i%4]);
        fflush(stdout);
        usleep(100000);
    }
    printf("\n");
    return 0;
}
