#include "Projectile.h"
#include <math.h> 

using namespace CharacterGroup;

Projectile::Projectile()
{

}

Projectile::~Projectile()
{
}

void Projectile::SetType(Enums::PrimaryMove move)
{
	SetRectSize(21);
	cSprite.setOrigin(0, 0);
	rectSourceSprite.left = -21;
	offset = 5;

	switch (move) {
	case Enums::PrimaryMove::ForesterShooterPrimary:
		type = Enums::ProjectileTypes::Forester;
		hasHitSound = true;
		cSprite.setTexture(TextureBank::Get().FShooterProj);
		startSound = "foresterCast";
		hitSound = "foresterCastHit";
		accelerate = true;
		break;

	case Enums::PrimaryMove::BlueMagePrimary:
		type = Enums::ProjectileTypes::BlueMage;
		hasHitSound = true;
		cSprite.setTexture(TextureBank::Get().BlueMageProj);
		startSound = "blueMageCast";
		hitSound = "blueMageHit";
		rotateTowards = true;
		accelerate = true;
		break;

	case Enums::PrimaryMove::ElfRangedPrimary:
		type = Enums::ProjectileTypes::ElfArrow;
		hasHitSound = false;
		cSprite.setTexture(TextureBank::Get().ElfProj);
		startSound = "arrowFire";
		offset = 2.5f;
		cSprite.setOrigin(10.5, 3.5);
		rotateTowards = true;
		isAnimated = false;
		break;
	}

	cSprite.setScale(Utils::GetAppScale());
}

void Projectile::AnimationLoop()
{
	rectSourceSprite.top = 0;
	if (clock.getElapsedTime().asSeconds() > animationSpeed) {
		if (rectSourceSprite.left == 63)
			rectSourceSprite.left = -21;
		else {

		}
		rectSourceSprite.left += 21;

		cSprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void Projectile::SetTarget(GameObject& originGo, GameObject& targetGo) {
	if (!positionSet) {

		SoundBank::Get().Play(startSound);


		SetPosition(originGo.position.x + (float)((originGo.rectSourceSprite.width * 5) / 2) - (float)((21 * offset) / 2), originGo.position.y + (float)((originGo.rectSourceSprite.height * 5) / 2) + (float)((21 * offset) / 2));

		positionSet = true;
	}

	targetSet = true;
	target = &targetGo;
	origin = &originGo;
}

GameObject* CharacterGroup::Projectile::GetTarget() const
{
	return target;
}

void CharacterGroup::Projectile::ClearTarget()
{
	SetPosition(0, 0);
	target = nullptr;
	origin = nullptr;
	positionSet = false;
}

void Projectile::MoveToObject(GameObject& originGo, GameObject& targetGo, RenderWindow& rw)
{
	Vector2f targetDiff(0, 0);

	if (rectSourceSprite.width != 16) {
		targetDiff = position - targetGo.position - Vector2f((float)((targetGo.rectSourceSprite.width * 5) / 2) - (float)((21 * offset) / 2), (float)((targetGo.rectSourceSprite.width * 5) / 2) + (float)((21 * offset) / 2));
	}
	else {
		targetDiff = position - targetGo.position;
	}

	float difference = Utils::Length(targetDiff);

	if (difference >= 55) {
		position -= (Utils::SetLength(targetDiff, projSpeed)); //5.5f

		if (rotateTowards) {

			Vector2f mpos = (Vector2f)Mouse::getPosition(rw);
			float dx = targetGo.position.x - (float)((targetGo.rectSourceSprite.width * 5) / 2) - originGo.position.x + (float)((originGo.rectSourceSprite.width * 5) / 2);
			float dy = targetGo.position.y - (float)((targetGo.rectSourceSprite.width * 5) / 2) - originGo.position.y + (float)((originGo.rectSourceSprite.width * 5) / 2);
			float angle = atan2(dy, dx);
			float targ = angle * (180 / 3.14159);
			cSprite.setRotation(targ);

		}

	}
	else {
		projSpeed = 6;
		if (hasHitSound)
			SoundBank::Get().Play(hitSound);
		targetSet = false;
	}
}

const bool CharacterGroup::Projectile::AtTargetPosition()
{
	if (target == nullptr)
		return false;

	return !targetSet;
}

void Projectile::update(RenderWindow& window)
{
	visible = targetSet;
	if (targetSet) {
		MoveToObject(*origin, *target, window);

		if (accelerate && projSpeed < 15)
			projSpeed *= 1.05f;

		if (!accelerate) {
			projSpeed = 15;
		}
	}
	cSprite.setPosition(position);
	if (isAnimated)
		AnimationLoop();
}

void CharacterGroup::Projectile::render(RenderWindow& window)
{
	if (visible)
		window.draw(this->cSprite);
}
