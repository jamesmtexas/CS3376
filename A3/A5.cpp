#include <sqlite3.h>
#include <iostream>

static int callback(void *data, int argc, char **argv, char **azColName) {
	
}

int main(int argc, char *argv[]) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::string sql;

	rc = sqlite3_open("song.db",&db);

	sql = "drop table track";
	sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	sql = "drop table cd";
	sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	sql = "drop table artist";
	sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	sqlite3_close(db);
	return 0;
}
