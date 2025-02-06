#pragma once

#include "TextureBank.h"
#include "Utils.h"
#include "Enums.h"
#include "SoundBank.h"
#include <unordered_map>
#include "MoveEffects.h"

using namespace sf;
using namespace std;

struct PrimaryMove {
	string name = "";
	Enums::PrimaryMove type;
	Texture cardTexture;
	MoveEffect effect;
	int effectChance = 1;
	char targetMode = 'e';
};

struct SecondaryMove {
	string name = "";
	Enums::SecondaryMove type;
	Texture cardTexture;
	Enums::PassiveEffects passiveEffect = Enums::PassiveEffects::None;
	MoveEffect effect;
	char targetMode = 'e';
	bool globalEffect = false;
	bool selfCastOnly = false;
	int cooldown = 1;
	string soundName = "genericMove";
};

class Moves {

private:

public:
	Moves();
	static Moves& Get();

	unordered_map<string, PrimaryMove> primaryMoves;
	unordered_map<string, PrimaryMove> secondaryMoves;

	//Ally Moves
	PrimaryMove elfPrimary{ "Weak Spot", Enums::PrimaryMove::ElfRangedPrimary, TextureBank::Get().ElfPrimary, MoveEffects::Get().BreakShield, 2, 'e' };
	SecondaryMove elfSecondary{ "Arrow Rain", Enums::SecondaryMove::ElfRangedSecondary, TextureBank::Get().ElfSecondary, Enums::PassiveEffects::None, {}, 'e', true, false, 3, "arrowVolley" };

	PrimaryMove centaurPrimary{ "Joint Assault", Enums::PrimaryMove::CentaurPrimary, TextureBank::Get().CentaurPrimary, {}, 0, 'e' };
	SecondaryMove centaurSecondary{ "Charge", Enums::SecondaryMove::CentaurSecondary, TextureBank::Get().CentaurSecondary, Enums::PassiveEffects::None, {}, 'a', true, false, 5, "centaurSecondary"};

	PrimaryMove knightPrimary{ "Heavy Hit", Enums::PrimaryMove::KnightPrimary, TextureBank::Get().KnightPrimary, MoveEffects::Get().Stun, 3, 'e' };
	SecondaryMove knightSecondary{ "Divine Shield", Enums::SecondaryMove::KnightSecondary, TextureBank::Get().KnightSecondary, Enums::PassiveEffects::None, MoveEffects::Get().AddShield, 'a', false, false, 4 };

	PrimaryMove magePrimary{ "Magic Bolt", Enums::PrimaryMove::BlueMagePrimary, TextureBank::Get().MagePrimary, MoveEffects::Get().ReduceStamina, 0, 'e' };
	SecondaryMove mageSecondary{ "Lasting Heal", Enums::SecondaryMove::BlueMageSecondary, TextureBank::Get().MageSecondary, Enums::PassiveEffects::None, MoveEffects::Get().NextTurnHeal, 'a', false, false, 4, "blueMageHealMove" };

	PrimaryMove dinoPrimary{ "Sharp Claw", Enums::PrimaryMove::DinoPrimary, TextureBank::Get().DinoPrimary, MoveEffects::Get().RemoveBeneficial, 2, 'e' };
	SecondaryMove dinoSecondary{ "Adrenaline", Enums::SecondaryMove::DinoSecondary, TextureBank::Get().DinoSecondary, Enums::PassiveEffects::TurnOnKill, {}, 'a', false, true, 0 };

	PrimaryMove forestlingPrimary{ "Toxic Touch", Enums::PrimaryMove::MiniForesterPrimary, {}, MoveEffects::Get().Poison, 2, 'e' };

	PrimaryMove foresterShooter{ "Exhaust", Enums::PrimaryMove::ForesterShooterPrimary, {}, MoveEffects::Get().ReduceStamina, 1, 'e' };

	PrimaryMove leafLordPrimary{ "Huge Hit", Enums::PrimaryMove::LeafLordPrimary, {}, MoveEffects::Get().BreakShield, 2, 'e' };
	SecondaryMove leafLordSecondary{ "Gift of Life", Enums::SecondaryMove::LeafLordSecondary, {}, Enums::PassiveEffects::None, {}, 'a', false, false, 3, "foresterBossSecondary" };

	PrimaryMove miniOrcPrimary{ "Foul Play", Enums::PrimaryMove::MiniOrcPrimary, {}, MoveEffects::Get().BreakAttack, 4, 'e' };

	PrimaryMove medOrcPrimary{ "Rout", Enums::PrimaryMove::OrcPrimary, {}, MoveEffects::Get().BreakShield, 2, 'e' };
	SecondaryMove medOrcSecondary{ "War Cry", Enums::SecondaryMove::OrcSecondary, {}, Enums::PassiveEffects::None, MoveEffects::Get().AddAttack, 'a', false, true, 4, "orcBattleCry" };

	PrimaryMove maskedOrcPrimary{ "Rout", Enums::PrimaryMove::MaskedOrcPrimary, {}, MoveEffects::Get().BlockHeal, 2, 'e' };
	SecondaryMove maskedOrcSecondary{ "Ambush", Enums::SecondaryMove::MaskedOrcSecondary, {}, Enums::PassiveEffects::None, MoveEffects::Get().AddSpeed, 'a', false, true, 4 };

	PrimaryMove shamanOrcPrimary{ "Forbidden Power",  Enums::PrimaryMove::ShamanOrcPrimary, {}, {}, 0, 'e' };
	SecondaryMove shamanOrcSecondary{ "Distribute Health", Enums::SecondaryMove::ShamanOrcSecondary, {}, Enums::PassiveEffects::None, {}, 'a', true, false, 4, "shamanCircle" };

	PrimaryMove orcBossPrimary{ "Brute Force", Enums::PrimaryMove::OrcBossPrimary, {}, MoveEffects::Get().BreakSpeed, 2, 'e' };
	SecondaryMove orcBossSecondary{ "Greed", Enums::SecondaryMove::OrcBossSecondary, {}, Enums::PassiveEffects::None, {}, 'a', true, true, 3, "orcBossSecondary" }; //4

	//weapon secondaries
	SecondaryMove massHealSecondary{ "Clensing Heal", Enums::SecondaryMove::ForestStaffSecondary, TextureBank::Get().ForestStaffSecondary, {}, {}, 'a', true, false, 3, "forestStaffMove" };

	SecondaryMove none{};
	//Enemy Moves
};

