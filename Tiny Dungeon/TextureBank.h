#pragma once

#include <SFML/Graphics.hpp> 
#include <iostream>

using namespace sf;
using namespace std;

class TextureBank {
public:
	static TextureBank& Get();

	void ForceLoad();

	//Buff Cards
	Texture AtkBf;
	Texture DefBf;
	Texture HealBf;
	Texture SpeedBf;

	//Debuff Cards
	Texture AtkDbf;
	Texture DefDbf;
	Texture StunDbf;
	Texture DotDbf;
	Texture BlockHealDbf;
	Texture SpeedDbf;


	//Move Cards
	Texture MagePrimary;
	Texture MageSecondary;
	Texture KnightPrimary;
	Texture KnightSecondary;
	Texture ElfPrimary;
	Texture ElfSecondary;
	Texture DinoPrimary;
	Texture DinoSecondary;
	Texture CentaurPrimary;
	Texture CentaurSecondary;

	Texture ForestStaffSecondary;

	//Enemies
	Texture ForesterMinion;
	Texture ForesterShooter;
	Texture LeafLord;

	Texture MiniWhiteling;

	Texture MiniDemon;

	Texture MiniOrc;
	Texture MediumOrc;
	Texture MediumShamanOrc;
	Texture MediumMaskedOrc;
	Texture OrcBoss;

	//Allies
	Texture KnightM;
	Texture KnightF;
	Texture ElfM;
	Texture ElfF;
	Texture MageM;
	Texture MageF;
	Texture DinoM;
	Texture DinoF;
	Texture CentaurM;
	Texture CentaurF;

	//Reward Allies
	Texture PlatinumKnight;
	Texture GoldKnight;

	//Projectiles
	Texture FShooterProj;
	Texture BlueMageProj;
	Texture ElfProj;

	//Effect Effects
	Texture HealEffect;
	Texture ShieldEffect;
	Texture ShieldBreakEffect;
	Texture SlowEffect;
	Texture SpeedEffect;
	Texture StunEffect;
	Texture AttackEffect;
	Texture AttackBreakEffect;
	Texture PoisonEffect;
	Texture LeafLordSpecial;
	Texture ShamanTransferAlly;
	Texture ShamanTransferEnemy;

	//Global Moves
	Texture ElfVolley;
	Texture ShamanSecondary;
	Texture OrcBossSecondary;

	//Weapons
	Texture IronSword;
	Texture IronSaber;
	Texture IronTemplarSword;
	Texture IronDagger;
	Texture DiamondKatana;
	Texture DiamondSword;
	Texture DiamondChopper;
	Texture DiamondElfSword;
	Texture BlackAxe;
	Texture BlackHammer;
	Texture BlackMace;
	Texture BlackSword;
	Texture GoldSword;
	Texture GoldShortSword;
	Texture LifeStaff;
	Texture DamageStaff;
	Texture SpecialStaff;
	Texture WoodStaff;
	Texture WoodClub;
	Texture SkullMace;

	//Level Decor
	Texture CenterRoomPillar;
	Texture BackWallPillar;
	Texture WallSlime;
	Texture RedFlag;
	Texture GreenFlag;
	Texture BlueFlag;
	Texture YellowFlag;
	Texture FloorStain1;
	Texture FloorStain2;
	Texture FloorStain3;
	Texture FloorStain4;
	Texture FloorStain5;
	Texture FloorStain6;
	Texture FloorStain7;
	Texture AnimWallFountainBlue;
	Texture AnimWallFountainRed;

	//Level / UI Elements
	Texture MenuMap;
	Texture GameMap;
	Texture Door;
	Texture DoorOpen;
	Texture UiFrame;
	Texture TurnCircle;
	Texture TurnCircleSheet;
	Texture AllyCastIndicator;
	Texture EnemyCastIndicator;
	Texture UiMoveSelectedBorder;
	Texture UiMovePassiveBorder;
	Texture UiCooldownRect;
	Texture UiRearrangeIndicator;
	Texture MoveDetails;	
	Texture HpStaminaBar;
	Texture Button;
	Texture CurrentLevelCard;	
	Texture CurrentLevelCardExtended;

	Texture AutoPlayButton;
	Texture AutoPlayPauseButton;
	Texture AudioButton;
	Texture MuteButton;
	Texture MenuButton;

	Texture MenuPopup;
	Texture PlayButton;
	Texture PlayButtonSelected;
	Texture ReturnButton;
	Texture ReturnButtonSelected;
	Texture RestartButton;
	Texture RestartButtonSelected;
	Texture HelpButton;
	Texture HelpButtonSelected;
	Texture ExitButton;
	Texture ExitButtonSelected;

	Texture ContinueButton;	
	Texture ContinueButtonSelected;

	Texture ScoresTitleElement;
	Texture ScoresAdditionElement;

	Texture SaveFound;

	Texture WeaponDetails;

private:
	TextureBank();
};

