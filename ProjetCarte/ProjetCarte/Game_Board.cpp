#include "stdafx.h"
#include "Game_Board.h"


Game_Board::Row & Game_Board::Get_row(int index)
{
	if(index >= 0 && index < nbr_row) return *this->game_rows[index];
	else throw new exception("On essaye d'acceder a une rangée inexistante");
}

Game_Board::Game_Board()
{
	for (int i = 0; i < nbr_row; i++)
	{
		this->game_rows[i] = new Row();
	}
}


Game_Board::~Game_Board()
{
	for (int i = 0; i < nbr_row; i++)
	{
		delete this->game_rows[i];
		this->game_rows[i] = nullptr;
	}
}



/////////////////////////

void Game_Board::Row::Add_card(Card * my_card, int index)
{
	if (index >= 0 && index < nbr_cards_in_rows)
	{
		row_card[index] = my_card;
		row_card[index]->Set_status(2);
	}
	else throw new exception("On essaye d'ajouter une carte de trop dans les rangées");
}

Card & Game_Board::Row::Get_card(int index)
{
	if (index < nbr_cards_in_rows && nbr_cards_in_rows >= 0) return *row_card[index];
}

Game_Board::Row::Row()
{
	for (int i = 0; i < nbr_cards_in_rows; i++)
	{
		row_card[i] = nullptr;
	}
}


Game_Board::Row::~Row()
{
	for (int i = 0; i < nbr_cards_in_rows; i++)
	{
		delete row_card[i];
		row_card[i] = nullptr;
	}
}