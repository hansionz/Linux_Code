.PHONY:all
all:dict_client dict_server

dict_client:calc_client.cc  
	g++ -o $@ -std=c++11 $^
dict_server:calc_server.cc 
	g++ -o $@ -std=c++11 $^ -lpthread
.PHONY:clean
clean:
	rm -f dict_client dict_server
