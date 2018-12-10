#pragma once
#include <iostream>
#include "Const_var.h"

using namespace std;

class Card
{
	const int deck_status = 0;
	const int hand_status = 1;
	const int row_status = 2;

	int number;
	int beef_Number;
	int status; // Si status : 0 = deck, 1 = hand, 2 = row 
				
public:
	Card(int nmbr);
	~Card();
	
	bool In_hand();
	bool In_Deck();
	bool In_Row();
	void Set_status(int nbr_status);

	int  Get_number();		     
	void Set_number(int nmbr);	
	int	 Get_beef_number();

	Card operator>(const Card& other_card) const;
	Card operator<(const Card& other_card) const;
	int  operator-(const Card& other_card) const;
};

