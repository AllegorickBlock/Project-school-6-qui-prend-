#include "stdafx.h"
#include "Carte.h"


Carte::Carte()
{
}


Carte::~Carte()
{
}

int Carte::Get_numero() { return numero; }

int Carte::Get_numero_boeuf() { return numero_boeuf; }

bool Carte::Compare_numero(Carte carte_a_comparer) 
{
	if (Get_numero() > carte_a_comparer.Get_numero()) return true; // Si superieur return true
	if (Get_numero() < carte_a_comparer.Get_numero()) return false; // Si inferieur return false
}
