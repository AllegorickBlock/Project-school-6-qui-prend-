#include "stdafx.h"
#include "Game.h"



#pragma region Game

#pragma region Game : Constructeur & Destructeur


int number_turn;
Game::Game()
{
	Bot_Player bot_1;
	Bot_Player bot_2;
	Bot_Player bot_3;
	Human_Player human_4;

	Player * les_joueurs[Const_Var::nmbr_Gamer];

	les_joueurs[0] = &bot_1;
	les_joueurs[1] = &bot_2;
	les_joueurs[2] = &bot_3;
	les_joueurs[3] = &human_4;
	Game_Board plateau;
	Deck my_deck;
	number_turn = 0;

	cout << " \n\n\t----Deck non melange ---- \n\n";
	Show_deck(my_deck);

	my_deck.Mix_card();

	cout << " \n\n\t---- Deck melange ---- \n\n";
	Show_deck(my_deck);

	// ajout des cartes dans les mains des joueurs et des rangées
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) my_deck.Add_card_to_player(les_joueurs[i]);
	for (int i = 0; i < Const_Var::nmbr_Rows; i++) my_deck.Add_card_to_row(plateau.Get_row(i));
	
	Show_hand(les_joueurs);

	Show_row(plateau);

	cout << "\n\n\n\n Carte restante dans le Paquets \n\n";

	Show_deck(my_deck);
	
	this->Start(les_joueurs, plateau, my_deck);
}

Game::~Game()
{
}

#pragma endregion

#pragma region Game : Show Functions

inline void Game::Show_beef_symbol()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Permet de passer au mode de translation de texte UTF16 pour indiquer les caracteres speciaux souhaite ( Voir doc : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2017 )
	wprintf(L"\x0222"); // Inscription en UTF16 du signe du zodiaque du taureau ( voir doc : https://www.compart.com/en/unicode/U+0222 ) 
	_setmode(_fileno(stdout), _O_TEXT);    // Necessaire pour eviter un plantage lors de la compilation : on reviens a l'etat normal de mode de translation de texte
}

inline void Game::Show_card(Card my_card)
{
	if (my_card.Get_number() < 10) cout << "[  " << my_card.Get_number() << "|" << my_card.Get_beef_number();
	else if (my_card.Get_number() < 100) cout << "[ " << my_card.Get_number() << "|" << my_card.Get_beef_number();
	else cout << "[" << my_card.Get_number() << "|" << my_card.Get_beef_number();
	Show_beef_symbol();
	cout << "]  ";
}

inline void Game::Show_deck(Deck &my_deck)
{
	cout << "\n\n---- Carte dans deck ---- \n";
	for (int j = 0; j < Const_Var::nmbr_deck_cards; j++)
	{
		if (my_deck.Get_Card(j).In_Deck()) Show_card(my_deck.Get_Card(j));
		if ((j + 1) % 10 == 0) cout << "\n";
	}
}

inline void Game::Show_hand(Player * les_joueurs[])
{
	cout << "\n\n---- Carte des joueurs ---- ";
	for (int i = 0; i < Const_Var::nmbr_Gamer ; i++)
	{
		cout << "\n Joueur " << (i+1) << " : ";
		for (int j = 0; j < Const_Var::nmbr_cards_in_Hand; j++)
		{
			if (&les_joueurs[i]->Get_hand_player().Get_card_of_hand(j) != nullptr)
			{
				cout << (j + 1) << ".";
				Show_card(les_joueurs[i]->Get_hand_player().Get_card_of_hand(j));
			}
		}
	}
}

inline void Game::Show_row(Game_Board & plateau)
{
	cout << "\n\n---- Carte des rangees ---- ";
	for (int i = 0; i < Const_Var::nmbr_Rows; i++)
	{
		cout << "\n R" << (i+1) << ":\t";
		for (int j = 0; j < Const_Var::nmbr_cards_in_Rows; j++)
		{
			if (&plateau.Get_row(i).Get_card(j) != nullptr)	Show_card(plateau.Get_row(i).Get_card(j));
			else break;
		}
	}
}

inline void Game::Show_cards_selection(Card * cards_selection[], Player * my_players[])
{
	cout << "\n\n---- Cartes selectionnes ---- \n";
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
	{
		cout << "   " ;
		Show_card(*cards_selection[i]);
		for (int m = 0; m < Const_Var::nmbr_Gamer; m++)
		{
			if (my_players[m]->Get_card_selection() == cards_selection[i])
			{
				cout << ": J" << (my_players[m]->Get_number() + 1) << "   ";
			}
		}
		
	}
}

inline void Game::Show_player_scores(Player * my_players[])
{
	cout << "\n\n------> Scores des joueurs <------";
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++)		cout << "\nJoueur " << (i+1) << " : " << my_players[i]->Get_score();
}

#pragma endregion

#pragma region Game : Fonctions Sort_asc

inline void Game::Sort_asc(Card * my_tab[]) // tri dans l'ordre croissant
{
	Card * my_copy_tab[Const_Var::nmbr_Gamer];
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // on regarde le tableau de carte pris en parametere
	{
		int index = 0;
		for (int j = 0; j < Const_Var::nmbr_Gamer; j++) // On regarde toute les carte de my_tab
		{
			if (my_tab[i]->Get_number() > my_tab[j]->Get_number()) index++; // on regarde les difference de notre carte[i] avec les tout les autres cartes[j]
		}
		my_copy_tab[index] = my_tab[i]; // ON assigne dans l'ordre les ellements de my_tab dans my_copy_tab
	}
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) my_tab[i] = my_copy_tab[i];
}

inline void Game::Sort_asc(int my_tab[])
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

#pragma region Game : Usefull Fonctions

