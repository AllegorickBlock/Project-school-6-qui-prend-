#include "stdafx.h"
#include "Game_Board.h"


Game_Board::Row & Game_Board::Get_row(int index)
{
	if(index >= 0 && index < Const_var::nmbr_Rows) return *this->game_rows[index];
	else throw new exception("On essaye d'acceder a une rangée inexistante");
}

Game_Board::Game_Board()
{
	for (int i = 0; i < Const_var::nmbr_Rows; i++)
	{
		this->game_rows[i] = new Row();
	}
}


Game_Board::~Game_Board()
{
	for (int i = 0; i < Const_var::nmbr_Rows; i++)
	{
		delete this->game_rows[i];
		this->game_rows[i] = nullptr;
	}
}



/////////////////////////

void Game_Board::Row::Add_card(Card * my_card)
{
	for (int l = 0; l < Const_var::nmbr_cards_in_Rows; l++)
	{
		if (row_card[l] == nullptr)
		{
			row_card[l] = my_card;
			row_card[l]->Set_status(2);
			my_card = nullptr;
			break;
		}
	}
}

Card & Game_Board::Row::Get_card(int index)
{
	if (index < Const_var::nmbr_cards_in_Rows && Const_var::nmbr_cards_in_Rows >= 0) return *row_card[index];
}

Card & Game_Board::Row::Get_last_card()
{
	for (int i = 0; i < Const_var::nmbr_cards_in_Rows; i++)
	{
		if(i == 5) return *this->row_card[Const_var::nmbr_cards_in_Rows-1];
		else if (this->row_card[i + 1] == nullptr)
		{
			return *this->row_card[i];
			break;
		}
	}
}

Game_Board::Row::Row() { for (int i = 0; i < Const_var::nmbr_cards_in_Rows; i++) row_card[i] = nullptr; }

Game_Board::Row::~Row() { for (int i = 0; i < Const_var::nmbr_cards_in_Rows; i++) row_card[i] = nullptr; }