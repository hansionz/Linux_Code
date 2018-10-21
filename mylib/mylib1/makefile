libmymath.a:sub.o sum.o
	ar -rc libmymath.a sub.o sum.o
sub.o:sub.c
	gcc -c sub.c -o sub.o
sum.o:sum.c
	gcc -c sum.c -o sum.o

.PHONY:clean
clean:
	rm -rf sub.o sum.o libmymath.a
