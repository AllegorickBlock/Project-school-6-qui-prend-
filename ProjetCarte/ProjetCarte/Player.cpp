#include "stdafx.h"
#include "Player.h"

#pragma region Class : Player

#pragma region Constructor & Destructor

int mbr = 0;

Player::Player() 
{ 
	this->hand = new Player::Hand_Player();
	this->score = 0;
	this->number = mbr++;
	if (mbr == Const_Var::nmbr_Gamer) mbr = 0; // Lorsqu'on cree des tableaux de joeurs et de joueurs bot et humain, ils auront un nombre équivalenbt a l'objet de la classe mere 

} // On cree dynamiquement notre objet main apparent au joueur

Player::~Player() // Le destructeur va detruite l'instance dynamique cree par le constructeur
{
	delete this->hand;
	hand = nullptr;
}
#pragma endregion

#pragma region Functions : Get and Set

int Player::Get_number() { return this->number; }

int Player::Get_score() { return this->score; }

void Player::Set_card_selection(Card * my_card) { this->selection_card = my_card; }

Card * Player::Get_card_selection() { return this->selection_card; }

Player::Hand_Player& Player::Get_hand_player() { return *this->hand; }

#pragma endregion

#pragma region Functions : Add & Remove

void Player::Add_to_number_score(int beef_score) { this->score += beef_score; }

void Player::Remove_card_selection(Card * my_card) { this->selection_card = nullptr; }

#pragma endregion

#pragma region Functions : Sort

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

#pragma endregion

#pragma region Class : Player::Hand_Player

#pragma region Player::Hand_Player : Constructeur & Destructeur

Player::Hand_Player::Hand_Player() { } 

Player::Hand_Player::~Hand_Player() {} 

#pragma endregion

#pragma region Functions : Add & Remove

void Player::Hand_Player::Add_card(Card * my_card, int index) // ON DOIT FAIRE UN PASSAGE PAR REFERENCE OU SINON LE DECK NE SE VERRA PAS MODIFIE -> CAR COPIE
{
	player_cards[index] = my_card;
	player_cards[index]->Set_status(1);
}

void Player::Hand_Player::Remove_card(int index) { this->player_cards[index] = nullptr; }

#pragma endregion

#pragma region Functions : Get and Set 

bool Player::Hand_Player::Card_in_hand(int index) { return this->player_cards[index] != nullptr; }

Card& Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder a des cartes qui ne sont plus/pas dans la main du joueur
{
	if (card < Const_Var::nmbr_cards_in_Hand && card >= 0) return *player_cards[card];
}

#pragma endregion

#pragma endregion

