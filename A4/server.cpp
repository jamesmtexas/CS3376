#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>
#include <vector>
#include <iostream>

#include "table.h"
#include "cd.h"
#include "track.h"
#include "artist.h"

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /* server port – you need to change this */
#define LISTENQ 8 /*maximum number of client connections*/

int main (int argc, char **argv) {
	int listenfd, connfd, n;
	pid_t childpid;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;
	
	//Create a socket for the soclet
	//If sockfd<0 there was an error in the creation of the socket
	if ((listenfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
		perror("Problem in creating the socket");
		exit(2);
	}

	//preparation of the socket address
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	//bind the socket
	bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//listen to the socket by creating a connection queue, then wait for clients
	listen (listenfd, LISTENQ);
	printf("%s\n","Server running...waiting for connections.");
	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		
		//accept a connection
		connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
		printf("%s\n","Received request...");

		if ( (childpid = fork ()) == 0 ) {          //if it’s 0, it’s child process
			printf ("%s\n","Child created for dealing with client requests");

			//close listening socket
			close (listenfd);
			while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
				printf("%s","String received from the client:");
				puts(buf);

				sqlite3 *db;
				sqlite3_open("music.db", &db);

				sqlite3_stmt *stmt;
				sqlite3_prepare_v2(db, buf, -1, &stmt, NULL);

				std::vector<Table*> items;

				//Find out which table we're reading from
				std::string input = buf;

				if (input.find("cd") != std::string::npos) {
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						int id = sqlite3_column_int(stmt, 0);
						const char *title = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
						int artist_id = sqlite3_column_int(stmt, 2);
						const char *catalogue = reinterpret_cast<const char*>(sqlite3_column_text(stmt,3));
						CD *row = new CD(id, title, artist_id, catalogue);
						items.push_back(row);
					}			
				}
			
				else if (input.find("track") != std::string::npos) {
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						int id = sqlite3_column_int(stmt, 0);
						int track_id = sqlite3_column_int(stmt, 1);
						const char *title = reinterpret_cast<const char*>(sqlite3_column_text(stmt,2));
						Track *row = new Track(id, track_id, title);
						items.push_back(row);
					}
				}

				else if (input.find("artist")!= std::string::npos) {
					while (sqlite3_step(stmt) == SQLITE_ROW) {
						int id = sqlite3_column_int(stmt, 0);
						const char *name = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
						Artist *row = new Artist(id, name);
						items.push_back(row);
					}
				}

				sqlite3_close(db);

				std::string result;

				for(std::vector<Table*>::iterator it = items.begin(); it != items.end(); ++it) {
					Table *next = *it;
					result += next->output();
				}

				send(connfd, result.c_str(), MAXLINE, 0);

			}
		
			if (n < 0)
				printf("%s\n", "Read error");
		
			exit(0);
		
		}

		close(connfd);
	}
}
