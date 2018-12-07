#! /bin/bash 

cc=gcc #cc代表要用那个编译器
src=$(ls *.c) #src代表源代码在哪
bin=test # bin代表生成的可执行文件名字

# 表示从两个EOF之间的内容读到cat中然后放到Makfile中
cat <<EOF > Makefile
$bin:$src
  $cc -o \$@ \$<
.PHONY:clean
clean:
  rm -f $bin 
EOF
