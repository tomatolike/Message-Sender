all : client_test server_test

client_test : client_test.cpp ClientApi.o
	g++ -o client_test client_test.cpp client_api.o lib/libzookeeper_mt.a -std=c++11 -pthread

server_test : server_test.cpp ServerApi.o
	g++ -o server_test server_test.cpp server_api.o lib/libzookeeper_mt.a -std=c++11 -pthread

ClientApi.o : client_api.cpp client_api.h
	g++ -c client_api.cpp

ServerApi.o : server_api.cpp server_api.h
	g++ -c server_api.cpp

clean :
	rm client_test server_test client_api.o server_api.o