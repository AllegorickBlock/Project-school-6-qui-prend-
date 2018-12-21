// Constructor_database.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "sqlite3.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) 
{


	int a = 0;


	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;

	/* Open database */
	rc = sqlite3_open("score.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else fprintf(stderr, "Opened database successfully\n");
	

	/* Create SQL statement */
	sql = "INSERT INTO Player (IDplayer)\n"  
		"VALUES (1); \n" \
		"INSERT INTO Player (IDplayer) \n"  \
		"VALUES (2); \n"     \
		"INSERT INTO Player (IDplayer)\n" \
		"VALUES (3);\n" \
		"INSERT INTO Player (IDplayer)\n" \
		"VALUES (4);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else fprintf(stdout, "Records created successfully\n");

	sqlite3_close(db);
	cin >> a;
	return 0;
}
