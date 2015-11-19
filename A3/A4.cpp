#include <sqlite3.h>
#include <fstream>
#include <iostream>

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;
	for (i=0;i<argc;i++) {
		std::cout << azColName[i] << " = " << argv[i] << std::endl;
	}
}

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::string sql;
	const char* data = "Callback function called";

	sqlite3_open("song.db",&db);

	sql = "update track set title='Money' where cd_id=1 and track_id=6";
	sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	sql = "select * from track where title='Money'";
	sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	sqlite3_close(db);

	return 0;
}
