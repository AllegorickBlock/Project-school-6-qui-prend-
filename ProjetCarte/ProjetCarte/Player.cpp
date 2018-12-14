#include "stdafx.h"
#include "Player.h"

int tampon_nb_players = 0;

#pragma region Classe Player

#pragma region Player : Constructeur & Destructeur
Player::Player() 
{ 
	this->nb_Player = tampon_nb_players++;
	this->hand = new Player::Hand_Player();
	this->score = 0;

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

void Player::Show_hand()
{
	cout << "\n Joueur " << this->nb_Player << " : ";
	for (int j = 0; j < Const_Var::nmbr_cards_in_Hand; j++)
	{
		if (&this->Get_hand_player().Get_card_of_hand(j) != nullptr)	Game::Show_card(this->Get_hand_player().Get_card_of_hand(j));
	}
}

int Player::Get_score()
{
	return this->score;
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


void Player::Hand_Player::Remove_card(int & index)	{	this->player_Cards[index] = nullptr;	}

bool Player::Hand_Player::Card_in_hand(int & index)	{	return this->player_Cards[index] != nullptr;	}

Card& Player::Hand_Player::Get_card_of_hand(int card) // Gere les exceptions dans lesquelles on veut acceder a des cartes qui ne sont plus/pas dans la main du joueur
{
	if (card < Const_Var::nmbr_cards_in_Hand && card >= 0) return *player_Cards[card];
}



#pragma endregion



///////////////// METHODES DE CLASSE ENFANT 


void Human_Player::Choose_card_for_turn(Card * cards_selec[])
{
	cout << "\n ~~~~~~  ~~~~~~ Choisissez une carte Joueur " << this->nb_Player << " ~~~~~~  ~~~~~~ \n";
	for (int j = 0; j < Const_Var::nmbr_cards_in_Hand; j++)
	{
		if (&this->Get_hand_player().Get_card_of_hand(j) != nullptr)
		{
			if (&this->Get_hand_player().Get_card_of_hand(j) != nullptr)
			{
				cout << (j + 1) << ".";
				Game::Show_card(this->Get_hand_player().Get_card_of_hand(j));
			}
		}
	}
	int choix;
	cout << "\n ~~~~~~  ~~~~~~ Choisissez botre carte : ";
	cin >> choix;

	switch (choix)
	{
	case 1: break;
	case 2: break;
	case 3: break;
	case 4: break;
	case 5: break;
	case 6: break;
	case 7: break;
	case 8: break;
	case 9: break;
	case 10: break;

	default:
	}


}

void Bot_Player::Choose_card_for_turn(Card * cards_selec[])
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents
	int random_number = 0;
	int random_number_card_selec = 0;

	random_number = ((rand() % Const_Var::nmbr_cards_in_Hand));

	for (bool card_choosed = false; card_choosed != true;)	 // On cherche apres une carte de notre main à poser
	{								 
		if ( (&this->Get_hand_player().Get_card_of_hand(random_number)) != nullptr ) // Si on recupere une carte de la main qui existe 
		{
			for (; card_choosed != true;)	 // On cherche apres un emplacement de la selction de carte du tour, surlequel on peut mettre notre carte
			{
				random_number_card_selec = ((rand() % Const_Var::nmbr_Gamer));
				if(cards_selec[random_number_card_selec] == nullptr) // Si l'emplacement est vide, on va le remplir
				{
					cards_selec[random_number_card_selec] = &this->Get_hand_player().Get_card_of_hand(random_number); 
					this->Get_hand_player().Remove_card(random_number);
					card_choosed = true;
				}
			}
		}
	}
}
