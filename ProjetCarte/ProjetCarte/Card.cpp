#include "stdafx.h"
#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(int nbr)
{
	number = nbr;

	if (nbr = 55) beef_number = 7;
	else if ((nbr % 11) == 0) beef_number = 5;
	else if ((nbr % 10) == 0) beef_number = 3;
	else if ((nbr % 5 ) == 0) beef_number = 2;
	else beef_number = 1;

}


Card::~Card()
{
}

int Card::Get_number() { return number; }

int Card::Get_beef_number() { return beef_number; }

bool Card::Compare_number(Card carte_a_comparer)
{
	if (Get_number() > carte_a_comparer.Get_number()) return true; // Si superieur return true
	if (Get_number() < carte_a_comparer.Get_number()) return false; // Si inferieur return false
}

int Card::Difference_number(Card Card_to_compare) //Si negatif, il faut gerer le fait que l'on ne peut pas placer la carte
{ return (Get_number() - Card_to_compare.Get_number() ) ; }
