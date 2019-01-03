inline void Game::Sql_score_insertion(Player * my_players[])
{
	int z = 0;
	sqlite3 *db; // On crée notre objet sqlite3 qui représentera notre Base de donnée qu'on liera par la suite
	char *zErrMsg = 0;
	int rc = sqlite3_open("score.db", &db); // On ouvre la base de donné en specifiant le fichie, et on la lie à notre objet db

	string Game_query = "INSERT INTO Game(Gdate) VALUES(DATETIME('now','localtime'));";
	sqlite3_exec(db, Game_query.c_str(), callback, NULL, NULL);

	for (int i = 0; i < 4; i++, Const_Var::nmbr_Gamer)
	{
		char insert_player_query[100] = "";
		char insert_score_request[150] = "";
		int resultat;

		if (my_players[i]->Get_score() >= 66) resultat = 0;
		else resultat = 1;

		string player_query = "INSERT OR REPLACE INTO Player(Name) VALUES(Paul" + to_string(1) + ");";
		strcat(insert_player_query, player_query.c_str());
		rc = sqlite3_exec(db, insert_player_query, callback, 0, &zErrMsg);

		string score_query = "INSERT INTO Score(IDPlayer,IDGame,NBscore,NBresult) VALUES("
			+ to_string(my_players[i]->Get_number() + 1) + ",(SELECT IDGame FROM Game WHERE IDGame = (SELECT max(IDGame) FROM Game)),"
			+ to_string(my_players[i]->Get_score()) + "," + to_string(resultat) + ")";
		strcat(insert_score_request, score_query.c_str());
		sqlite3_exec(db, score_query.c_str(), callback, NULL, NULL);
	}

	sqlite3_close(db);
}

int Game::callback(void * data, int argc, char ** argv, char ** azColName)
{
	fprintf(stderr, "%s: ", (const char*)data);

	for (int i = 0; i < argc; i++) 	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	printf("\n");
	return 0;
}