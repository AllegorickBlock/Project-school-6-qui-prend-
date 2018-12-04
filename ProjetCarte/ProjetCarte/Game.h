#pragma once
#include "iostream"
#include <ctime>
#include "Deck.h"
#include "Card.h"
#include "Player.h"
#include "Game_Board.h"
#include <fcntl.h>   // Bibliotheque necessaire pour l'utilisation de _setmode
#include <io.h>	

class Game
{
	int number_Gamer;
	class Turn
	{
		int number_Turn;

		Turn();
		~Turn();
		
	};

public:
	Game();
	~Game();
	static inline void Show_beef_symbol();
};

