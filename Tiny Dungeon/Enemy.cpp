#include "Enemy.h"

using namespace CharacterGroup;

Enemy::Enemy(Enums::EnemyTypes type)
{
	Affinity = 'e';
	LoadAttributes();
}

Enemy::~Enemy()
{
}

void CharacterGroup::Enemy::LoadAttributes()
{
	IsRanged(false);
	secondaryMove = Moves::Get().none;
	attackVariations = 0;

	switch (type) {

		//Foresters
	case Enums::EnemyTypes::MiniForester:

		hitVariations = SoundBank::Get().foresterHits;
		hitNameGroup = "foresterHit";

		primaryMove = Moves::Get().forestlingPrimary;

		setMaxHp(30);
		Speed = 8;
		Damage = 5;

		SetTexture(TextureBank::Get().ForesterMinion);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 16;

		break;

	case Enums::EnemyTypes::Forester:

		hitVariations = SoundBank::Get().foresterHits;
		hitNameGroup = "foresterHit";

		IsRanged(true);
		
		primaryMove = Moves::Get().foresterShooter;

		setMaxHp(25);
		Speed = 9;
		Damage = 7;

		SetTexture(TextureBank::Get().ForesterShooter);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 16;

		break;

	case Enums::EnemyTypes::LeafLord:

		hitVariations = SoundBank::Get().foresterBossHits;
		hitNameGroup = "foresterBossHit";

		attackVariations = SoundBank::Get().foresterBossAttacks;
		attackNameGroup = "foresterBossAttack";

		primaryMove = Moves::Get().leafLordPrimary;
		secondaryMove = Moves::Get().leafLordSecondary;

		setMaxHp(200);
		Speed = 7; 
		Damage = 28; 

		SetTexture(TextureBank::Get().LeafLord);
		rectSourceSprite.width = 32;
		rectSourceSprite.height = 32;

		break;

		//Orcs
	case Enums::EnemyTypes::MiniOrc:

		primaryMove = Moves::Get().miniOrcPrimary;
	
		hitVariations = SoundBank::Get().orcHits;
		hitNameGroup = "orcHit";

		attackVariations = SoundBank::Get().orcAttacks;
		attackNameGroup = "orcAttack";

		setMaxHp(70);
		Speed = 9;
		Damage = 9;

		SetTexture(TextureBank::Get().MiniOrc);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 16;

		break;
		
	case Enums::EnemyTypes::MediumOrc:

		primaryMove = Moves::Get().medOrcPrimary;
		secondaryMove = Moves::Get().medOrcSecondary;

		hitVariations = SoundBank::Get().orcHits;
		hitNameGroup = "orcHit";

		attackVariations = SoundBank::Get().orcAttacks;
		attackNameGroup = "orcAttack";

		setMaxHp(85);
		Speed = 9;
		Damage = 12;

		SetTexture(TextureBank::Get().MediumOrc);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 32;

		break;

	case Enums::EnemyTypes::MediumMaskedOrc:
	
		primaryMove = Moves::Get().maskedOrcPrimary;
		secondaryMove = Moves::Get().maskedOrcSecondary;

		hitVariations = SoundBank::Get().orcHits;
		hitNameGroup = "orcHit";

		attackVariations = SoundBank::Get().orcAttacks;
		attackNameGroup = "orcAttack";

		setMaxHp(55);
		Speed = 11;
		Damage = 14;	 //13
		
		SetTexture(TextureBank::Get().MediumMaskedOrc);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 32;

		break;

	case Enums::EnemyTypes::MediumShamanOrc:
		IsRanged(true);

		primaryMove = Moves::Get().shamanOrcPrimary;
		secondaryMove = Moves::Get().shamanOrcSecondary;
		hitVariations = SoundBank::Get().orcHits;

		hitVariations = SoundBank::Get().orcHits;
		hitNameGroup = "orcHit";

		attackVariations = SoundBank::Get().orcAttacks;
		attackNameGroup = "orcAttack";

		setMaxHp(70);
		Speed = 9;
		Damage = 11; //11

		SetTexture(TextureBank::Get().MediumShamanOrc);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 32;
		break;

	case Enums::EnemyTypes::OrcBoss:

		primaryMove = Moves::Get().orcBossPrimary;
		secondaryMove = Moves::Get().orcBossSecondary;

		hitVariations = SoundBank::Get().orcBossHits;

		hitVariations = SoundBank::Get().orcBossHits;
		hitNameGroup = "orcBossHit";

		attackVariations = SoundBank::Get().orcBossAttacks;
		attackNameGroup = "orcBossAttack";

		setMaxHp(300);
		Speed = 15; // 7
		Damage = 35; //11

		SetTexture(TextureBank::Get().OrcBoss);
		rectSourceSprite.width = 32;
		rectSourceSprite.height = 32;
		break;

		//Demons
	case Enums::EnemyTypes::MiniDemon:
		SetTexture(TextureBank::Get().MiniDemon);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 16;
		setMaxHp(70);
		Speed = 9;
		Damage = 15;
		break;

	case Enums::EnemyTypes::MiniWhiteling:
		SetTexture(TextureBank::Get().MiniWhiteling);
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 16;
		setMaxHp(40);
		Speed = 7;
		Damage = 10;
		break;
	}

	HitPointsCurrent = HitPointsMax();

	projectile.SetType(primaryMove.type);

	this->BasePos.y += basePosOffset;
	basePosOffset = 0;
	if (rectSourceSprite.height > 16)
	basePosOffset = (rectSourceSprite.height * 2.5f);
	this->BasePos.y -= basePosOffset;
	this->position = BasePos;

}

void CharacterGroup::Enemy::Transmog(Enums::EnemyTypes newType)
{	
	type = newType;
	LoadAttributes();
	ResetEffectOverlayPos();
	SetWidthOffset();
	weaponCtrl.ClearWeapon();
}

