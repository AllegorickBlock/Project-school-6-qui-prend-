#pragma once
#include "Card.h"
#include "Player.h"
#include "Const_var.h"

class Game_Board
{
public:
	class Row
	{
		Card * row_card[Const_Var::nmbr_cards_in_Rows];
	public:
		Row();
		~Row();

		void Add_card(Card * my_card);
		void Remove_all();

		int Get_sum_number_beef();
		int Get_nbr_cards_in();
		Card& Get_card(int index);
		Card& Get_last_card();
	};

	Row * game_rows[Const_Var::nmbr_Rows];

	Game_Board();
	~Game_Board();

	Row & Get_row(int index);
};

