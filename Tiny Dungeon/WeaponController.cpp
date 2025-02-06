#include "WeaponController.h"


void WeaponController::SetAnimSpeed(float val)
{
	animSpeed = val;
}

WeaponController::WeaponController()
{
	SetRectSize(16, 32);
	visible = true;
	SetTexture(equippedWeapon.weaponTexture);
}


void WeaponController::RandomizeWeapon()
{
	Set(*weapons[rand() % 6]);

	SetTexture(equippedWeapon.weaponTexture);
}

void WeaponController::Set(Weapon newWeapon, bool randomizeStats)
{
	equippedWeapon = newWeapon;

	if (randomizeStats) {

		equippedWeapon.weaponQuality = rarityRoll();

		if (equippedWeapon.id == 3 && Utils::Chance(3) && equippedWeapon.weaponQuality >= 3) {
			cout << "arondight";
		}

		switch (Quality()) {
		case 1:
			cout << "Common" << endl;
			stats().Attack += Utils::RandRange(-3, 3);
			stats().Health += Utils::RandRange(-5, 5);
			stats().Speed += Utils::RandRange(-3, 3);
			if (stats().Healing != 0) {
				stats().Healing += Utils::RandRange(-5, 5);
			}

			if (stats().SpecialEffect != Enums::SpecWpnEfct::None) {
				stats().SpecialEffectVal += Utils::RandRange(-5, 5);
			}

			break;

		case 2:
			cout << "Rare" << endl;
			stats().Attack += Utils::RandRange(-2, 6);
			stats().Health += Utils::RandRange(-4, 10);
			stats().Speed += Utils::RandRange(-2, 5);
			if (stats().Healing != 0) {
				stats().Healing += Utils::RandRange(-4, 10);
			}

			if (stats().SpecialEffect != Enums::SpecWpnEfct::None) {
				stats().SpecialEffectVal += Utils::RandRange(-4, 10);
			}

			break;

		case 3:
			cout << "Epic" << endl;
			stats().Attack += Utils::RandRange(-1, 9);
			stats().Health += Utils::RandRange(-3, 15);
			stats().Speed += Utils::RandRange(-1, 7);
			if (stats().Healing != 0) {
				stats().Healing += Utils::RandRange(-3, 15);
			}

			if (stats().SpecialEffect != Enums::SpecWpnEfct::None) {
				stats().SpecialEffectVal += Utils::RandRange(-3, 15);
			}
			break;

		case 4:
			cout << "Legendary" << endl;
			stats().Attack += Utils::RandRange(0, 12);
			stats().Health += Utils::RandRange(-2, 20);
			stats().Speed += Utils::RandRange(0, 9);
			if (stats().Healing != 0) {
				stats().Healing += Utils::RandRange(-2, 20);
			}

			if (stats().SpecialEffect != Enums::SpecWpnEfct::None) {
				stats().SpecialEffectVal += Utils::RandRange(-2, 20);
			}

			break;

		}

		cout << "atk: " << stats().Attack << endl;
		cout << "hp: " << stats().Health << endl;
		cout << "speed: " << stats().Speed << endl;

		if (stats().Healing != 0)
		cout << "healBonus: " << stats().Healing << endl;

	}

	SetTexture(equippedWeapon.weaponTexture);
}

WeaponEffects& WeaponController::stats()
{
	return equippedWeapon.weaponEffects;
}

const int WeaponController::Quality()
{
	return equippedWeapon.weaponQuality;
}

const string WeaponController::QualityString()
{
	switch (Quality()) {
	case 1:
		return "common";
		break;

	case 2:
		return "rare";
		break;

	case 3:
		return "epic";
		break;

	case 4:
		return "legendary";
		break;

	default:
		return "";
		break;
	}

	return "";
}

const Color WeaponController::RarityColor()
{
	switch (Quality()) {
	case 1:
		return Color(75, 167, 71);
		break;

	case 2:
		return Color(86, 152, 204);
		break;

	case 3:
		return Color(196, 33, 150);
		break;

	case 4:
		return Color(238, 142, 46);
		break;

	default:
		return Color::Black;
		break;
	}
}

