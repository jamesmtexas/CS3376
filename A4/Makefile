all: server client

server: server.cpp table.cpp cd.cpp track.cpp artist.cpp
	g++ server.cpp table.cpp cd.cpp track.cpp artist.cpp -o server -lsqlite3 -std=c++11

client: client.cpp
	g++ client.cpp -o client