inline void Game::Pick_card_random(Card * cards_selec[], Player les_joueurs[])
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents
	int random_number = 0;
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
	{
		random_number = ((rand() % Const_Var::nmbr_cards_in_Hand));
		if (&les_joueurs[i].Get_hand_player().Get_card_of_hand(random_number) != nullptr)
		{
			cards_selec[i] = &les_joueurs[i].Get_hand_player().Get_card_of_hand(random_number); // On prend toutes les cartes selectionné au hasard par notre joueurs lors de ce tour
			les_joueurs[i].Get_hand_player().Remove_card(random_number);
			les_joueurs[i].Set_card_selection(cards_selec[i]);
		}
		else i--;
	}
}

inline void Game::Look_add_in_row(Game_Board & plateau, Card * cards_selection[], Player * my_players[])
{
	int copy_number_diff[Const_Var::nmbr_Gamer];

	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // On regarde toute les differences des nombres de la carte selectionné du joueur avec celles des rangées
	{
		for (int j = 0; j < Const_Var::nmbr_Gamer; j++)copy_number_diff[j] = (*cards_selection[i] - plateau.Get_row(j).Get_last_card());
		// On stoque toute les differences de notre cards_selection[i] avec toute les cartes des rangées
		int lower_diff = 0;
		bool card_added_in_row = false;
		Sort_asc(copy_number_diff); // On met dans l'ordre du plus petit au plus grand notre liste des differences mathématiques obtenues
		for (int j = 0; j < Const_Var::nmbr_Rows; j++)
		{
			if (copy_number_diff[j] > 0) // Si nous arrivons a notre premiere differences > 0, Cas ou on peut poser la carte
			{
				lower_diff = copy_number_diff[j]; 
				for (int k = 0; k < Const_Var::nmbr_Rows; k++) // On va comparer chaque rangée pour voir ou poser notre carte selectionnée
				{
					if (lower_diff == (*cards_selection[i] - plateau.Get_row(k).Get_last_card())) // Si nous recuperons la difference aparenté à la bonne rangé, on va ajouter notre carte selectionnée dans la rangée
					{
						if (plateau.Get_row(k).Get_nbr_cards_in() == Const_Var::nmbr_cards_in_Rows - 1) // si le nombre carte dans une rangée avant d'ajouter un carte est de 5
						{
							for (int m = 0; m < Const_Var::nmbr_Gamer; m++)
							{
								if (my_players[m]->Get_card_selection() == cards_selection[i])
								{
									my_players[m]->Add_to_number_score(plateau.Get_row(k).Get_sum_number_beef());
								}
							}
							plateau.Get_row(k).Remove_all();
						}
						plateau.Get_row(k).Add_card(cards_selection[i]);
						j = Const_Var::nmbr_Rows;
						card_added_in_row = true;
						break;
					}
					if (card_added_in_row == true) break;
				}
			}
			else if( j == (Const_Var::nmbr_Rows - 1) ) // Si la carte a un nombre trop petit et ne peut être ajouté a aucune rangée
			{
				srand(time(0));
				int rand_number = ((rand() % Const_Var::nmbr_Rows));
				int index_player = 0;
				cards_selection[i];
				for (int m = 0; m < Const_Var::nmbr_Gamer; m++)
				{
					if (my_players[m]->Get_card_selection() == cards_selection[i])
					{
						my_players[m]->Add_to_number_score(plateau.Get_row(rand_number).Get_sum_number_beef());
					}
				}
				plateau.Get_row(rand_number).Remove_all();
				plateau.Get_row(rand_number).Add_card(cards_selection[i]);
			}
		}
	}
}

inline void Game::Start(Player * les_joueurs[], Game_Board & plateau, Deck & my_deck)
{
	for (this->end = false; end != true; )
	{
		for (int i = 0; i < Const_Var::nmbr_cards_in_Hand && (end == false); i++)
		{
			Turn my_Turn(les_joueurs, plateau, my_deck);
			for (int j = 0; j < Const_Var::nmbr_Gamer; j++)
			{
				if (les_joueurs[j]->Get_score() >= 66)
				{
					this->end = true;
					my_deck.Recover_cards_and_mix(les_joueurs, &plateau);
					
					break;
					
				}
			}
		}
		my_deck.Recover_cards_and_mix(les_joueurs, &plateau);
		for (int i = 0; i < Const_Var::nmbr_Gamer; i++)		my_deck.Add_card_to_player(les_joueurs[i]);
		for (int i = 0; i < Const_Var::nmbr_Rows; i++)	my_deck.Add_card_to_row(plateau.Get_row(i));
		cout << "\n\n\ndTest" << endl;
	}
}

#pragma endregion

#pragma endregion

#pragma region Turn

#pragma region Turn : Constructeur & Destructeur

Game::Turn::Turn(Player * les_joueurs[], Game_Board & plateau, Deck & my_deck)
{
	number_turn++;
	cout << "\n\n--------------------------------------------{Tour " << number_turn << "}--------------------------------------------";

	Show_row(plateau);

	Show_hand(les_joueurs);
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) les_joueurs[i]->Pick_selection_card(this->cards_selection);
	//Pick_card_random(cards_selection, les_joueurs);

	Sort_asc(cards_selection); // L'index de cartes dans cards_selection ne va plus corespondre a l'index du joueur

	Show_cards_selection(cards_selection, les_joueurs);

	Look_add_in_row(plateau, cards_selection, les_joueurs);

	Show_row(plateau);
	Show_player_scores(les_joueurs);

	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) cards_selection[i] = nullptr; // A la fin du tour il n'existe plus de carte selectionné par les joueurs
}


Game::Turn:: ~Turn()
{

}

#pragma endregion

#pragma endregion



