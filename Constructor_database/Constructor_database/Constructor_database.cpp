// Constructor_database.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "sqlite3.h"

using namespace std;

int main()
{
	int a;



	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("score.db", &db);

	if (rc)	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	else	fprintf(stderr, "Opened database successfully\n");

	sqlite3_close(db);




	cin >> a;
	return (0);
}
