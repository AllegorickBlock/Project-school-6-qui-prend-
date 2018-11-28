#pragma once
#include <iostream>

using namespace std;

class Card
{
	int number;
	int beef_Number;

public:
	Card(int nmbr);
	~Card();
	int Get_number();	   // Accesseur a number
	void Set_number(int nmbr);
	int Get_beef_number(); // Accesseur a beef_number
	bool Compare_number(Card card_to_compare);	 // Renvoie true si est plus grand que la carte passé en parametre, false dans le cas contraire
	int Difference_number(Card card_to_compare); // Retourne la difference de l'objet card et de l'objet card passé en parametre. ATTENTION renvoi un negatif si plus petit

};

