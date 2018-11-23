#pragma once
class Card
{
	int number;
	int beef_number;

public:
	Card(int nmbr);
	~Card();
	int Get_number();
	int Get_beef_number();
	bool Compare_number(Card Card_to_compare);
	int Difference_number(Card Card_to_compare);

};

