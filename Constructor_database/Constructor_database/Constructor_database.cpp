// Constructor_database.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <string.h>
#include <cstring>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "sqlite3.h"

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName) {
	int i;

	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) 	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) {

	int z = 0;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char sql[100] ="";

	
	rc = sqlite3_open("score.db", &db); // On ouvre la base de donné en specifiant le fichier

	if (rc) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else fprintf(stderr, "Opened database successfully\n");
	
	int a = 4;
	string b = ")";
	string ms = "INSERT INTO Player VALUES (" + to_string(a) + b;
	strcat(sql, ms.c_str()); // Permet de concatener nos chaines de caractères
	strcat(sql, ")");
	
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // On execute la requette que l'on créé dans sql

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else fprintf(stdout, "Records created successfully\n");
	
	sqlite3_close(db);
	return 0;

	cin >> z;
}
