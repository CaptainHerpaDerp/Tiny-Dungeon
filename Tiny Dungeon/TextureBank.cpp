#include "TextureBank.h"

TextureBank& TextureBank::Get() {
	static TextureBank te;
	return te;
}

void TextureBank::ForceLoad()
{
	cout << "forced";
}

TextureBank::TextureBank() {
	AtkBf.loadFromFile("Assets/Buffs/AtkBf.png");
	DefBf.loadFromFile("Assets/Buffs/DefBf.png");
	HealBf.loadFromFile("Assets/Buffs/HealBf.png");
	SpeedBf.loadFromFile("Assets/Buffs/SpeedBf.png");

	AtkDbf.loadFromFile("Assets/Debuffs/AtkDbf.png");
	DefDbf.loadFromFile("Assets/Debuffs/DefDbf.png");
	StunDbf.loadFromFile("Assets/Debuffs/StunDbf.png");
	DotDbf.loadFromFile("Assets/Debuffs/PoisonDbf.png");
	BlockHealDbf.loadFromFile("Assets/Debuffs/BlockHealDbf.png");
	SpeedDbf.loadFromFile("Assets/Debuffs/SpeedDbf.png");

	ForesterMinion.loadFromFile("Assets/Enemies/MiniForestCreature.png");
	ForesterShooter.loadFromFile("Assets/Enemies/Forester.png");
	LeafLord.loadFromFile("Assets/Enemies/LeafLord.png");

	MiniOrc.loadFromFile("Assets/Enemies/MiniOrc.png");
	MediumOrc.loadFromFile("Assets/Enemies/MediumOrc.png");
	MediumMaskedOrc.loadFromFile("Assets/Enemies/MediumMaskedOrc.png");
	MediumShamanOrc.loadFromFile("Assets/Enemies/MediumShamanOrc.png");
	OrcBoss.loadFromFile("Assets/Enemies/OrcBoss.png");

	//Move Cards
	MagePrimary.loadFromFile("Assets/MoveCards/BlueMageBasic.png");
	MageSecondary.loadFromFile("Assets/MoveCards/BlueMageSecondary.png");
	KnightPrimary.loadFromFile("Assets/MoveCards/KnightBasic.png");
	KnightSecondary.loadFromFile("Assets/MoveCards/KnightSecondary.png");
	ElfPrimary.loadFromFile("Assets/MoveCards/RangedElfPrimary.png");
	ElfSecondary.loadFromFile("Assets/MoveCards/RangedElfSecondary.png");
	DinoPrimary.loadFromFile("Assets/MoveCards/DinoPrimary.png");
	DinoSecondary.loadFromFile("Assets/MoveCards/DinoSecondary.png");
	CentaurPrimary.loadFromFile("Assets/MoveCards/CentaurPrimary.png");
	CentaurSecondary.loadFromFile("Assets/MoveCards/CentaurSecondary.png");
	ForestStaffSecondary.loadFromFile("Assets/MoveCards/ForestStaffSecondary.png");

	//Allies
	KnightM.loadFromFile("Assets/Allies/KnightM.png");
	KnightF.loadFromFile("Assets/Allies/KnightF.png");
	ElfM.loadFromFile("Assets/Allies/ElfM.png");
	ElfF.loadFromFile("Assets/Allies/ElfF.png");
	MageM.loadFromFile("Assets/Allies/MageM.png");
	MageF.loadFromFile("Assets/Allies/MageF.png");
	DinoM.loadFromFile("Assets/Allies/DinoM.png");
	DinoF.loadFromFile("Assets/Allies/DinoF.png");
	CentaurM.loadFromFile("Assets/Allies/CentaurM.png");
	CentaurF.loadFromFile("Assets/Allies/CentaurF.png");

	//Reward Allies
	PlatinumKnight.loadFromFile("Assets/Allies/BonusKnight/PlatinumKnight.png");
	GoldKnight.loadFromFile("Assets/Allies/BonusKnight/GoldKnight.png");

	//Projectiles
	FShooterProj.loadFromFile("Assets/Projectiles/ForesterProjectileSheet.png");
	BlueMageProj.loadFromFile("Assets/Projectiles/MageBolt.png");
	ElfProj.loadFromFile("Assets/Projectiles/ElfArrow.png");

	//Effect Effects
	HealEffect.loadFromFile("Assets/MoveEffects/HealEffect.png");
	ShieldEffect.loadFromFile("Assets/MoveEffects/ShieldEffect.png");
	ShieldBreakEffect.loadFromFile("Assets/MoveEffects/ShieldBreakEffect.png");
	SlowEffect.loadFromFile("Assets/MoveEffects/SlowEffect.png");
	SpeedEffect.loadFromFile("Assets/MoveEffects/SpeedEffect.png");
	StunEffect.loadFromFile("Assets/MoveEffects/StunEffect.png");
	AttackEffect.loadFromFile("Assets/MoveEffects/AttackEffect.png");
	AttackBreakEffect.loadFromFile("Assets/MoveEffects/AttackBreakEffect.png");
	PoisonEffect.loadFromFile("Assets/MoveEffects/PoisonEffect.png");
	LeafLordSpecial.loadFromFile("Assets/MoveEffects/LeafLordSpecial.png");
	ShamanTransferAlly.loadFromFile("Assets/MoveEffects/ShamanHPTransferAlly.png");
	ShamanTransferEnemy.loadFromFile("Assets/MoveEffects/ShamanHPTransferEnemy.png");

	//Global Moves
	ElfVolley.loadFromFile("Assets/GlobalMoveAnimations/ElfVolley.png");
	ShamanSecondary.loadFromFile("Assets/GlobalMoveAnimations/ShamanSecondary.png");
	OrcBossSecondary.loadFromFile("Assets/GlobalMoveAnimations/OrcBossSecondary.png");

	//Weapons
	IronSword.loadFromFile("Assets/Weapons/IronSword.png");
	IronSaber.loadFromFile("Assets/Weapons/IronSaber.png");
	IronTemplarSword.loadFromFile("Assets/Weapons/IronTemplarSword.png");
	IronDagger.loadFromFile("Assets/Weapons/IronDagger.png");
	DiamondKatana.loadFromFile("Assets/Weapons/DiamondKatana.png");
	DiamondSword.loadFromFile("Assets/Weapons/DiamondSword.png");
	DiamondChopper.loadFromFile("Assets/Weapons/DiamondChopper.png");
	DiamondElfSword.loadFromFile("Assets/Weapons/DiamondElfSword.png");
	BlackAxe.loadFromFile("Assets/Weapons/BlackAxe.png");
	BlackHammer.loadFromFile("Assets/Weapons/BlackHammer.png");
	BlackMace.loadFromFile("Assets/Weapons/BlackMace.png");
	BlackSword.loadFromFile("Assets/Weapons/BlackSword.png");
	GoldSword.loadFromFile("Assets/Weapons/GoldSword.png");
	GoldShortSword.loadFromFile("Assets/Weapons/GoldShortSword.png");
	LifeStaff.loadFromFile("Assets/Weapons/LifeStaff.png");
	DamageStaff.loadFromFile("Assets/Weapons/DamageStaff.png");
	SpecialStaff.loadFromFile("Assets/Weapons/SpecialStaff.png");
	WoodStaff.loadFromFile("Assets/Weapons/WoodStaff.png");
	WoodClub.loadFromFile("Assets/Weapons/WoodClub.png");
	SkullMace.loadFromFile("Assets/Weapons/SkullMace.png");

	//Level Decor
	CenterRoomPillar.loadFromFile("Assets/LevelDecorElements/Pillar.png");
	BackWallPillar.loadFromFile("Assets/LevelDecorElements/BackWallPillar.png");
	WallSlime.loadFromFile("Assets/LevelDecorElements/WallSlime.png");
	RedFlag.loadFromFile("Assets/LevelDecorElements/RedFlag.png");
	GreenFlag.loadFromFile("Assets/LevelDecorElements/GreenFlag.png");
	BlueFlag.loadFromFile("Assets/LevelDecorElements/BlueFlag.png");
	YellowFlag.loadFromFile("Assets/LevelDecorElements/YellowFlag.png");
	FloorStain1.loadFromFile("Assets/LevelDecorElements/FloorStain1.png");
	FloorStain2.loadFromFile("Assets/LevelDecorElements/FloorStain2.png");
	FloorStain3.loadFromFile("Assets/LevelDecorElements/FloorStain3.png");
	FloorStain4.loadFromFile("Assets/LevelDecorElements/FloorStain4.png");
	FloorStain5.loadFromFile("Assets/LevelDecorElements/FloorStain5.png");
	FloorStain6.loadFromFile("Assets/LevelDecorElements/FloorStain6.png");
	FloorStain7.loadFromFile("Assets/LevelDecorElements/FloorStain7.png");
	AnimWallFountainBlue.loadFromFile("Assets/LevelDecorElements/AnimWallFountainBlue.png");
	AnimWallFountainRed.loadFromFile("Assets/LevelDecorElements/AnimWallFountainRed.png");

	//Level Elements
	Door.loadFromFile("Assets/LevelElements/Door.png");
	DoorOpen.loadFromFile("Assets/LevelElements/DoorOpen.png");
	MenuMap.loadFromFile("Assets/LevelElements/menumap.png");
	GameMap.loadFromFile("Assets/LevelElements/map.png");
	Door.loadFromFile("Assets/LevelElements/Door.png");

	TurnCircle.loadFromFile("Assets/LevelElements/turnCircle.png");
	TurnCircleSheet.loadFromFile("Assets/LevelElements/turnCircleSheet.png");
	AllyCastIndicator.loadFromFile("Assets/LevelElements/AllyCastableIndicator.png");
	EnemyCastIndicator.loadFromFile("Assets/LevelElements/EnemyCastableIndicator.png");

	UiFrame.loadFromFile("Assets/LevelElements/MovesUiFrame.png");
	UiMoveSelectedBorder.loadFromFile("Assets/LevelElements/MovesUiFrameSelected.png");
	UiMovePassiveBorder.loadFromFile("Assets/LevelElements/MovesUiFramePassive.png");
	HpStaminaBar.loadFromFile("Assets/LevelElements/healthstaminabar.png");
	UiRearrangeIndicator.loadFromFile("Assets/LevelElements/RearrangeIndicator.png");
	UiCooldownRect.loadFromFile("Assets/LevelElements/Cooldown.png");
	MoveDetails.loadFromFile("Assets/LevelElements/MoveDetails.png");
	CurrentLevelCard.loadFromFile("Assets/LevelElements/CurrentLevelCard.png");
	CurrentLevelCardExtended.loadFromFile("Assets/LevelElements/CurrentLevelCardExtended.png");

	Button.loadFromFile("Assets/LevelElements/Button.png");
	AutoPlayButton.loadFromFile("Assets/LevelElements/AutoPlayButton.png");
	AutoPlayPauseButton.loadFromFile("Assets/LevelElements/AutoPlayPauseButton.png");
	AudioButton.loadFromFile("Assets/LevelElements/VolumeButton.png");
	MuteButton.loadFromFile("Assets/LevelElements/MuteButton.png");
	MenuButton.loadFromFile("Assets/LevelElements/MenuButton.png");

	MenuPopup.loadFromFile("Assets/LevelElements/MenuPopup.png");

	PlayButton.loadFromFile("Assets/LevelElements/PlayButton.png");
	PlayButtonSelected.loadFromFile("Assets/LevelElements/PlayButtonSelected.png");
	ReturnButton.loadFromFile("Assets/LevelElements/ReturnButton.png");
	ReturnButtonSelected.loadFromFile("Assets/LevelElements/ReturnButtonSelected.png");
	RestartButton.loadFromFile("Assets/LevelElements/RestartButton.png");
	RestartButtonSelected.loadFromFile("Assets/LevelElements/RestartButtonSelected.png");
	HelpButton.loadFromFile("Assets/LevelElements/HelpButton.png");
	HelpButtonSelected.loadFromFile("Assets/LevelElements/HelpButtonSelected.png");
	ExitButton.loadFromFile("Assets/LevelElements/ExitButton.png");
	ExitButtonSelected.loadFromFile("Assets/LevelElements/ExitButtonSelected.png");

	ContinueButton.loadFromFile("Assets/LevelElements/ContinueButton.png");
	ContinueButtonSelected.loadFromFile("Assets/LevelElements/ContinueButtonSelected.png");

	ScoresTitleElement.loadFromFile("Assets/LevelElements/ScoresTitleElement.png");
	ScoresAdditionElement.loadFromFile("Assets/LevelElements/ScoresAdditionElement.png");

	SaveFound.loadFromFile("Assets/LevelElements/SaveFound.png");

	WeaponDetails.loadFromFile("Assets/LevelElements/WeaponDetails.png");

	cout << "loaded all textures" << endl;
}

//TextureBank TextureBank::tb_Instance;
