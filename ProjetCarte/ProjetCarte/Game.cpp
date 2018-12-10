#include "stdafx.h"
#include "Game.h"



#pragma region Game

#pragma region Game : Constructeur & Destructeur


int number_turn;
Game::Game()
{
	Player les_joueurs[Const_Var::nmbr_Gamer];
	Game_Board plateau;
	Deck my_deck;

	number_turn = 0;

	cout << " \n\n\n\n Deck non melang� : \n\n";
	Show_deck(my_deck);

	my_deck.Mix_card();

	cout << " \n\n\n\n Deck melang� : \n\n";
	Show_deck(my_deck);

	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // ajout des cartes dans les mains des joueurs et des rang�es
	{
		my_deck.Add_card_to_player(les_joueurs[i]);
		my_deck.Add_card_to_row(plateau.Get_row(i));
	}

	Show_hand(les_joueurs);

	Show_row(plateau);

	cout << "\n\n\n\n Carte restante dans le Paquets \n\n";

	Show_deck(my_deck);

	Turn my_Turn(les_joueurs,plateau,my_deck);

	Show_deck(my_deck);
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

inline void Game::Show_deck(Deck &my_deck)
{
	for (int j = 0; j < Const_Var::nmbr_deck_cards; j++)
	{
		if (my_deck.Get_Card(j).In_Deck())
		{
			cout << "[" << my_deck.Get_Card(j).Get_number() << "|" << my_deck.Get_Card(j).Get_beef_number();
			Show_beef_symbol();
			cout << "]  ";
			if ((j + 1) % 10 == 0) cout << "\n";
		}
	}
}

inline void Game::Show_hand(Player les_joueurs[])
{
	cout << "\n\n\n Carte des joueurs : \n";
	for (int i = 0; i < Const_Var::nmbr_Gamer ; i++)
	{
		cout << "\n\n Joueur " << i << endl;
		for (int j = 0; j < Const_Var::nmbr_cards_in_Hand; j++)
		{
			if (les_joueurs[i].Get_hand_player().Card_in_hand(j) == true)
			{
				cout << "[" << les_joueurs[i].Get_hand_player().Get_card_of_hand(j).Get_number() << "|" << les_joueurs[i].Get_hand_player().Get_card_of_hand(j).Get_beef_number();
				Show_beef_symbol();
				cout << "]  ";
			}
		}
	}
}

inline void Game::Show_row(Game_Board & plateau)
{
	cout << "\n\n\n Carte des rangees : \n";
	for (int i = 0; i < 4; i++)
	{
		cout << "\n R" << i << ":\t";
		for (int j = 0; j < 6; j++)
		{
			if (&plateau.Get_row(i).Get_card(j) != nullptr)
			{
				cout << "[" << plateau.Get_row(i).Get_card(j).Get_number() << "|" << plateau.Get_row(i).Get_card(j).Get_beef_number();
				Show_beef_symbol();
				cout << "]  ";
			}
			else break;
		}
	}
}

inline void Game::Show_cards_selection(Card * cards_selection[])
{
	cout << "\n\t Cartes selectionnes :  ";
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
	{
		cout << "[" << cards_selection[i]->Get_number() << "|" << cards_selection[i]->Get_beef_number();
		Show_beef_symbol();
		cout << "]  ";
	}
	cout << "\n" ;
}

inline void Game::Show_player_scores(Player my_players[])
{
	cout << "\n\t-- Scores des joueurs --";
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
	{
		cout << "\nJoueur " << i << " : " << my_players[i].Get_score();
	}
	cout << "\n\n";
}

#pragma endregion

#pragma region Game : Fonctions Sort_asc

inline void Game::Sort_asc(Card * my_tab[], int index_players[]) // tri dans l'ordre croissant
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
		index_players[index] = i; // on stoque l'index du player en rapport avec l'index de sa carte mise dans selection_cards, on ne pers pas le lien ainsi
	}
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) my_tab[i] = my_copy_tab[i];
}

inline void Game::Sort_asc(int my_tab[])
{
	int my_copy_tab[Const_Var::nmbr_Gamer];
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // on regarde le tableau de carte pris en parameter
	{
		int index = 0;
		for (int j = 0; j < Const_Var::nmbr_Gamer; j++) // On regarde toute les carte de my_tab
		{
			if (my_tab[i] > my_tab[j]) index++; // on regarde les difference de notre carte[i] avec les tout les autres cartes[j]
		}
		my_copy_tab[index] = my_tab[i]; // ON assigne dans l'ordre les ellements de my_tab dans my_copy_tab
	}
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) my_tab[i] = my_copy_tab[i];
}

