// ProjetCarte.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "iostream"
#include "Game.h"

using namespace std;

int main()
{
	int point_arret;

	Game * my_Game = new Game(); // ON créée une partiue vie la constructeur de Game

	cin >> point_arret;
	delete my_Game;
	my_Game = nullptr;
}



