#!/bin/bash 

cc=gcc
src=$(ls *.c)
bin=test 

# 表示从两个EOF之间的内容读到cat中然后放到Makfile中
cat <<EOF > Makefile
$bin:$src
  $cc -o \$@ \$<
.PHONY:clean
clean:
  rm -f $bin 

EOF
