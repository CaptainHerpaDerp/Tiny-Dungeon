#pragma once
#include "TextureBank.h"
#include "GameObject.h"
#include "Enums.h"
#include <SFML/Graphics.hpp> 
#include <iostream>
#include <unordered_map>
#include "Utils.h"

struct WeaponEffects 
{
	int Attack = 0;
	int Health = 0;
	int Speed = 0;
	//percentage added to heals
	int Healing = 0;
	Enums::SpecWpnEfct SpecialEffect = Enums::SpecWpnEfct::None;
	//percentage chance of applying effect, or a bonus in some cases
	int SpecialEffectVal = 0;
};

struct Weapon
{
	string name = "none";
	int id = 0;
	Enums::WeaponTypes type;
	Texture weaponTexture;
	WeaponEffects weaponEffects;
	//1 = Common, 2 = Rare, 3 = Epic, 4 = Legendary
	int weaponQuality = 0;
};

constexpr auto WeaponCount = 20;
constexpr auto FirstPhaseGroupSize = 8; 
constexpr auto SecondPhaseGroupSize = 11;
constexpr auto OrcWeaponGroupSize = 4;

class WeaponController : public GameObject
{
private:

	int animStep = 0;

	float animSpeed = 0;
	float offsetX = 0;
	float offsetY = 0;

	bool moving = false;
	bool animating = false;

	Enums::cState state = Enums::cState::Idle;
	Vector2f targPos;

	const bool inactive();
	void runAnimation();
	int rarityRoll();

	const float rareChance = 30;
	const float epicChance = 12;
	const float legendaryChance = 3;

public:
	void SetAnimSpeed(float val);
	WeaponController();
																	 //atk //hp //spd //healMod
	Weapon equippedWeapon{ "none", 0 , Enums::WeaponTypes::None, TextureBank::Get().IronSword, {0, 0, 0, 0, Enums::SpecWpnEfct::None, 0}};

	Weapon IronSword{ "Sword", 1 ,Enums::WeaponTypes::Sword, TextureBank::Get().IronSword, {3, 2, 1, 0} };
	Weapon IronSaber{ "Saber", 2 ,Enums::WeaponTypes::Sword, TextureBank::Get().IronSaber, {5, -2, 3, 0} };
	Weapon IronTemplarSword{ "Templar Sword", 3 ,Enums::WeaponTypes::Sword, TextureBank::Get().IronTemplarSword, {3, 8, -2, 25} };
	Weapon IronDagger{ "Dagger", 4 ,Enums::WeaponTypes::Sword, TextureBank::Get().IronDagger, {5, -4, 4, 0} };						//switched from chance to bonus
	Weapon LifeStaff{ "Staff of Life", 5 ,Enums::WeaponTypes::Staff, TextureBank::Get().LifeStaff, {3, 1, 3, 33, Enums::SpecWpnEfct::BonusHeal, 25} };
	Weapon DamageStaff{ "Staff of Power", 6 ,Enums::WeaponTypes::Staff, TextureBank::Get().DamageStaff, {5, 2, 1, -10, Enums::SpecWpnEfct::ApplyRandomDebuff, 35} };
	Weapon SpecialStaff{ "Staff of Aid", 7 ,Enums::WeaponTypes::Staff, TextureBank::Get().SpecialStaff, {3, -7, 2, -10, Enums::SpecWpnEfct::ApplyRandomBuff, 35} };
	Weapon WoodStaff{ "Wood Staff", 8 ,Enums::WeaponTypes::Staff, TextureBank::Get().WoodStaff, {3, 3, 0, 0, Enums::SpecWpnEfct::SecondaryMassHeal, 20} };
	Weapon WoodClub{ "Wood Club", 9 ,Enums::WeaponTypes::Sword, TextureBank::Get().WoodClub, {4, 4, 0, 25} };
	Weapon DiamondKatana{ "DiamondKatana", 10 ,Enums::WeaponTypes::Sword, TextureBank::Get().DiamondKatana };
	Weapon DiamondSword{ "DiamondSword", 11 ,Enums::WeaponTypes::Sword, TextureBank::Get().DiamondSword };
	Weapon DiamondChopper{ "DiamondChopper", 12 ,Enums::WeaponTypes::Sword, TextureBank::Get().DiamondChopper };
	Weapon DiamondElfSword{ "DiamondElfSword", 13 ,Enums::WeaponTypes::Sword, TextureBank::Get().DiamondElfSword };
	Weapon BlackAxe{ "BlackAxe", 14 ,Enums::WeaponTypes::Sword, TextureBank::Get().BlackAxe, {6, 2, 2} };
	Weapon BlackHammer{ "BlackHammer", 15 ,Enums::WeaponTypes::Sword, TextureBank::Get().BlackHammer, {8, 10, -3} };
	Weapon BlackMace{ "BlackMace", 16 ,Enums::WeaponTypes::Sword, TextureBank::Get().BlackMace, {6, 7, -2} };
	Weapon BlackSword{ "BlackSword", 17 ,Enums::WeaponTypes::Sword, TextureBank::Get().BlackSword, {6, 4, 0} };
	Weapon GoldSword{ "GoldSword", 18 ,Enums::WeaponTypes::Sword, TextureBank::Get().GoldSword };
	Weapon GoldShortSword{ "GoldShortSword", 19 ,Enums::WeaponTypes::Sword, TextureBank::Get().GoldShortSword };
	//boss weapon, visual
	Weapon SkullMace{ "Skull Mace", 20, Enums::WeaponTypes::Sword, TextureBank::Get().SkullMace };

	Weapon* weapons[WeaponCount]{ &IronSword, &IronSaber, &IronTemplarSword, &IronDagger,
		&LifeStaff, &DamageStaff, &SpecialStaff, &
		WoodStaff, &WoodClub,
		& DiamondKatana, &DiamondSword, &DiamondChopper, &DiamondElfSword,
		& BlackAxe, &BlackHammer, &BlackMace, &BlackSword,
		& GoldSword, &GoldShortSword, &SkullMace
	};

	Weapon* firstPhaseGroup[FirstPhaseGroupSize]{
		&IronSword,& IronSaber,& IronTemplarSword,& IronDagger,& LifeStaff, &SpecialStaff, &WoodStaff, &WoodClub
	};

	Weapon* secondPhaseGroup[SecondPhaseGroupSize]{
		&IronSword,&IronSaber,&IronTemplarSword,&IronDagger,&LifeStaff, &DamageStaff, &SpecialStaff, &BlackAxe,& BlackHammer, &BlackMace, &BlackSword
	};

	Weapon* orcWeaponGroup[OrcWeaponGroupSize]{
		&IronDagger,& BlackAxe,& BlackHammer, &BlackMace
	};

	//Vector2f vectors[2]{ Vector2f(10, 10), Vector2f(5, 5) };

	void RandomizeWeapon();
	void Set(Weapon weapon, bool randomizeStats = false);

	WeaponEffects& stats();

	const int Quality();
	const string QualityString();
	const Color RarityColor();
	const bool HasReplaceSecondary();

	void update(Vector2f pos);
	void update();
	void render(RenderWindow& window) override;
	void NextFrame();
	void SetState(Enums::cState newState);
	void ResetAnimLoop();
	void MoveTo(Vector2f targ);
	void StartAnimation();

	void ClearWeapon();
};

