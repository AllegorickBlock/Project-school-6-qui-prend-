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

static int callback(void *data, int argc, char **argv, char **azColName) // Methode d'appel de retour pour l'execution des requettes sqlite
{
	int i;

	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) 	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	
	printf("\n");
	return 0;
}

int main(int argc, char* argv[]) {

	int break_point = 0; //Permet de ne pas fermer l'application directement apres qu'elle se soit ouvert
	sqlite3 * db; // Objet sqlite
	char *error_msg = 0;	// si il y a une erreur, cette variable contiendra la phrase explicative du système par rapport à celle ci
	int connection_database;
	
	connection_database = sqlite3_open("score.db", &db); // On ouvre la base de donné en specifiant le fichier .db, celui ci doit se trouver dans le même dossier que le .exe de notre application

	if (connection_database) 
	{
		fprintf(stderr, "Base de donnee inaccessible : %s\n", sqlite3_errmsg(db));
		return 0;
	}
	else fprintf(stderr, "Base de donnee ouverte avec succes \n");
	
	char sql_request[100] = "";
	int a = 4;
	string b = ")";
	string ms = "insert or replace into player(idplayer)values(" + to_string(a) + b;
	strcat(sql_request, ms.c_str()); // permet de concatener nos chaines de caractères
	connection_database = sqlite3_exec(db, sql_request, callback, 0, &error_msg); // on execute la requette que l'on créé dans sql

	int nb_player = 1;
	int nb_score = 24;
	int resultat = 1;

	string score_query = "";
	string game_query = "INSERT INTO Game (Gdate) VALUES(DATETIME('now','localtime'));";
	sqlite3_exec(db, game_query.c_str(), callback, NULL, NULL);
	for (int i = 0; i < 4; i++, nb_player++)
	{
		char sql[150] = "";
		score_query = "INSERT INTO Score(IDPlayer,IDGame,NBscore,NBresult) VALUES("
			+ to_string(nb_player) + ",(SELECT IDGame FROM Game WHERE IDGame = (SELECT max(IDGame) FROM Game)),"
			+ to_string(nb_score) + "," + to_string(resultat) + ")";
		strcat(sql, score_query.c_str());
		sqlite3_exec(db, score_query.c_str(), callback, NULL, NULL);
	}

	cout << "------------------------------------ Voici tout les resultats par ordre croissant sur la date et l'heure ------------------------------------ \n\n";
	string query = "SELECT s.IDGame,g.GDate,s.IDPlayer,s.NBscore,s.NBresult   FROM Game as g ,Score as s WHERE g.IDGame = s.IDGame ORDER BY g.GDate ";
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

	cout << "------------------------------------ Voici le nombre de partie gagnee pour chaque joueur ------------------------------------ \n\n";
	query = "SELECT p.IDPLayer ,COUNT(p.IDPLAYER) as partiesGagnees FROM Score as s, Player as P WHERE s.NBresult = 1 AND p.IDPLayer == s.IDPlayer GROUP BY p.IDPLAYER;";
	sqlite3_exec(db, query.c_str(), callback, NULL, NULL);

	if (connection_database != SQLITE_OK)
	{
		fprintf(stderr, "Erreur dans l'insertion de requetes dans la base de donnee sqlite: %s\n", error_msg);
		sqlite3_free(error_msg);
	}
	else fprintf(stdout, "La base de donnee a ete modifiee avec succes\n");
	
	sqlite3_close(db);	

	cin >> break_point;

	return 0;
}
