#include "GlobalMoveAnimator.h"

GlobalMoveAnimator::GlobalMoveAnimator()
{
	SetRectSize(93, 78);
	cSprite.setScale(Utils::GetAppScale());
	position = Vector2f(94 * 5, 24 * 5);
	originalPos = position;
}

int GlobalMoveAnimator::Animate(SecondaryMove newMove)
{
	if (!setType) {	
		move = newMove;
		switch (newMove.type) {
		case Enums::SecondaryMove::ElfRangedSecondary:
			animating = true;
			cSprite.setTexture(TextureBank::Get().ElfVolley);
			frames = 14;
			break;

		case Enums::SecondaryMove::ShamanOrcSecondary:
			animating = true;
			cSprite.setTexture(TextureBank::Get().ShamanSecondary);
			frames = 21;
			offsetY = 75;
			break;

		case Enums::SecondaryMove::OrcBossSecondary:
			animating = true;
			cSprite.setTexture(TextureBank::Get().OrcBossSecondary);
			frames = 14;
			offsetY = 75;
			break;

		default:
			return 0;
		break;
		}
		
		SetPosition(position.x + offsetX, position.y + offsetY);
		setType = true;
	}

	if (clock.getElapsedTime().asSeconds() > 0.06f) {
		if (rectSourceSprite.left == rectSourceSprite.width * frames) {
			//end of spriteSheet
			rectSourceSprite.left = -rectSourceSprite.width;
			animating = false;
			Reset();
			return 1;
		}

		rectSourceSprite.left += rectSourceSprite.width;

		cSprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}

	return 0;
}

const bool GlobalMoveAnimator::IsAnimating()
{
	return animating;
}

void GlobalMoveAnimator::Reset()
{
	SetPosition(originalPos);
	offsetY = 0;
	offsetX = 0;
	setType = false;
}

void GlobalMoveAnimator::update()
{
	cSprite.setPosition(position);
	if (animating) {
		Animate(move);
	}
}
