#pragma once
#include "Card.h"
class Deck
{
	Card *tab_Cards[104];
	


public:
	Deck();
	~Deck();

	Card get_Card(int some_Card);
	void Mix_card();
};