#pragma endregion

#pragma region Game : Usefull Fonctions

inline void Game::Pick_card_random(Card * cards_selec[], Player les_joueurs[], int index_players[])
{
	srand(time(0)); // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents
	int random_number = 0;
	for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
	{
		random_number = ((rand() % Const_Var::nmbr_cards_in_Hand));
		index_players[i] = i;
		cards_selec[i] = &les_joueurs[i].Get_hand_player().Get_card_of_hand(random_number); // On prend toutes les cartes selectionn� au hasard par notre joueurs lors de ce tour
		les_joueurs[i].Get_hand_player().Remove_card(random_number);
	}
}

inline void Game::Look_add_in_row(Game_Board & plateau, Card * cards_selection[], Player my_players[], int index_players[])
{
	int copy_number_diff[Const_Var::nmbr_Gamer];

	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) // On regarde toute les differences des nombres de la carte selectionn� du joueur avec celles des rang�es
	{
		for (int j = 0; j < Const_Var::nmbr_Gamer; j++)copy_number_diff[j] = (*cards_selection[i] - plateau.Get_row(j).Get_last_card());
		// On stoque toute les differences de notre cards_selection[i] avec toute les cartes des rang�es
		int lower_diff = 0;
		bool card_added_in_ronw = false;
		Sort_asc(copy_number_diff); // On met dans l'ordre du plus petit au plus grand notre liste des differences math�matiques obtenues
		for (int j = 0; j < Const_Var::nmbr_Rows; j++)
		{
			if (copy_number_diff[j] > 0) // Si nous arrivons a notre premiere differences > 0, Cas ou on peut poser la carte
			{
				lower_diff = copy_number_diff[j]; 
				for (int k = 0; k < Const_Var::nmbr_Rows; k++) // On va comparer chaque rang�e pour voir ou poser notre carte selectionn�e
				{
					if (lower_diff == (*cards_selection[i] - plateau.Get_row(k).Get_last_card())) // Si nous recuperons la difference aparent� � la bonne rang�, on va ajouter notre carte selectionn�e dans la rang�e
					{
						plateau.Get_row(k).Add_card(cards_selection[i]); // Si il existe encore un emplacement de la rang�e choisie
						j = Const_Var::nmbr_Rows;
						card_added_in_ronw = true;
						break;
					}
					if (card_added_in_ronw == true) break;
				}
			}
			else if( j == (Const_Var::nmbr_Rows - 1) ) // Si la carte a un nombre trop petit et ne peut �tre ajout� a aucune rang�e
			{
				srand(time(0));
				int rand_number = ((rand() % Const_Var::nmbr_Rows));
				int index_player = 0;
				for (int k = 0; k < Const_Var::nmbr_Gamer; k++) // On regarde chaque joueurs
				{
					if (k == index_players[i]) // Lorsqu'on recupere l'index du joueur auquel apartient la carte de cards_selection[] en jeu
					{
						cards_selection[i];
						my_players[k].Add_to_number_score(plateau.Get_row(rand_number).Get_sum_number_beef());
						plateau.Get_row(rand_number).Remove_all();
						plateau.Get_row(rand_number).Add_card(cards_selection[i]);
					}
				}
			}
		}
	}
}

#pragma endregion

#pragma endregion

#pragma region Turn

#pragma region Turn : Constructeur & Destructeur

Game::Turn::Turn(Player les_joueurs[], Game_Board & plateau, Deck & my_deck)
{
	number_turn++;
	cout << "\n\n\n\n\t----|Tour " << number_turn << "|----";

	Pick_card_random(cards_selection, les_joueurs,this->index_player_selection);

	Sort_asc(cards_selection, this->index_player_selection); // L'index de cartes dans cards_selection ne va plus corespondre a l'index du joueur

	Show_cards_selection(cards_selection);

	Look_add_in_row(plateau, cards_selection, les_joueurs, this->index_player_selection);

	Show_hand(les_joueurs);
	Show_row(plateau);
	Show_player_scores(les_joueurs);

	for (int i = 0; i < Const_Var::nmbr_Gamer; i++) cards_selection[i] = nullptr; // A la fin du tour il n'existe plus de carte selectionn� par les joueurs
}


Game::Turn:: ~Turn()
{

}

#pragma endregion

#pragma endregion



