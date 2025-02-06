#pragma once
#include "Enums.h"
#include "SoundBank.h"
#include <iostream>


using namespace std;
//percentage of stamina that would be reduced by a stamina reducing effect
constexpr auto ReduceStaminaAmount = 25;
constexpr auto PosModVal = 0.7;
constexpr auto NegModVal = 1.4;

struct MoveEffect {
	Enums::Effects action;
	int duration = 1;
	char type = 'n';
	string sound;
};

class MoveEffects{
public:
	static MoveEffects& Get();
	//beneficial	
	MoveEffect AddShield{ Enums::Effects::Shield , 3, 'b', "shield" };
	MoveEffect AddAttack{ Enums::Effects::Attack , 3, 'b', "attack"};
	MoveEffect AddSpeed{ Enums::Effects::Speed , 3, 'b', "speed"};
	MoveEffect NextTurnHeal{ Enums::Effects::NextTurnHeal , 1, 'b', "heal"};

	//harmful
	MoveEffect BreakShield{ Enums::Effects::BreakShield , 3, 'h', "breakShield"};
	MoveEffect Stun{ Enums::Effects::Stun , 1, 'h', "stun"};
	MoveEffect Poison{ Enums::Effects::Dot , 2, 'h', "poison"};
	MoveEffect BreakSpeed{ Enums::Effects::ReduceSpeed , 3, 'h', "slow"};
	MoveEffect BlockHeal{ Enums::Effects::BlockHeal , 2, 'h', "preventHeal"};
	MoveEffect BreakAttack{ Enums::Effects::BreakAttack , 3, 'h', "breakAttack"};

	MoveEffect RemoveBeneficial{ Enums::Effects::RemoveBeneficial , 0, 'a', "removeBeneficial" };
	MoveEffect ReduceStamina{ Enums::Effects::ReduceStamina , 0, 'a', "reuduceStam"};


private:
	MoveEffects();
};

