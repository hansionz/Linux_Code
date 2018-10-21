libmymath.so:sum.o sub.o
	gcc -shared -o libmymath.so sum.o sub.o
sum.o:sum.c
	gcc -fPIC sum.c -o sum.o
sub.o:sub.c
	gcc -fPIC sub.c -o sub.o
.PHONY:clean
clean:
	rm -rf sum.o sub.o libmymath.so