const bool WeaponController::HasReplaceSecondary()
{
	switch (stats().SpecialEffect) {
	case Enums::SpecWpnEfct::SecondaryMassHeal:
		return true;
		break;
	}
	return false;
}

void WeaponController::update(Vector2f pos)
{
	if (inactive()) {
		if (visible)
			visible = false;
		return;
	}

	position = pos + Vector2f(-10 + offsetX, 10 + offsetY);

	cSprite.setPosition(position);

	if (!inactive()) {
		if (!visible)
			visible = true;
		return;
	}
}

void WeaponController::update()
{
	if (inactive()) {
		if (visible)
			visible = false;
		return;
	}

	if (moving) {
		MoveTo(targPos);
	}

	cSprite.setPosition(position);

	if (!inactive()) {
		if (!visible)
			visible = true;
		return;
	}
}

void WeaponController::SetState(Enums::cState newState)
{
	ResetAnimLoop();
	state = newState;
}

void WeaponController::render(RenderWindow& window)
{
	if (visible)
		window.draw(this->cSprite);
}

void WeaponController::NextFrame()
{
	if (inactive()) {
		return;
	}

	if (!animating)
	switch (state) {
	case Enums::cState::Move:
		if (animStep == 1) {
			offsetY += 5;
		}

		if (animStep == 2) {
			offsetY -= 15;
			offsetX += 5;
		}

		if (animStep == 3) {
			offsetY += 5;
			offsetX -= 5;
		}

		if (animStep == 4) {
			offsetY += 10;
			offsetX -= 5;
		}
		break;

	case Enums::cState::Idle:
		if (animStep == 1) {
			offsetY += 5;
		}
		if (animStep == 3) {
			offsetY -= 5;
		}
		break;
	}
	
	if (animating) {
		runAnimation();
	}


	animStep++;
}

void WeaponController::ResetAnimLoop()
{
	if (inactive() || animating) {
		return;
	}

	offsetX = 0;
	offsetY = 0;
	animStep = 0;
}

void WeaponController::ClearWeapon()
{
	equippedWeapon.type = Enums::WeaponTypes::None;
	equippedWeapon.id = 0;
	stats().Attack = 0;
	stats().Healing = 0;
	stats().Health = 0;
	stats().Speed = 0;
	stats().SpecialEffect = Enums::SpecWpnEfct::None;
	stats().SpecialEffectVal = 0;
	visible = false;
}

const bool WeaponController::inactive()
{
	if (equippedWeapon.type == Enums::WeaponTypes::None) {
		return true;
	}
	return false;
}

void WeaponController::MoveTo(Vector2f targ)
{
	moving = true;
	targPos = targ;

	Vector2f targetDiff = position - targ;
	float difference = Utils::Length(targetDiff);

	if (Utils::DistanceTo(position, targPos) > 5) {
		position -= (Utils::SetLength(targetDiff, Utils::DistanceTo(position, targPos) / 10)); //5.5f //SPEED	
	}
	else {
		moving = false;
	}

}

void WeaponController::StartAnimation()
{
	if (equippedWeapon.type == Enums::WeaponTypes::None)
		return;

	ResetAnimLoop();
	animating = true;
}

void WeaponController::runAnimation()
{
	switch (animStep) {
	case 0:
		offsetY = 15;
		break;

	case 1:
		offsetX += 5;
		offsetY -= 30;
		break;

	case 2:
		offsetY = -30;
		break;
	case 3:
		offsetY = -5;
		break;

	case 4:
		animating = false;
		ResetAnimLoop();
		break;
	}
}

int WeaponController::rarityRoll()
{
	int rand = Utils::RandRange(100);

	if (rand <= legendaryChance)
		return 4;
	else if (rand <= epicChance)
		return 3;
	else if (rand <= rareChance)
		return 2;
	else
		return 1;

}

