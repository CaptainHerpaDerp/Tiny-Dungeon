#include "Ally.h"

using namespace CharacterGroup;

Ally::Ally(Enums::AllyTypes type)
{
	Affinity = 'a';

	this->type = type;

	LoadAttributes();

	rectSourceSprite.width = 16;
	rectSourceSprite.height = 32;
	HitPointsCurrent = HitPointsMax();
	cSprite.setScale(Utils::GetAppScale());
}

Ally::~Ally()
{
}

void CharacterGroup::Ally::LoadAttributes()
{

	rectSourceSprite.width = 16;
	rectSourceSprite.height = 32;
	IsRanged(false);

	switch (type) {
	case Enums::AllyTypes::CentaurM:
	case Enums::AllyTypes::CentaurF:

		rectSourceSprite.width = 32;
		rectSourceSprite.height = 32;

		hitVariations = SoundBank::Get().centaurHits;
		hitNameGroup = "centaurHit";

		attackVariations = SoundBank::Get().centaurAttacks;
		attackNameGroup = "centaurAttack";

		primaryMove = Moves::Get().centaurPrimary;
		secondaryMove = Moves::Get().centaurSecondary;

		setMaxHp(80);
		Speed = 7;
		Damage = 10;

		if (type == Enums::AllyTypes::CentaurF)
			cSprite.setTexture(TextureBank::Get().CentaurF);

		if (type == Enums::AllyTypes::CentaurM)
			cSprite.setTexture(TextureBank::Get().CentaurM);
		break;


	case Enums::AllyTypes::ElfM:
	case Enums::AllyTypes::ElfF:

		hitVariations = SoundBank::Get().humanHits;
		hitNameGroup = "humanHit";

		IsRanged(true);

		primaryMove = Moves::Get().elfPrimary;
		secondaryMove = Moves::Get().elfSecondary;

		setMaxHp(65);
		Speed = 12;
		Damage = 10;

		if (type == Enums::AllyTypes::ElfF)
			cSprite.setTexture(TextureBank::Get().ElfF);

		if (type == Enums::AllyTypes::ElfM)
			cSprite.setTexture(TextureBank::Get().ElfM);
		break;

	case Enums::AllyTypes::KnightM:
	case Enums::AllyTypes::KnightF:
	case Enums::AllyTypes::KnightP:
	case Enums::AllyTypes::KnightG:

		hitVariations = SoundBank::Get().humanHits;
		hitNameGroup = "humanHit";

		primaryMove = Moves::Get().knightPrimary;
		secondaryMove = Moves::Get().knightSecondary;

		setMaxHp(85);
		Speed = 9;
		Damage = 12;

		if (type == Enums::AllyTypes::KnightM)
			cSprite.setTexture(TextureBank::Get().KnightM);

		if (type == Enums::AllyTypes::KnightF)
			cSprite.setTexture(TextureBank::Get().KnightF);

		if (type == Enums::AllyTypes::KnightG)
			cSprite.setTexture(TextureBank::Get().GoldKnight);

		if (type == Enums::AllyTypes::KnightP)
			cSprite.setTexture(TextureBank::Get().PlatinumKnight);
		break;

	case Enums::AllyTypes::MageM:
	case Enums::AllyTypes::MageF:

		hitVariations = SoundBank::Get().humanHits;

		hitVariations = SoundBank::Get().humanHits;
		hitNameGroup = "humanHit";

		IsRanged(true);

		primaryMove = Moves::Get().magePrimary;
		secondaryMove = Moves::Get().mageSecondary;

		setMaxHp(55);
		Speed = 10;
		Damage = 9; //9

		if (type == Enums::AllyTypes::MageM)
			cSprite.setTexture(TextureBank::Get().MageM);

		if (type == Enums::AllyTypes::MageF)
			cSprite.setTexture(TextureBank::Get().MageF);
		break;


	case Enums::AllyTypes::DinoM:
	case Enums::AllyTypes::DinoF:

		hitVariations = SoundBank::Get().orcHits;
		hitNameGroup = "orcHit";

		attackVariations = SoundBank::Get().orcAttacks;
		attackNameGroup = "orcAttack";

		primaryMove = Moves::Get().dinoPrimary;
		secondaryMove = Moves::Get().dinoSecondary;

		setMaxHp(70);
		Speed = 9; // 10
		Damage = 16;

		if (type == Enums::AllyTypes::DinoM)
			cSprite.setTexture(TextureBank::Get().DinoM);

		if (type == Enums::AllyTypes::DinoF)
			cSprite.setTexture(TextureBank::Get().DinoF);
		break;
	}

	originalSecondary = secondaryMove;
	projectile.SetType(primaryMove.type);
	
}

void CharacterGroup::Ally::Transmog(Enums::AllyTypes newType, bool reloadRect)
{
	type = newType;
	LoadAttributes();
	if (reloadRect)
	SetWidthOffset();
	weaponCtrl.ClearWeapon();
}