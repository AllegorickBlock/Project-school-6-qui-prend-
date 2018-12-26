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
#include <ctime>
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

	
	rc = sqlite3_open("score.db", &db); // On ouvre la base de donné en specifiant le fichier

	if (rc) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	}
	else fprintf(stderr, "Opened database successfully\n");
	
	char sql[100] = "";
	int a = 4;
	string b = ")";
	string ms = "INSERT OR REPLACE INTO Player(Name) VALUES(\"Salut je suis Paul\")";
	strcat(sql, ms.c_str()); // permet de concatener nos chaines de caractères
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg); // on execute la requette que l'on créé dans sql

	int nb_player = 1;
	int nb_score = 24;
	int resultat = 1;


	string Score_query = "";
	string Game_query = "INSERT INTO Game(GDate) VALUES(DATETIME('now','localtime'));";
	sqlite3_exec(db, Game_query.c_str(), callback, NULL, NULL);
	for (int i = 0; i < 4; i++, nb_player++)
	{
		char sql[150] = "";
		Score_query = "INSERT INTO Score(IDPlayer,IDGame,NBscore,NBresult) VALUES("
			+ to_string(nb_player) + ",(SELECT IDGame FROM Game WHERE IDGame = (SELECT max(IDGame) FROM Game)),"
			+ to_string(nb_score) + "," + to_string(resultat) + ")";
		strcat(sql, Score_query.c_str());
		sqlite3_exec(db, Score_query.c_str(), callback, NULL, NULL);
	}

	string query = "SELECT s.IDGame,g.GDate,s.IDPlayer,s.NBscore,s.NBresult   FROM Game as g ,Score as s WHERE g.IDGame = s.IDGame ORDER BY g.GDate ";
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

	query = "SELECT p.IDPLayer ,COUNT(p.IDPLAYER) as n° FROM Score as s, Player as P WHERE s.NBresult = 1 AND p.IDPLayer == s.IDPlayer GROUP BY p.IDPLAYER;";
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);


	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else fprintf(stdout, "Records created successfully\n");
	
	sqlite3_close(db);

	time_t now = time(0);
	char * charDate = ctime(&now);

	cout << "\n the current time is : " << charDate;


	cin >> z;
}
