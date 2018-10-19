#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
  FILE*fp=fopen("myfile","w");
  if(!fp){
    perror("use fopen");
    exit(1);
  }
  int count=5;
  const char *msg="hello world\n";
  while(count--)
  {
    fwrite(msg,strlen(msg),1,fp);
  }
  fclose(fp);
  return 0;
}
