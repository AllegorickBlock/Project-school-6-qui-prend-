#include "stdafx.h"
#include "Game.h"

#pragma region Class : Game

	#pragma region Constructor & Destructor

	int number_turn;

	Game::Game(int nb_human_player)
	{
		Player * the_players[Const_Var::nmbr_Gamer];
		Bot_Player the_bot_players[Const_Var::nmbr_Gamer];
		Human_Player the_human_players[Const_Var::nmbr_Gamer];

		for(int i = 0; i < Const_Var::nmbr_Gamer; i++)
		{
			if(nb_human_player > i)	the_players[i] = &the_human_players[i];
			else the_players[i] = &the_bot_players[i];
		}

		Game_Board the_game_board;
		Deck my_deck;
		number_turn = 0;

		cout << " \n\n\t----Deck non melange ---- \n\n";
		Show_deck(my_deck);

		my_deck.Mix_card();

		cout << " \n\n\t---- Deck melange ---- \n\n";

		for (int i = 0; i < Const_Var::nmbr_Gamer; i++) my_deck.Add_card_to_player(the_players[i]);
		for (int i = 0; i < Const_Var::nmbr_Rows; i++) my_deck.Add_card_to_row(the_game_board.Get_row(i));
	
		for (int i = 0; i < Const_Var::nmbr_Gamer; i++) Show_hand(the_players[i]);

		Show_row(the_game_board);

		this->Start(the_players, the_game_board, my_deck);
	}

	Game::~Game()	{	}

	#pragma endregion

	#pragma region Functions : Show

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
			if (my_deck.Get_card(j).In_deck()) Show_card(my_deck.Get_card(j));
			if ((j + 1) % 10 == 0) cout << "\n";
		}
	}

	inline void Game::Show_hand(Player * my_player)
	{
		cout << "\n\n ~~~~~~~~~~~{ Carte du joueur " << (my_player->Get_number() + 1) << " : " ;
		for (int j = 0; j < Const_Var::nmbr_cards_in_Hand; j++)
		{
			if (&my_player->Get_hand_player().Get_card_of_hand(j) != nullptr)
			{
				cout << (j + 1) << ".";
				Show_card(my_player->Get_hand_player().Get_card_of_hand(j));
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

	inline void Game::Show_cards_selection( Player * my_players[], Card * selection_card[])
	{
		cout << "\n\n-----------------------------< Cartes selectionnes >---------------------------- \n";
		for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
		{
			cout << "   " ;
			Show_card(*selection_card[i]);
			cout << ": J" << (selection_card[i]->Get_nbr_player() + 1) << "   ";
		}
		cout << "\n-------------------------------------------------------------------------------- \n";
	}

	inline void Game::Show_player_scores(Player * my_players[])
	{
		cout << "\n\n------> Scores des joueurs <------";
		for (int i = 0; i < Const_Var::nmbr_Gamer; i++)		cout << "\nJoueur " << (i+1) << " : " << my_players[i]->Get_score();
	}

	#pragma endregion

	#pragma region Functions : Sort & Start

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

	inline void Game::Start(Player * the_players[], Game_Board & game_board, Deck & my_deck)
	{
		for (this->end = false; end != true; )
		{
			for (int i = 0; i < Const_Var::nmbr_cards_in_Hand && (end == false); i++)
			{
				Turn my_Turn(the_players, game_board, my_deck);
				for (int j = 0; j < Const_Var::nmbr_Gamer; j++)
				{
					if (the_players[j]->Get_score() >= 66)
					{
						this->end = true;
						my_deck.Recover_cards_and_mix(the_players, &game_board);
						break;
					}
				}
			}
			my_deck.Recover_cards_and_mix(the_players, &game_board);
			for (int i = 0; i < Const_Var::nmbr_Gamer; i++)		my_deck.Add_card_to_player(the_players[i]);
			for (int i = 0; i < Const_Var::nmbr_Rows; i++)	my_deck.Add_card_to_row(game_board.Get_row(i));
		}
	}

	#pragma endregion

#pragma endregion

#pragma region Class : Turn

	#pragma region Constructor & Destructor

	Game::Turn::Turn(Player * the_players[], Game_Board & game_board, Deck & my_deck)
	{
		number_turn++;
		cout << "\n\n--------------------------------------------{Tour " << number_turn << "}--------------------------------------------";

		for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
		{
			Show_hand(the_players[i]);
			the_players[i]->Pick_selection_card(this->cards_selection);
		}
		Show_row(game_board);

		Sort_asc(cards_selection); // L'index de cartes dans cards_selection ne va plus corespondre a l'index du joueur

		Show_cards_selection(the_players,cards_selection);
	
		for (int i = 0; i < Const_Var::nmbr_Gamer; i++)
		{
			cout << "\n\n\n|||  ||||||||| Au tour du Joueur " << this->cards_selection[i]->Get_nbr_player() + 1 << " |||||||||  |||\n Carte choisie : ";
			Show_card(*the_players[this->cards_selection[i]->Get_nbr_player()]->Get_card_selection());
			the_players[this->cards_selection[i]->Get_nbr_player()]->Add_in_row(game_board,this->cards_selection);
			Show_row(game_board);
		}

		Show_player_scores(the_players);

		for (int i = 0; i < Const_Var::nmbr_Gamer; i++) cards_selection[i] = nullptr; // A la fin du tour il n'existe plus de carte selectionné par les joueurs
	}

	Game::Turn:: ~Turn(){	}

	#pragma endregion

#pragma endregion



