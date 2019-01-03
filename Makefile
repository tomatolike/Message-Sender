all : client_test server_test

client_test : client_test.cpp Client_API.o
	g++ -o client_test client_test.cpp Client_API.o lib/libzookeeper_mt.a -std=c++11 -pthread

server_test : server_test.cpp Server_API.o
	g++ -o server_test server_test.cpp Server_API.o lib/libzookeeper_mt.a -std=c++11 -pthread

Client_API.o : Client_API/Client_API.cpp Client_API/Client_API.h
	g++ -c Client_API/Client_API.cpp

Server_API.o : Server_API/Server_API.cpp Server_API/Server_API.h
	g++ -c Server_API/Server_API.cpp