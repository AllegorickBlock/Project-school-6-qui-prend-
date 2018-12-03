#include "stdafx.h"
#include "Deck.h"


#pragma region Deck : Constructeur & Destructeur

Deck::Deck()  // Constructeur par defaut qui reference chaque Carte à son adresse associée dans le tableau de carte
{
	for (int i = 0; i < deck_cards_104; i++)
	{
		Card *my_Card = new Card(i+1); // On instancie dynamiquement une carte
		tab_Cards[i] = my_Card;		   // On dit a cette même carte qu'elle pointera vers tel adresse du tableau
	}
}
Deck::~Deck() // Destructeur necessaire pour detruire toutes les cartes créé dynamiquement, TRES IMPORTANT car il permet d'éviter un stackoverflow
{
	for (int i = 0; i < deck_cards_104; i++)
	{
		delete tab_Cards[i];
		tab_Cards[i] = nullptr;
	}
}
#pragma endregion 

Card & Deck::Get_Card(int card_Number) // Renvoie une carte du paquet
{ 
	if(card_Number < deck_cards_104 && card_Number >= 0) return *tab_Cards[card_Number];
	else throw "Attention on essaye d'acceder a une carte inexistante ";
}

void Deck::Add_card_to_player(Player & my_player)
{
	int hand_counter = 0;
	for (int i = (deck_cards_104 -1) ; i > 0; --i) // On regarde toute les cartes du paquet et on va en soustraire jusqu'a 10 pour les ajouter dans la main du joueur
	{
		if ( (this->tab_Cards[i]->In_Deck() == true) && hand_counter < player_cards_10 )
		{
			my_player.Get_hand_player().Add_card(this->tab_Cards[i], hand_counter);
			hand_counter++;
		}
		else if (hand_counter == player_cards_10 ) break;
	}
}

void Deck::Add_card_to_row(Game_Board::Row & my_row)
{
	bool card_added = false;
	for (int i = (deck_cards_104 - 1); i > 0; --i) // On regarde toute les cartes du paquet 
	{
		if ((this->tab_Cards[i]->In_Deck() == true) ) // ON regarde celle qui restent dans le paquet
		{
			for (int j = 0; j < row_cards_6; j++) // On regarde les cartes dans la rangée
			{
				if (&my_row.Get_card(j) == nullptr) // ON ajoute les cartes dns l'espace de la rangée disponible
				{
					my_row.Add_card(this->tab_Cards[i],j);
					card_added = true;
					break;
				}
			}
			if (card_added == true) break;
		}
	}

}

void Deck::Mix_card()// Reprend les 104 cartes du jeux et les mellange
{
	srand(time(0));  // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	Card * tampon_deck_cards[104];
	for (int i = 0; i < deck_cards_104; i++) tampon_deck_cards[i] = nullptr; // On met toute les valeurs à 0 car par defaut les valeurs d'un tableau créé statiquement en C++ sont inconnue
	for (int i = 0; i < deck_cards_104; i++)
	{ 
		random_number = ((rand() % deck_cards_104) + 1);
		tampon_deck_cards[i] = tab_Cards[random_number - 1];
		for (int j = 0; j < deck_cards_104; j++)
		{
			if (tampon_deck_cards[i] == tampon_deck_cards[j] && (i != j))
			{
				--i;
				break;
			}
		 }
	}
	for (int i = 0; i < deck_cards_104; i++) tab_Cards[i] = tampon_deck_cards[i];
}
