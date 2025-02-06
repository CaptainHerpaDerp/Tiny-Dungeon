#include "RearrangeIndicator.h"

CharacterGroup::RearrangeIndicator::RearrangeIndicator()
{
	cSprite.setScale(Vector2f(5.0f, 5.0f));

	centered = true;

	cSprite.setTexture(TextureBank::Get().UiRearrangeIndicator);

	SetRectSize(16);

	visible = false;
}

CharacterGroup::RearrangeIndicator::~RearrangeIndicator()
{

}

void CharacterGroup::RearrangeIndicator::update()
{
	Animate(5, 16, 16);
	cSprite.setPosition(position);
}

void CharacterGroup::RearrangeIndicator::ToggleSelected(bool condition)
{
	if (condition == true) {
		cSprite.setColor(Color::Green);
	}

	if (condition == false) {
		cSprite.setColor(WindowEffects::Get().BoneWhite);
	}
}

