#pragma once
#include <iostream>

using namespace std;

class Card
{
	const int deck_status = 0;
	const int hand_status = 1;
	const int row_status = 2;
	int number;
	int beef_Number;
	int status; // Definira quand quel etate est la carte, c'est a dire soit dans une mains, soit dans le deck, soit dans une rang�e 
				// Si status : 0 = deck, 1 = hand, 2 = row 
public:
	Card(int nmbr);
	~Card();
	int Get_number();		     // Accesseur a number
	void Set_number(int nmbr);	 // Modifie le num�ro de la carte
	bool In_hand();
	bool In_Deck();
	bool In_Row();
	void Set_status(int nbr_status);
	int Get_beef_number();		 // Accesseur a beef_number
	bool Compare_number(Card card_to_compare);	 // Renvoie true si est plus grand que la carte pass� en parametre, false dans le cas contraire
	int Difference_number(Card card_to_compare); // Retourne la difference de l'objet card et de l'objet card pass� en parametre. ATTENTION renvoi un negatif si plus petit

};

