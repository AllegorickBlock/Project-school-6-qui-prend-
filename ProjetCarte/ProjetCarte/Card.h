#pragma once
#include <iostream>
class Card
{
	int number;
	int beef_Number;

public:
	Card(int nmbr);
	~Card();
	int Get_number();	   // Accesseur a number
	int Get_beef_number(); // Accesseur � beef_number
	bool Compare_number(Card card_to_compare);	 // renvoie true si est plus grand que la carte pass� en parametre, false dans le cas contraire
	int Difference_number(Card card_to_compare); // Retourne la difference de l'objet card et de l'objet card pass� en parametre. ATTENTION renvoi un negatif si plus petit

};

