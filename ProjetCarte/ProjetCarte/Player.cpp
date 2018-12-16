#include "stdafx.h"
#include "Player.h"

#pragma region Classe Player

#pragma region Player : Constructeur & Destructeur

int mbr = 0;

Player::Player() 
{ 
	this->hand = new Player::Hand_Player();
	this->score = 0;
	this->number = mbr++;

} // On cree dynamiquement notre objet main apparente au joueur

Player::~Player() // Le destructeur va detruite l'instance dynamique cree par le constructeur
{
	delete this->hand;
	hand = nullptr;
}
#pragma endregion

Player::Hand_Player& Player::Get_hand_player() { return *this->hand; }

void Player::Add_to_number_score(int beef_score)
{
	this->score += beef_score;
}

int Player::Get_score()
{
	return this->score;
}

void Player::Pick_selection_card(Card * selection_cards[])
{
}

void Player::Add_in_row(Game_Board & my_board, Card * card_selection[])
{
}


void Player::Set_card_selection(Card * my_card)
{
	this->selection_card = my_card;
}

void Player::Remove_card_selection(Card * my_card)
{
	this->selection_card = nullptr;
}

Card * Player::Get_card_selection()
{
	return this->selection_card;
}

int Player::Get_number()
{
	return this->number;
}

inline void Player::Sort_asc(int my_tab[])
{
	int my_copy_tab[Const_Var::nmbr_Gamer];
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // on regarde le tableau de carte pris en parameter
	{												// On regarde toute les carte de my_tab
		int index = 0;								// on regarde les difference de notre carte[i] avec les tout les autres cartes[j]
		for (int j = 0; j < Const_Var::nmbr_Gamer; j++) if (my_tab[i] > my_tab[j]) index++;
		my_copy_tab[index] = my_tab[i]; // ON assigne dans l'ordre les ellements de my_tab dans my_copy_tab
	}
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) my_tab[i] = my_copy_tab[i];
}




#pragma endregion

#pragma region Classe Player::Hand_Player

#pragma region Player::Hand_Player : Constructeur & Destructeur
Player::Hand_Player::Hand_Player() { } 

Player::Hand_Player::~Hand_Player() {} 

#pragma endregion

void Player::Hand_Player::Add_card(Card * my_card, int index) // ON DOIT FAIRE UN PASSAGE PAR REFERENCE OU SINON LE DECK NE SE VERRA PAS MODIFIE -> CAR COPIE
{
	player_Cards[index] = my_card;
	player_Cards[index]->Set_status(1);
}


void Player::Hand_Player::Remove_card(int index)	{	this->player_Cards[index] = nullptr;	}

bool Player::Hand_Player::Card_in_hand(int index)	{	return this->player_Cards[index] != nullptr;	}

Card& Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder a des cartes qui ne sont plus/pas dans la main du joueur
{
	if (card < Const_Var::nmbr_cards_in_Hand && card >= 0) return *player_Cards[card];
}

#pragma endregion

void Bot_Player::Pick_selection_card(Card * selection_cards[])
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents
	int random_number = 0;
	bool choice_is_correct = false;
	while (choice_is_correct == false) // On fait une boucle pour arriver a choisir aleatoirement une carte qui existe
	{
		random_number = ((rand() % Const_Var::nmbr_cards_in_Hand));
		if (&this->Get_hand_player().Get_card_of_hand(random_number) != nullptr) // Si l'objet Card que l'on recupere existe bien 
		{
			selection_cards[this->Get_number()] = &this->Get_hand_player().Get_card_of_hand(random_number); // On choisi cette carte pour jouer
			this->Get_hand_player().Remove_card(random_number);
			this->Set_card_selection(selection_cards[this->Get_number()]);
			choice_is_correct = true;
			break;
		}
	}
}

void Bot_Player::Add_in_row(Game_Board & my_board, Card * cards_selection[])
{
	int copy_number_diff[Const_Var::nmbr_Gamer];
	for (int j = 0; j < Const_Var::nmbr_Gamer; j++)	copy_number_diff[j] = (*this->Get_card_selection() - my_board.Get_row(j).Get_last_card());
	// On stoque toute les differences de notre cards_selection[i] avec toute les cartes des rangées

	int lower_diff = 0;
	Sort_asc(copy_number_diff); // Permet de faciliter la rechecherche a propos de la rangée 

	for (int j = 0; j < Const_Var::nmbr_Rows; j++) // On regarde toutes les rangées
	{
		if (copy_number_diff[j] > 0) // Si nous arrivons a notre premiere differences > 0, Cas ou on peut poser la carte
		{
			for (int k = 0; k < Const_Var::nmbr_Rows && copy_number_diff[j] == (*this->Get_card_selection() - my_board.Get_row(k).Get_last_card()); k++) 
			{	// On va recomparer chaque rangée pour voir leurs derniere carte et les comparer avec notre carte pour savoir ou la poser 
				
				if (my_board.Get_row(k).Get_nbr_cards_in() == Const_Var::nmbr_cards_in_Rows - 1)// si le nombre carte dans une rangée avant d'ajouter un carte est de 5
				{
					for (int m = 0; m < Const_Var::nmbr_Gamer && this->Get_card_selection() == cards_selection[m]; m++) // On 
					{
						this->Add_to_number_score(my_board.Get_row(k).Get_sum_number_beef());

						my_board.Get_row(k).Remove_all();


						my_board.Get_row(k).Add_card(cards_selection[m]);
					}
					
				}
				j = Const_Var::nmbr_Rows;
				k = Const_Var::nmbr_Rows;
			}
		}
		else if (j == (Const_Var::nmbr_Rows - 1)) // Si la carte a un nombre trop petit et ne peut être ajouté a aucune rangée
		{
			srand(time(0));
			int rand_number = ((rand() % Const_Var::nmbr_Rows));
			int index_player = 0;
			for (int m = 0; m < Const_Var::nmbr_Gamer; m++)
			{
				if (this->Get_card_selection() == cards_selection[m])
				{
					this->Add_to_number_score(my_board.Get_row(rand_number).Get_sum_number_beef());
					my_board.Get_row(rand_number).Remove_all();
					my_board.Get_row(rand_number).Add_card(cards_selection[m]);
					break;
				}
			}
		}
	}
}






void Human_Player::Pick_selection_card(Card * selection_cards[])
{
	int choice = 0;
	bool choice_is_correct = false;
	cout << "\n\n ~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~ Joueur " << (this->Get_number() + 1)<< " , a toi de jouer ! ~~~~~~~~~~~ ~~~~~~~~~~~ ~~~~~~~~~~~";

	while (choice_is_correct == false)
	{
		cout << "\n\tChoix : ";
		cin >> choice;
		if(choice > 0 && choice <= 10)// Si le joueur a tapé une entrée corecte
		{
			if (this->Get_hand_player().Card_in_hand(choice) == true)
			{
				choice_is_correct = true;
				selection_cards[this->Get_number()] = &this->Get_hand_player().Get_card_of_hand((choice-1)); // On choisi cette carte pour jouer
				this->Get_hand_player().Remove_card((choice - 1));
				this->Set_card_selection(selection_cards[this->Get_number()]);
				choice_is_correct = true;
				break;
			}
		}
		cout << "\nMauvaise entrée, veuillez essayer a nouveau en entrant un chifre valide !\n\n";
	}
}

void Human_Player::Add_in_row(Game_Board & my_board, Card * card_selection[])
{
}
