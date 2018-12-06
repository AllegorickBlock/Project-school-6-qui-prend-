#include "stdafx.h"
#include "Game.h"

#pragma region Game

#pragma region Game : Constructeur & Destructeur


int number_turn;

Game::Game(Player les_joueurs[], Game_Board& plateau, Deck& my_deck)
{

	number_turn = 0;

	cout << " \n\n\n\n Deck non melangé : \n\n";
	Show_deck(my_deck);

	my_deck.Mix_card();

	cout << " \n\n\n\n Deck melangé : \n\n";
	Show_deck(my_deck);

	for (int i = 0; i < number_Gamer; i++) // ajout des cartes dans les mains des joueurs et des rangées
	{
		my_deck.Add_card_to_player(les_joueurs[i]);
		my_deck.Add_card_to_row(plateau.Get_row(i));
	}

	Show_hand(les_joueurs);

	Show_row(plateau);

	cout << "\n\n\n\n Carte restante dans le Paquets \n\n";

	Show_deck(my_deck);


	Turn my_Turn(les_joueurs,plateau,my_deck);

}



Game::~Game()
{
}

#pragma endregion

#pragma region Show Functions

inline void Game::Show_beef_symbol()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Permet de passer au mode de translation de texte UTF16 pour indiquer les caracteres speciaux souhaite ( Voir doc : https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2017 )
	wprintf(L"\x0222"); // Inscription en UTF16 du signe du zodiaque du taureau ( voir doc : https://www.compart.com/en/unicode/U+0222 ) 
	_setmode(_fileno(stdout), _O_TEXT);    // Necessaire pour eviter un plantage lors de la compilation : on reviens a l'etat normal de mode de translation de texte
}

inline void Game::Show_deck(Deck &my_deck)
{
	for (int j = 0; j < 104; j++)
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

inline void Game::Show_hand(Player les_joueurs[4])
{
	cout << "\n\n\n Carte des joueurs : \n";
	for (int i = 0; i < 4; i++)
	{
		cout << "\n\n Joueur " << i << endl;
		for (int j = 0; j < 10; j++)
		{
			cout << "[" << les_joueurs[i].Get_hand_player().Get_card_of_hand(j).Get_number() << "|" << les_joueurs[i].Get_hand_player().Get_card_of_hand(j).Get_beef_number();
			Show_beef_symbol();
			cout << "]  ";
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


#pragma endregion

#pragma endregion



#pragma region Turn

Game::Turn::Turn(Player les_joueurs[], Game_Board & plateau, Deck & my_deck)
{
	
	number_turn++;
	cout << "\n\n\n\n\t----|Tour " << number_turn << "|----";
	srand(time(0));  // Prend un temps random comme valeur, permet de s'assurer d'avoir des chifres differents
	int random_number = 0;
	for (int i = 0; i < number_Gamer ; i++)
	{
		random_number = ((rand() % nbr_hand_cards) );
		cards_selection[i] = &les_joueurs[i].Get_hand_player().Get_card_of_hand(random_number); // On prend toutes les cartes selectionné au hasard par notre joueurs lors de ce tour
	}

	Sort_asc(cards_selection); 
	cout << "\n\t Cartes selectionnées : ";
	for (int i = 0; i < 4; i++)
	{
		cout << "[" << cards_selection[i]->Get_number() << "|" << cards_selection[i]->Get_beef_number();
		Show_beef_symbol();
		cout << "]  ";
	}

	int copy_number_diff[4];
	

	for (int i = 0; i < number_Gamer; i++) // On regarde toute les differences des nombres de la carte selectionné du joueur avec celles des rangées
	{
		for (int j = 0; j < number_Row; j++) copy_number_diff[j] = (cards_selection[i]->Get_number()) - (plateau.Get_row(j).Get_last_card().Get_number());
		// On stoque toute les differences de notre cards_selection[i] avec toute les cartes des rangées

		int lower_diff = 0;
		bool card_added_in_ronw = false;

		Sort_asc(copy_number_diff);

		for (int j = 0; j < number_Row; j++)
		{
			if (copy_number_diff[j] > 0)
			{
				lower_diff = copy_number_diff[j];
				for (int k = 0; k < number_Row; k++)
				{
					if (lower_diff == (cards_selection[i]->Get_number()) - (plateau.Get_row(k).Get_last_card().Get_number()))
					{
						for (int l = 0; l < 6; l++)
						{
							if (&plateau.Get_row(k).Get_card(l) == nullptr)
							{
								plateau.Get_row(k).Add_card(cards_selection[i], l); // Si il existe encore un emplacement de la rangée choisie
								j = 4;
								card_added_in_ronw = true;
								break;
							}
						}
					}
					if (card_added_in_ronw == true) break;
				}
				// ON recupere l'indice de la plus petit difference dans notre tableau copy_number_diff, refletant la rangée avec la derniere carte
				// On fait bien attention de recuperer une Difference POSITIVE, signifiant que notre carte avec la plus petite difference est bien superieur à la rangée definie
			
			}
			
		}


	}


	Show_hand(les_joueurs);
	Show_row(plateau);

}


 inline void Game::Sort_asc(Card * my_tab[]) // tri dans l'ordre croissant
{
	 Card * my_copy_tab[4]; 

	for (int i = 0; i < 4 ; i++) // on regarde le tableau de carte pris en parameter
	{
		int index = 0;
		for (int j = 0; j < 4; j++) // On regarde toute les carte de my_tab
		{
			if (my_tab[i]->Get_number() > my_tab[j]->Get_number() ) index++; // on regarde les difference de notre carte[i] avec les tout les autres cartes[j]
		}
		my_copy_tab[index] = my_tab[i]; // ON assigne dans l'ordre les ellements de my_tab dans my_copy_tab
	}

	for (int i = 0; i < 4; i++) my_tab[i] = my_copy_tab[i];
}

 inline void Game::Sort_asc(int my_tab[])
 {
	
	 int my_copy_tab[4];

	 for (int i = 0; i < 4; i++) // on regarde le tableau de carte pris en parameter
	 {
		 int index = 0;
		 for (int j = 0; j < 4; j++) // On regarde toute les carte de my_tab
		 {
			 if (my_tab[i] > my_tab[j]) index++; // on regarde les difference de notre carte[i] avec les tout les autres cartes[j]
		 }
		 my_copy_tab[index] = my_tab[i]; // ON assigne dans l'ordre les ellements de my_tab dans my_copy_tab
	 }

	 for (int i = 0; i < 4; i++) my_tab[i] = my_copy_tab[i];
 }




Game::Turn:: ~Turn()
{

}

#pragma endregion



