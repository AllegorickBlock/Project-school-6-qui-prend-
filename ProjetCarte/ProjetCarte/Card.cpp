#include "stdafx.h"
#include "Card.h"


Card::Card(int nmbr) //Constructeur dans lequel on va definir le beef_number de l'objet Card en fonction de son number
{
	if (nmbr != 0) // On mettera en parametre 0 si l'on souhaite creer des cartes "vides", donc des emplacements pour cartes
	{
		this->number = nmbr;
		if (nmbr == 55) this->beef_Number = 7;
		else if ((nmbr % 11) == 0) this->beef_Number = 5;
		else if ((nmbr % 10) == 0) this->beef_Number = 3;
		else if ((nmbr % 5) == 0) this->beef_Number = 2;
		else this->beef_Number = 1;
	}
}


Card::~Card() {}

void Card::Set_number(int nmbr)  { this->number = nmbr; } // Permet de modifier le numero de carte

int Card::Get_number() { return number; }

int Card::Get_beef_number() { return beef_Number; }

bool Card::Compare_number(Card carte_a_comparer)
{
	if (Get_number() > carte_a_comparer.Get_number()) return true;  // Si superieur return true
	if (Get_number() < carte_a_comparer.Get_number()) return false; // Si inferieur return false
}

int Card::Difference_number(Card card_to_compare) //Si negatif, il faut gerer le fait que l'on ne peut pas placer la carte
{ return (Get_number() - card_to_compare.Get_number() ) ; }
