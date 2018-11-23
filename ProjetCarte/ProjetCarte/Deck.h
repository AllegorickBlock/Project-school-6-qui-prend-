#pragma once
#include "Card.h"
class Deck
{
	Card *tab_Cards[104];
	


public:
	Deck();
	~Deck();

	void Mix_card();
};

