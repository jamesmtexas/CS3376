#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <fstream>
#include <string.h>
#include <iostream>

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   std::string sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("song.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "create table cd ( \
	id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY, \
	title VARCHAR(70) NOT NULL, \
	artist_id INTEGER NOT NULL, \
	catalogue VARCHAR(30) NOT NULL \
    );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

   /* Create SQL statement */
   sql = "create table artist ( \
	id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY, \
	name VARCHAR(100) NOT NULL \
    );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

   /* Create SQL statement */
   sql = "create table track ( \
	cd_id INTEGER NOT NULL, \
	track_id INTEGER NOT NULL, \
	title VARCHAR(70), \
	PRIMARY KEY(cd_id, track_id) \
    );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

    std::fstream track;
    track.open("track.txt");

    std::string line;
    std::string delimiter = "|";
    std::string cd_id_ref;
    std::string track_id;
    std::string title;

    while (std::getline(track,line)) {
        cd_id_ref = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());
        track_id = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());
        title = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());

        sql = "insert into track(cd_id, track_id, title) values(";
        sql += cd_id_ref + "," + track_id + ",'" + title + "')";
        sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    }

    track.close();

    std::fstream cd;
    cd.open("cd.txt");

    std::string id;
    std::string cd_title;
    std::string cd_id;
    std::string catalogue;

    while (std::getline(cd,line)) {
        id = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());
        cd_title = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());
        cd_id= line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());
        catalogue = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());

        sql = "insert into cd(id,title, artist_id, catalogue) values(";
        sql += id +"," + "'" + cd_title + "'" + "," + cd_id + ",'" + catalogue + "')";
        sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    }

    cd.close();


    std::fstream artist;
    artist.open("artist.txt");

    std::string artist_id;
    std::string track_name;

    while (std::getline(artist,line)) {
        artist_id = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());
        track_name = line.substr(0,line.find(delimiter));
        line.erase(0,line.find(delimiter) + delimiter.length());

        sql = "insert into artist(id,name) values(";
        sql += artist_id + "," + "'" + track_name + "')";
        sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

    }

    artist.close();



    sql = "SELECT * FROM track";
    sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

    sql = "SELECT * FROM cd";
    sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

    sql = "SELECT * FROM artist";
    sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);

   sqlite3_close(db);
   return 0;
}


