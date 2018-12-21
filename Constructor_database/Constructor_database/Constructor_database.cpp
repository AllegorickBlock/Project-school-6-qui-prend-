// Constructor_database.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "sqlite3.h"

int main()
{
	sqlite3* Score;
	std::string sql = "CREATE TABLE Player("
		"ID INT PRIMARY KEY     NOT NULL) ";
	int exit = 0;
	exit = sqlite3_open("example.db", &Score);
	char* messaggeError;
	exit = sqlite3_exec(Score, sql.c_str(), NULL, 0, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
		std::cout << "Table created Successfully" << std::endl;
	sqlite3_close(Score);
	return (0);
}
