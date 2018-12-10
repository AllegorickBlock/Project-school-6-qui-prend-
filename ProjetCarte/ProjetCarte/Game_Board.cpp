#include "stdafx.h"
#include "Game_Board.h"


#pragma region Game

#pragma region Game_Board : Constructeurs et destructeurs

Game_Board::Game_Board() { for (int i = 0; i < Const_Var::nmbr_Rows; i++) this->game_rows[i] = new Row(); }

Game_Board::~Game_Board()
{
	for (int i = 0; i < Const_Var::nmbr_Rows; i++)
	{
		delete this->game_rows[i];
		this->game_rows[i] = nullptr;
	}
}

#pragma endregion

Game_Board::Row & Game_Board::Get_row(int index)
{
	if (index >= 0 && index < Const_Var::nmbr_Rows) return *this->game_rows[index];
	else throw new exception("On essaye d'acceder a une rangée inexistante");
}

#pragma endregion




#pragma region Row

#pragma region Row : Constructeurs & Destructeurs

Game_Board::Row::Row() { for (int i = 0; i < Const_Var::nmbr_cards_in_Rows; i++) row_card[i] = nullptr; }

Game_Board::Row::~Row() { for (int i = 0; i < Const_Var::nmbr_cards_in_Rows; i++) row_card[i] = nullptr; }

#pragma endregion

#pragma region Row : Fonctions modif cartes
void Game_Board::Row::Add_card(Card * my_card)
{
	for (int l = 0; l < Const_Var::nmbr_cards_in_Rows; l++)
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

void Game_Board::Row::Remove_all()
{
	for (int i = 0; i < Const_Var::nmbr_cards_in_Rows; i++)
	{
		if (this->row_card[i] != nullptr) this->row_card[i]->Set_status(0); // Si on retire la carte c'est pour la remettre dans le deck
		this->row_card[i] = nullptr;
	}
}

#pragma endregion

#pragma region Row : Fonctions Get

int Game_Board::Row::Get_sum_number_beef()
{
	int sum = 0;
	for (int i = 0; i < Const_Var::nmbr_cards_in_Rows; i++) // On fait la sommes des numéros têtes de boeufs de toute les carte de la rangée
	{
		if (this->row_card[i] != nullptr) sum += this->row_card[i]->Get_beef_number();
		else return sum;
	}
}

Card & Game_Board::Row::Get_card(int index) 
{
	if (index < Const_Var::nmbr_cards_in_Rows && Const_Var::nmbr_cards_in_Rows >= 0) return *row_card[index];
}

Card & Game_Board::Row::Get_last_card()
{
	for (int i = 0; i < Const_Var::nmbr_cards_in_Rows; i++)		// On regarde toute les cartes de la rangée, et si la prochaine carte est inexistante,
	{															// on considerra notre carte actuelle comme la derniere carte de la rangée
		if (i == 5) return *this->row_card[Const_Var::nmbr_cards_in_Rows - 1];
		else if (this->row_card[i + 1] == nullptr)
		{
			return *this->row_card[i];
			break;
		}
	}
}

#pragma endregion

#pragma endregion

