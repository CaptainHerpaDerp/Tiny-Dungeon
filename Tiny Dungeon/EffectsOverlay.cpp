#include "EffectsOverlay.h"

CharacterGroup::EffectsOverlay::EffectsOverlay()
{
	SetRectSize(32);
	DisableEffect();
}

CharacterGroup::EffectsOverlay::~EffectsOverlay()
{
}

void CharacterGroup::EffectsOverlay::RunEffect(PrimaryMove move, char targetAff)
{
	switch (move.type) {
		case Enums::PrimaryMove::ShamanOrcPrimary:
			if(targetAff == 'a')
		SetTexture(TextureBank::Get().ShamanTransferAlly);
			if (targetAff == 'e')
		SetTexture(TextureBank::Get().ShamanTransferEnemy);

		speedModifier = 0.75f;
		setTex = true;
		frames = 13;
		break;
	}

	RunEffect(move.effect.action);
}

void CharacterGroup::EffectsOverlay::RunEffect(SecondaryMove move)
{
	switch (move.type) {
		case Enums::SecondaryMove::LeafLordSecondary:
			SetTexture(TextureBank::Get().LeafLordSpecial);
			setTex = true;
			frames = 8;
			break;
	}

	RunEffect(move.effect.action);
}


void CharacterGroup::EffectsOverlay::RunEffect(Enums::Effects effect)
{
	if (isAnimating) {
		AnimEffect(frames);
		return;
	}
		
	if (!setTex)
	switch (effect) {
	case Enums::Effects::NextTurnHeal:
		SetTexture(TextureBank::Get().HealEffect);
		frames = 8;
		break;

	case Enums::Effects::Stun:
		SetTexture(TextureBank::Get().StunEffect);
		speedModifier = 0.75f;
		frames = 10;
		break;

	case Enums::Effects::Shield:
		SetTexture(TextureBank::Get().ShieldEffect);
		frames = 7;
		break;

	case Enums::Effects::BreakShield:
		SetTexture(TextureBank::Get().ShieldBreakEffect);
		frames = 7;
		break;

	case Enums::Effects::Speed:
		SetTexture(TextureBank::Get().SpeedEffect);
		frames = 8;
		break;

	case Enums::Effects::ReduceSpeed:
		SetTexture(TextureBank::Get().SlowEffect);
		frames = 8;
		break;

	case Enums::Effects::Attack:
		SetTexture(TextureBank::Get().AttackEffect);
		frames = 8;
		break;	
	
	case Enums::Effects::BreakAttack:
		SetTexture(TextureBank::Get().AttackBreakEffect);
		frames = 7;
		break;

	case Enums::Effects::Dot:
		SetTexture(TextureBank::Get().PoisonEffect);
		speedModifier = 0.75f;
		frames = 8;
	}
	EnableEffect();
}

void CharacterGroup::EffectsOverlay::EnableEffect()
{
	isAnimating = true;
	setTex = true;
}

void CharacterGroup::EffectsOverlay::AnimEffect(int frames)
{

	if (clock.getElapsedTime().asSeconds() > 0.125f * speedModifier) {
		visible = true;
		if (rectSourceSprite.left == rectSourceSprite.width * frames) {
			rectSourceSprite.left = -rectSourceSprite.width;
			DisableEffect();
		}

		rectSourceSprite.left += rectSourceSprite.width;

		cSprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void CharacterGroup::EffectsOverlay::DisableEffect()
{
	speedModifier = 1;
	frames = 0;
	visible = false;
	isAnimating = false;
	setTex = false;
}

void CharacterGroup::EffectsOverlay::update()
{
	cSprite.setPosition(position);

	if (isAnimating) {
		RunEffect(Enums::Effects::NextTurnHeal);
	}
}


const bool CharacterGroup::EffectsOverlay::FinishedAnim()
{
	return isAnimating;
}
