#include "Moves.h"


Moves::Moves()
{
	//primaryMoves.insert(pair<string, PrimaryMove>("KnightPrimary", PrimaryMove{ "Heavy Hit" , Enums::PrimaryMove::KnightPrimary, TextureBank::Get().KnightPrimary, Enums::Effects::Stun, 4, 'e'}));

	cout << "Loaded Moves";
}

Moves& Moves::Get()
{	
	static Moves mo;
	return mo;
}

