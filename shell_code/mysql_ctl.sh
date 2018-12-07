#! /bin/bash 

#echo $1
#echo $2
#echo $3
#echo $4  # 命令行参数

case $1 in
  start | -[sS]) # shell脚本支持通配符
    service mysqld start  # 启动mysql--service mysqld start
    ;;
  stop | -[tT])
    service mysqld stop 
    ;;
  status )
    ;;
  restart | -[rt] | [RT])
    service mysqld stop 
    service mysqld start 
    ;;
  * )
    echo "usage: $0 [start|stop|status|restart]" # $0 脚本名称
    ;;
esac # 结束标志
