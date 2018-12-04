#pragma once
#include "Card.h"
#include "Player.h"


class Game_Board
{
	const int nbr_row = 4;

public:

	class Row
	{
		const int nbr_cards_in_rows = 6;

		Card * row_card[6];
	public:

		void Add_card(Card * my_card, int index);
		Card& Get_card(int index);
		Card& Get_last_card();
		Row();
		~Row();
	};

	Row * game_rows[4];


	Row & Get_row(int index);
	Game_Board();
	~Game_Board();
};

