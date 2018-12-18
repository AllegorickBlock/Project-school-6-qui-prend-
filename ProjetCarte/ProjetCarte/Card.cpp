#include "stdafx.h"
#include "Card.h"


#pragma region Class : Card

#pragma region Constructor & Destructor

Card::Card(int nmbr) //Constructeur dans lequel on va definir le beef_number de l'objet Card en fonction de son number
{
	if (nmbr > 0 && nmbr <= Const_Var::nmbr_deck_cards)
	{
		this->number = nmbr;
		if (nmbr == 55) this->beef_Number = 7;
		else if ((nmbr % 11) == 0) this->beef_Number = 5;
		else if ((nmbr % 10) == 0) this->beef_Number = 3;
		else if ((nmbr % 5) == 0) this->beef_Number = 2;
		else this->beef_Number = 1;

		this->Set_status(0);
	}
}

Card::~Card() {}

#pragma endregion

#pragma region Functions status 

void Card::Set_status(int nbr_status) { this->status = nbr_status; }
bool Card::In_hand() {
	return status == hand_status
		;
}
bool Card::In_deck() { return status == deck_status; }
bool Card::In_row() { return status == row_status; }

#pragma endregion

#pragma region Functions : Get and Set 

int Card::Get_number() { return this->number; }
void Card::Set_number(int nmbr) { this->number = nmbr; } // Per

int Card::Get_beef_number() { return this->beef_Number; }

void Card::Set_nbr_player(int nbr) { nbr_current_player = nbr; }
int Card::Get_nbr_player() { return nbr_current_player; }

#pragma endregion

#pragma region Operator overloading

Card Card::operator>(const Card & other_card) const { return this->number > other_card.number; }

Card Card::operator<(const Card & other_card) const { return this->number < other_card.number; }

int Card::operator-(const Card & other_card) const { return (this->number - other_card.number); }

#pragma endregion

#pragma endregion
