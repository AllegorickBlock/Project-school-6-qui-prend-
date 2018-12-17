#include "stdafx.h"
#include "Card.h"

#pragma region Card : Constructeur & Destructeur

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

#pragma region Fonctions etat de status 

void Card::Set_status(int nbr_status) { this->status = nbr_status; } 
bool Card::In_hand() { return status == deck_status; }
bool Card::In_Deck() { return status == deck_status; }
bool Card::In_Row()  { return status == row_status; }

#pragma endregion

int Card::Get_number() { return this->number; }
void Card::Set_number(int nmbr) { this->number = nmbr; } // Permet de modifier le numero de carte

int Card::Get_beef_number() { return this->beef_Number; }

int Card::Get_nbr_player() {	return nbr_current_player;	}

void Card::Set_nbr_player(int nbr)	{	nbr_current_player = nbr;	}

#pragma region surcharges operateurs

Card Card::operator>(const Card & other_card) const	{	return this->number > other_card.number;	}

Card Card::operator<(const Card & other_card) const	{	return this->number < other_card.number;	}

int Card::operator-(const Card & other_card) const	{	return (this->number - other_card.number);	}

#pragma endregion

