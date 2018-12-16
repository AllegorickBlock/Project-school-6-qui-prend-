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
		if (&this->Get_hand_player().Get_card_of_hand(random_number) != nullptr) // Si l'objet Card que l'on recupereexiste bien 
		{
			selection_cards[this->Get_number()] = &this->Get_hand_player().Get_card_of_hand(random_number); // On choisi cette carte pour jouer
			this->Get_hand_player().Remove_card(random_number);
			this->Set_card_selection(selection_cards[this->Get_number()]);
			choice_is_correct = true;
			break;
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
