.PHONY:all
all:dict_client dict_server

dict_client:dict_client.cc 
	g++ -o $@ -std=c++11 $^
dict_server:dict_server.cc 
	g++ -o $@ -std=c++11 $^
.PHONY:clean
clean:
	rm -f dict_client dict_server
