#include "WeaponDetails.h"

WeaponDetails::WeaponDetails()
{
	if (!font.loadFromFile("Assets/Fonts/typePixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	for (size_t i = 0; i < unsigned(textElementCount); i++)
	{
		textElement[i].setFont(font);
		//textElement[i].setCharacterColor(WindowEffects::Get().DirtyInk);
		textElement[i] << WindowEffects::Get().DirtyInk;
		textElement[i].setCharacterSize(20);
	}

	textElement[0].setCharacterSize(21);
	SetPosition(Vector2f(700 - (63 * 2.5f) - 2, 500 - (80 * 2.5f) + 1));
	SetTexture(TextureBank::Get().WeaponDetails);
	SetRectSize(64, 80);

}

void WeaponDetails::fadeIn()
{
	if (!fadingIn) {
		rectAlpha = 0;
	}
	fadingIn = true;
	fadingOut = false;
	if (rectAlpha < 255)
		rectAlpha += (6.375f * 4);

	cSprite.setColor(Color(255, 255, 255, rectAlpha));
}

void WeaponDetails::fadeOut()
{
	if (active)
		return;
	if (!fadingOut) {
		rectAlpha = 255;
	}
	fadingOut = true;
	if (rectAlpha > 1) {
		rectAlpha -= (6.375f * 8);
	}
	else {
		fadingOut = false;
		visible = false;
	}

	cSprite.setColor(Color(255, 255, 255, rectAlpha));
}

void WeaponDetails::Display(WeaponController* weapon, RenderWindow& rw, bool skipHover)
{
	if (!weapon->visible)
		return;

	if (Utils::MouseBoundsOf(*weapon, rw)) {
		if (active)
			return;

		if (!skipHover && hoverTime < MouseHoverTime) {
			hoverTime++;
			return;
		}
		
		active = true;
		targetWeapon = weapon;
		DisplayElements();
	}

	if (active)
	if (!Utils::MouseBoundsOf(*targetWeapon, rw)) {
		Reset();
	}
}

void WeaponDetails::DisplayElements()
{
	textElement[0] << (targetWeapon->equippedWeapon.name);
	textElement[0].setOrigin(Vector2f(textElement[0].getLocalBounds().width / 2, textElement[0].getLocalBounds().height / 2));
	textElement[0].setPosition(position + Vector2f(Utils::CenterOf(*this, 'x'), 55));

	textElement[1] << targetWeapon->RarityColor() << (targetWeapon->QualityString());
	textElement[1].setOrigin(Vector2f(textElement[1].getLocalBounds().width / 2, textElement[1].getLocalBounds().height / 2));
	textElement[1].setPosition(position + Vector2f(Utils::CenterOf(*this, 'x'), 107));

	auto index = 2;

	if (targetWeapon->stats().Attack != 0) {
		int* cur = &targetWeapon->stats().Attack;
		textElement[index] << "Attack " << Utils::Cov(*cur) << Utils::PosOrNeg(*cur) + to_string(*cur);
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().Health != 0) {
		int* cur = &targetWeapon->stats().Health;
		textElement[index] << "Hp " << Utils::Cov(*cur) << Utils::PosOrNeg(*cur) + to_string(*cur);
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().Speed != 0) {
		int* cur = &targetWeapon->stats().Speed;
		textElement[index] << "Speed " << Utils::Cov(*cur) << Utils::PosOrNeg(*cur) + to_string(*cur);
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().Healing != 0) {
		int* cur = &targetWeapon->stats().Healing;
		textElement[index] << "Heal " << Utils::Cov(*cur) << Utils::PosOrNeg(*cur) + to_string(*cur) << "%";
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().SpecialEffect == Enums::SpecWpnEfct::ApplyRandomDebuff) {
		int* cur = &targetWeapon->stats().SpecialEffectVal;
		textElement[index].setCharacterSize(15);
		textElement[index] << "Chance to apply a\nrandom debuff to\n" << Text::Bold << "enemy" << Text::Regular << " upon\nattacking them(" << Utils::Cov(*cur) << to_string(*cur) << "%" << WindowEffects::Get().DirtyInk << ")";
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().SpecialEffect == Enums::SpecWpnEfct::ApplyRandomBuff) {
		int* cur = &targetWeapon->stats().SpecialEffectVal;
		textElement[index].setCharacterSize(13);
		textElement[index] << "Chance to apply a\nrandom buff to " << Text::Bold << "other" << Text::Regular << "\nally upon targetting\nthem with a move(" << Utils::Cov(*cur) <<  to_string(*cur) << "%" << WindowEffects::Get().DirtyInk << ")";
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().SpecialEffect == Enums::SpecWpnEfct::BonusHeal) {
		int* cur = &targetWeapon->stats().SpecialEffectVal;
		textElement[index].setCharacterSize(15);
		textElement[index] << "Healing an ally\n(including self)\nwith an ability is\n" << Utils::Cov(*cur) << to_string(*cur) << "% " << WindowEffects::Get().DirtyInk << "more effective";
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}

	if (targetWeapon->stats().SpecialEffect == Enums::SpecWpnEfct::SecondaryMassHeal) {
		int* cur = &targetWeapon->stats().SpecialEffectVal;
		textElement[index].setCharacterSize(15);
		textElement[index] << "Secondary skill is\nreplaced with\n"<< Text::Bold << "Cleansing Heal" << Text::Regular <<",\nhealing all allies\nfor " << Utils::Cov(*cur) << to_string(*cur) << WindowEffects::Get().DirtyInk << " points and\nremoving debuffs";;
		textElement[index].setPosition(position + Vector2f(50, 70 + (index * 35)));
		index++;
	}
}

void WeaponDetails::update()
{
	cSprite.setPosition(position);

	if (active)
		fadeIn();

	if (fadingOut)
		fadeOut();

	if (active){
		visible = true;
	}
	else {
		fadingIn = false;
		fadingOut = true;
	}
}

void WeaponDetails::Reset()
{
	active = false;
	fadingIn = false;
	fadingOut = false; 
	targetWeapon = nullptr;
	hoverTime = 0;
	for (size_t i = 0; i < textElementCount; i++)
	{
		textElement[i].clear();
		textElement[i].setCharacterSize(20);
		textElement[i] << WindowEffects::Get().DirtyInk;
	}
}

void WeaponDetails::render(RenderWindow& window)
{
	if (!visible)
		return;

		window.draw(this->cSprite);

		if(!fadingOut)
		for (size_t i = 0; i < textElementCount; i++)
		{
			window.draw(textElement[i]);
		}
}