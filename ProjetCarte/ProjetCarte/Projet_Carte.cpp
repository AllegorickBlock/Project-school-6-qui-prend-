#include "stdafx.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[])
{
	int break_point;
	int nb_human_player = 0;

	if (argc > 1) nb_human_player = (int)*argv[1] - 28;

	Game * my_Game = new Game(nb_human_player);
	delete my_Game;
	my_Game = nullptr;

	cin >> break_point;
}