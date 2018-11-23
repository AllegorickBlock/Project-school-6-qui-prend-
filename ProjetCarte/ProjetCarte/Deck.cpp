#include "stdafx.h"
#include "Deck.h"



Deck::Deck()
{
	

	for (int i = 0; i < 104; i++)
	{
		Card *my_Card = new Card(i);
		*tab_Cards[i+1] = *my_Card;

		delete my_Card;
		my_Card = nullptr;
	}

}


Deck::~Deck()
{
}

Card Deck::get_Card(int some_Card)
{
	return tab_Cards(some_Card);
}
