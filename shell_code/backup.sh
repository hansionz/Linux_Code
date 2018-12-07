
#! /bin/bash 

[ $# -ne 1 ] && exit 1  # 如果参数个数不等于1退出

while read line 
do
  echo $line 

done < $1 > file.bak
