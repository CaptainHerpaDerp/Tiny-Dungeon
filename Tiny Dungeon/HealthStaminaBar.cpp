#include "HealthStaminaBar.h"

using namespace sf;
using namespace std;
using namespace CharacterGroup;



HealthStaminaBar::HealthStaminaBar() : GameObject()
{
	healthRect.setFillColor(Color(218, 78, 56));
	speedRect.setFillColor(Color(86, 152, 204));

	healthRect.setSize(Vector2f(60.0f, 5.0f));
	speedRect.setSize(Vector2f(60.0f, 5.0f));

	cSprite.setScale(Vector2f(5.0f, 5.0f));

	cSprite.setTexture(TextureBank::Get().HpStaminaBar);

	for (size_t i = 0; i < MaxEffects; i++)
	{
		BuffDisplays[i].cSprite.setScale(Utils::GetAppScale());
		BuffDisplays[i].SetRectSize(5);
		BuffDisplays[i].visible = false;
	}
}

HealthStaminaBar::~HealthStaminaBar()
{
}

void CharacterGroup::HealthStaminaBar::BalanceDisplayBars(float hp, float stam)
{
	displayHp = hp;
	displayStam = stam;
}

void HealthStaminaBar::ChangeHealthBarSize(int change)
{
	if (healthRect.getSize().x - change < 2 && change == -1) {
		return;
	}

	if (healthRect.getSize().x - change > 58 && change == 1) {
		return;
	}

	healthRect.setSize(healthRect.getSize() + Vector2f(change, 0));

}

void HealthStaminaBar::ChangeStaminaBarSize(int change)
{
	if (speedRect.getSize().x - change < 2 && change == -1) {
		return;
	}

	if (speedRect.getSize().x - change > 58 && change == 1) {
		return;
	}

	speedRect.setSize(speedRect.getSize() + Vector2f(change, 0));
}

void HealthStaminaBar::render(RenderWindow& window)
{
	if (visible) {
		window.draw(this->cSprite);
		window.draw(this->healthRect);
		window.draw(this->speedRect);
		for (size_t i = 0; i < MaxEffects; i++)
		{
			if (!BuffDisplays[i].visible)
				continue;

			window.draw(BuffDisplays[i].cSprite);
		}

	}
}

void HealthStaminaBar::update(float hp, float maxHp, float stam)
{
#pragma region DisplayBars
	//Sets display hp and bars equal to their true values, but slows the speed at which they fill.
	//If the added value(fill speed) to the display is greater than the true value, copies true value.
	if (displayHp > maxHp || displayHp <= 0)
		displayHp = maxHp;

	if (displayStam > stam || displayStam <= 0)
		displayStam = stam;

	if (displayHp > hp) {
		if (displayHp - dispHpChange < hp) {
			displayHp = hp;
		}
		else
			displayHp -= dispHpChange;
	}

	if (displayHp < hp) {
		if (displayHp + dispHpChange > hp) {
			displayHp = hp;
		}
		else
			displayHp += dispHpChange;
	}

	if (displayStam > stam) {
		if (displayStam - displayStamChange < stam) {
			displayStam = stam;
		}
		else
			displayStam -= displayStamChange;
	}

	if (displayStam < stam) {
		if (displayStam + displayStamChange > stam) {
			displayStam = stam;
		}
		else
			displayStam += displayStamChange;
	}
#pragma endregion

	if (flashed) {
		stamFlashCount += 0.1f;
		if (stamFlashCount > stamFlashDuration) {
			speedRect.setFillColor(Color(86, 152, 204));
			flashed = false;
		}

	}

	speedRect.setSize(Vector2f(displayStam * 0.6f, 5.0f));
	healthRect.setSize(Vector2f((displayHp / maxHp) * 60, 5.0f));

	cSprite.setPosition(position);
	healthRect.setPosition(position + Vector2f(4.6f, 4.5f));
	speedRect.setPosition(position + Vector2f(4.6f, 14.5f));
}

void CharacterGroup::HealthStaminaBar::reloadEffects(vector<pair<MoveEffect, int>> vec)
{
	int buffX = this->position.x + 75;
	int buffY = this->position.y;
	int buffI = 0;

	for (size_t i = 0; i < vec.size(); i++)
	{
		switch (vec[i].first.action) {

		case Enums::Effects::Shield:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().DefBf);
			break;

		case Enums::Effects::NextTurnHeal:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().HealBf);
			break;

		case Enums::Effects::BreakShield:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().DefDbf);
			break;

		case Enums::Effects::Stun:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().StunDbf);
			break;

		case Enums::Effects::Dot:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().DotDbf);
			break;

		case Enums::Effects::Attack:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().AtkBf);
			break;

		case Enums::Effects::BreakAttack:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().AtkDbf);
			break;

		case Enums::Effects::BlockHeal:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().BlockHealDbf);
			break;

		case Enums::Effects::Speed:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().SpeedBf);
			break;

		case Enums::Effects::ReduceSpeed:
			BuffDisplays[i].cSprite.setTexture(TextureBank::Get().SpeedDbf);
			break;
		}

		if (vec[i].second > 0) {
			BuffDisplays[i].visible = true;
			BuffDisplays[i].SetPosition(buffX, buffY);
			buffX += 30;
			buffI++;
			if (buffI == 3) {
				buffX = this->position.x + 75;
				buffY += 30;
			}
		}

		if (vec[i].second <= 0) {
			BuffDisplays[i].visible = false;
		}

		BuffDisplays[i].update();
	}
}

void CharacterGroup::HealthStaminaBar::ClearBuffs()
{
	for (size_t i = 0; i < MaxEffects; i++)
	{
		BuffDisplays[i].visible = false;
	}
}

void CharacterGroup::HealthStaminaBar::DetectMouse(vector<pair<MoveEffect, int>> vec, RenderWindow& window)
{
	for (size_t i = 0; i < MaxEffects; i++)
	{
		if (!BuffDisplays[i].visible)
			continue;

		if (Utils::MouseBoundsOf(BuffDisplays[i], window)) {

			switch (vec[i].first.action) {

			case Enums::Effects::Shield:
				cout << "shield";
				break;

			case Enums::Effects::NextTurnHeal:
				cout << "nextHeal";
				break;

			case Enums::Effects::BreakShield:
				cout << "breakShield";
				break;

			case Enums::Effects::Stun:
				cout << "stun";
				break;

			case Enums::Effects::Dot:
				cout << "dot";
				break;

			case Enums::Effects::Attack:
				cout << "Atk";
				break;

			case Enums::Effects::BreakAttack:
				cout << "breakAtk";
				break;

			case Enums::Effects::Speed:
				cout << "speed";
				break;
			}
		}
	}
}

void CharacterGroup::HealthStaminaBar::FlashStamBar()
{
	stamFlashCount = 0;
	flashed = true;
	speedRect.setFillColor(WindowEffects::Get().BoneWhite);
}





