#include "stdafx.h"
#include "Row.h"


void Row::Add_card(Card * my_card, int index)// index doit etre tel : index
{
	if (index >= 0 && index < 6)
	{
		row_card[index] = my_card;
		row_card[index]->Set_status(2);
	}
	else throw new exception("On essaye d'ajouter une carte de trop dans les rangées");
}

Card & Row::Get_card(int index)
{
	if (index < row_cards_6 && row_cards_6 >= 0) return *row_card[index];
}

Row::Row()
{
	for (int i = 0; i < row_cards_6; i++)
	{
		row_card[i] = nullptr;
	}
}


Row::~Row()
{
	for (int i = 0; i < row_cards_6; i++)
	{
		delete row_card[i];
		row_card[i] = nullptr;
	}
}

