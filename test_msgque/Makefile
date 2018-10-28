.PHONY:all
all:client server 

client:client.c commen.c
	gcc -o $@ $^
server:server.c commen.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f server client