#pragma region Class : Bot_Player

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
			this->Get_hand_player().Get_card_of_hand(random_number).Set_nbr_player(this->Get_number());
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
	Sort_asc(copy_number_diff); // Permet de faciliter la rechecherche a propos de la plus petite difference avec une rangeée

	for (int j = 0; j < Const_Var::nmbr_Rows; j++) // On regarde toutes differences calculées auparavant
	{
		if (copy_number_diff[j] > 0) // Cas ou on peut poser la carte car nous arrivons a la plus petite difference possible
		{
			for (int k = 0; k < Const_Var::nmbr_Rows; k++) // On regarde toutes les rangées pour voir a quelle rangée est attribué la plus petite difference
			{
				if (copy_number_diff[j] == (*this->Get_card_selection() - my_board.Get_row(k).Get_last_card())) // On va se concentrer sur notre rangée avec le calcul de la plus petite difference
				{
					if (my_board.Get_row(k).Get_nbr_cards_in() == Const_Var::nmbr_cards_in_Rows - 1)// si le nombre carte dans une rangée avant d'ajouter un carte est de 5 
					{
						for (int m = 0; m < Const_Var::nmbr_Gamer; m++) // On Regarde tout les jouers, et on va trouver celui qui joue actuellement pour lui faire prendre des points boeuf
						{
							if (this->Get_card_selection() == cards_selection[m])
							{
								this->Add_to_number_score(my_board.Get_row(k).Get_sum_number_beef());
								my_board.Get_row(k).Remove_all();
								my_board.Get_row(k).Add_card(cards_selection[m]);
							}
						}
						j = Const_Var::nmbr_Rows;
						k = Const_Var::nmbr_Rows;
					}
					else // Cas ou le nombre de rangée avant de poser la carte est moins de 5
					{
						for (int m = 0; m < Const_Var::nmbr_Gamer; m++) // On va juste ajouter notre carte dans la rangée
						{
							if (this->Get_card_selection() == cards_selection[m]) my_board.Get_row(k).Add_card(cards_selection[m]);
						}

						j = Const_Var::nmbr_Rows;
						k = Const_Var::nmbr_Rows;
					}
				}
			}
		}
		else if (j == (Const_Var::nmbr_Rows - 1)) // Si la carte a un nombre trop petit et ne peut être ajouté a aucune rangée
		{
			srand(time(0));
			int rand_number = ((rand() % Const_Var::nmbr_Rows));
			int index_player = 0;
			for (int m = 0; m < Const_Var::nmbr_Gamer; m++) // On va rechercher notre joueur a qui attribuer les points boeuf
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
#pragma endregion

#pragma region Class : Human_Player

void Human_Player::Pick_selection_card(Card * selection_cards[])
{
	int choice = 0;
	cout << "\n  choisi une carte C : ";

	while (true)
	{
		cin >> choice;
		if ( (choice > 0 && choice <= Const_Var::nmbr_cards_in_Hand) && this->Get_hand_player().Card_in_hand(choice-1) == true)// Si le joueur a tapé une entrée corecte
		{
			selection_cards[this->Get_number()] = &this->Get_hand_player().Get_card_of_hand((choice - 1)); 
			this->Get_hand_player().Get_card_of_hand(choice - 1).Set_nbr_player(this->Get_number());
			this->Get_hand_player().Remove_card((choice - 1));
			this->Set_card_selection(selection_cards[this->Get_number()]);
			break;
		}
		cout << "\nMauvaise entree, veuillez essayer a nouveau en entrant un chifre valide !\n\n";
	}
}

void Human_Player::Add_in_row(Game_Board & my_board, Card * card_selection[])
{
	int choice = 0;
	bool choice_is_correct = false;
	cout << "\n\n ~~~~~~~~~~~{ Joueur " << (this->Get_number() + 1) << " , choisie une rangée R : ";

	while (choice_is_correct == false)
	{
		cin >> choice;
		if ((choice - 1) >= 0 && (choice - 1) < Const_Var::nmbr_Rows)// Si le joueur a tapé une entrée corecte
		{
			choice_is_correct = true;
			if ((my_board.Get_row(choice - 1).Get_nbr_cards_in() < Const_Var::nmbr_cards_in_Rows - 1) && ( (*this->Get_card_selection() - my_board.Get_row(choice - 1).Get_last_card() ) > 0) )
			{											// Cas ou lorsqu'on pose une carte, la rangée n'est pas composée de 6 carte																		
														// ET que la difference de notre carte selectionné avec la derniere carte de cette ra,gée est superieur a 0
				for (int m = 0; m < Const_Var::nmbr_Gamer; m++)	//On va chercher pour effacer notre carte selectionnée dans notre tableau de cartes selectionné pour ce tour
				{
					if (this->Get_card_selection() == card_selection[m])
					{
						my_board.Get_row(choice - 1).Add_card(card_selection[m]);
						break;
					}
				}
			}
			else
			{
				for (int m = 0; m < Const_Var::nmbr_Gamer; m++)	//On va chercher pour effacer notre carte selectionnée dans notre tableau de cartes selectionné pour ce tour
				{
					if (this->Get_card_selection() == card_selection[m])
					{
						this->Add_to_number_score(my_board.Get_row(choice - 1).Get_sum_number_beef());
						my_board.Get_row(choice - 1).Remove_all();
						my_board.Get_row(choice - 1).Add_card(card_selection[m]);
						break;
					}
				}
			}	
		}
		cout << "\nMauvaise entrée, veuillez essayer a nouveau en entrant un chifre valide !\n\n";
	}
}

#pragma endregion









