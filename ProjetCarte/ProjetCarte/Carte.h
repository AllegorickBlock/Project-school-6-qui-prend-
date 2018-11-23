#pragma once
class Carte
{
	int numero;
	int numero_boeuf;

public:
	Carte();
	~Carte();
	int Get_numero();
	int Get_numero_boeuf();
	bool Compare_numero(Carte carte_a_comparer);
	int Difference_numero();

};

