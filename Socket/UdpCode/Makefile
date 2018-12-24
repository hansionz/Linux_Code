.PHONY:all
all:dict_client dict_server 

dict_client:dict_client.cc udp_client.hpp udp_sockect.hpp 
	g++ -o $@ -std=c++11 $^ -g 

dict_server:dict_server.cc udp_server.hpp udp_sockect.hpp 
	g++ -o $@ -std=c++11 $^ -g 

.PHONY:clean
clean:
	rm -f dict_client dict_server
