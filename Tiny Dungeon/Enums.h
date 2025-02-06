#pragma once


class Enums {
public:

	enum class cState { Move, Idle, Attack, Death };

	enum class SpecWpnEfct {
		None,
		ApplyRandomBuff,
		ApplyRandomDebuff,
		BonusHeal,
		SecondaryMassHeal
	};

	enum class WeaponTypes {
		None,
		Sword,
		Staff
	};

	enum class PrimaryMove {
		None,

		//Ally Moves
		KnightPrimary,
		ElfRangedPrimary,
		BlueMagePrimary,
		DinoPrimary,
		CentaurPrimary,

		//Enemy Moves
		MiniForesterPrimary,
		LeafLordPrimary,
		ForesterShooterPrimary,

		//
		MiniOrcPrimary,
		OrcPrimary,
		MaskedOrcPrimary,
		ShamanOrcPrimary,
		OrcBossPrimary
	};

	enum class SecondaryMove {
		None,

		//Ally Moves
		KnightSecondary,
		ElfRangedSecondary,
		BlueMageSecondary,
		DinoSecondary,
		CentaurSecondary,

		//Enemy Moves
		LeafLordSecondary,
		OrcSecondary,
		MaskedOrcSecondary,
		ShamanOrcSecondary,
		OrcBossSecondary,

		//Weapon Moves
		ForestStaffSecondary,
	};

	enum class Effects {
		None,

		Shield,
		NextTurnHeal,
		BreakShield,
		Stun,
		Dot, //(damage over time)
		BreakAttack,
		Attack,
		ReduceStamina,
		RemoveBeneficial,
		BlockHeal,
		Speed,
		ReduceSpeed
	};

	enum class AllyTypes {
		ElfF, ElfM, KnightF, KnightM, MageF, MageM, DinoF, DinoM, CentaurF, CentaurM,
		KnightG, KnightP
	};

	enum class EnemyTypes { 
		MiniForester, Forester, LeafLord,
		MiniOrc, MediumOrc, MediumShamanOrc, MediumMaskedOrc, OrcBoss,
		MiniDemon,
		MiniWhiteling
	};

	enum class ProjectileTypes {
		Forester,
		BlueMage,
		ElfArrow
	};

	enum class PassiveEffects {
		None, 
		
		TurnOnKill
	};

	enum class ButtonTypes {
		Clear, Audio, Mute, Menu, AutoPlay, PauseAuto, Play, Return, MainMenu, Options, Exit, NextLevel
	};

};


