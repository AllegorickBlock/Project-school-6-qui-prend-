// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Game.h"

using namespace std;

int main(int argc, char * argv[]) // argc est le nombre d'argument de argv, Attention argv[0] contient le nom de la solution, c'est a partir de argv[1] que l'on recupere des parametres entré
{
	int break_point;
	int  nb_human_player = 0;

	if (argc > 1)	nb_human_player =  (int)*argv[1] - 48; //-48 pour passer de l'ASCII a nos valeurs de chiffres

	Game * my_Game = new Game(nb_human_player); // ON créée une partiue vie la constructeur de Game
	delete my_Game;
	my_Game = nullptr;


	cin >> break_point;
}



