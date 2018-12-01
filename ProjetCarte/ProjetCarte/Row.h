#pragma once
#include "Card.h"
#include "Player.h"
class Row
{
	const int row_cards_6 = 6;

	Card * row_card[6];
public:

	void Add_card(Card * my_card, int index);
	Card& Get_card(int index);
	Row();
	~Row();
};

