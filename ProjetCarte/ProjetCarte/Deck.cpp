#include "stdafx.h"
#include "Deck.h"

#pragma region Class : Deck

#pragma region Constructor & Destructor

Deck::Deck()  // Constructeur par defaut qui reference chaque Carte à son adresse associée dans le tableau de carte
{
	for (int i = 0; i < Const_Var::nmbr_deck_cards; i++)
	{
		Card *my_Card = new Card(i + 1); // On instancie dynamiquement une carte
		tab_Cards[i] = my_Card;		   // On dit a cette même carte qu'elle pointera vers tel adresse du tableau
	}
}
Deck::~Deck() // Destructeur necessaire pour detruire toutes les cartes créé dynamiquement, TRES IMPORTANT car il permet d'éviter un stackoverflow
{
	for (int i = 0; i < Const_Var::nmbr_deck_cards; i++)
	{
		delete tab_Cards[i];
		tab_Cards[i] = nullptr;
	}
}
#pragma endregion 

#pragma region Functions

Card & Deck::Get_Card(int card_Number) // Renvoie une carte du paquet
{
	if (card_Number < Const_Var::nmbr_deck_cards && card_Number >= 0) return *tab_Cards[card_Number];
	else throw "Attention on essaye d'acceder a une carte inexistante ";
}

void Deck::Add_card_to_player(Player * my_player)
{
	int hand_counter = 0;
	for (int i = (Const_Var::nmbr_deck_cards - 1); i > 0; --i)	// On regarde toute les cartes du paquet deck de cartes et on va en soustraire jusqu'a 10 
	{															// pour les ajouter dans la main du joueur
		if ((this->tab_Cards[i]->In_deck() == true) && hand_counter < Const_Var::nmbr_cards_in_Hand)// On verifie bien que notre carte proviens du paquet
		{																							// On regarde di notre main est totallement remplie (hand_counter)
			my_player->Get_hand_player().Add_card(this->tab_Cards[i], hand_counter);
			hand_counter++;
		}
		else if (hand_counter == Const_Var::nmbr_cards_in_Hand) break;
	}
}

void Deck::Add_card_to_row(Game_Board::Row & my_row)
{
	for (int i = (Const_Var::nmbr_deck_cards - 1); i > 0; --i) // On regarde toute les cartes du paquet 
	{
		if ((this->tab_Cards[i]->In_deck() == true)) // On regarde celles qui restents dans le paquet
		{
			my_row.Add_card(this->tab_Cards[i]); // Et hop, on ajoute notre carte de notre deck a notre rangée
			break;
		}
	}
}

void Deck::Mix_card()// Reprend les 104 cartes du jeux et les mellange
{
	srand(time(0));  // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents a chaque compilation
	int random_number;
	Card * tampon_deck_cards[Const_Var::nmbr_deck_cards];
	for (int i = 0; i < Const_Var::nmbr_deck_cards; i++) tampon_deck_cards[i] = nullptr;	// On met toute les valeurs des pointeurs à nullptr car par defaut les
	for (int i = 0; i < Const_Var::nmbr_deck_cards; i++)									// valeurs d'un tableau créé statiquement en C++ sont inconnue
	{
		random_number = ((rand() % Const_Var::nmbr_deck_cards) + 1);
		tampon_deck_cards[i] = tab_Cards[random_number - 1];
		for (int j = 0; j < Const_Var::nmbr_deck_cards; j++)
		{
			if (tampon_deck_cards[i] == tampon_deck_cards[j] && (i != j))	// Si le numero assigné aléatoirement existe deja dans le paquet 
			{																// on recommence pour en avoir un different, et avoir melange de carte coherent
				--i;
				break;
			}
		}
	}
	for (int i = 0; i < Const_Var::nmbr_deck_cards; i++) tab_Cards[i] = tampon_deck_cards[i];	// On assigne les cartes melangées dans notre tampon 
}																								// a notre veritable paquet de carte du jeu

void Deck::Recover_cards_and_mix(Player * my_player[], Game_Board * the_board)
{
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // on regarde pour chaque joueur
	{															
		for (int j = 0; j < Const_Var::nmbr_cards_in_Hand; j++) my_player[i]->Get_hand_player().Remove_card(j); // on efface toute les cartes dans la main du joueur
	}
	for (int i = 0; i < Const_Var::nmbr_Rows; i++) the_board->game_rows[i]->Remove_all();
	for (int i = 0; i < Const_Var::nmbr_deck_cards; i++)this->tab_Cards[i]->Set_status(0);
	this->Mix_card();
}

#pragma endregion

#pragma endregion




