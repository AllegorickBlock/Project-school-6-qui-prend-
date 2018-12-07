#pragma once
#include "Card.h"
#include "Player.h"
#include "Const_var.h"

class Game_Board
{
public:

	class Row
	{
		Card * row_card[Const_var::nmbr_cards_in_Rows];
	public:

		void Add_card(Card * my_card);
		Card& Get_card(int index);
		Card& Get_last_card();
		Row();
		~Row();
	};

	Row * game_rows[Const_var::nmbr_Rows];
	

	Row & Get_row(int index);
	Game_Board();
	~Game_Board();
};

