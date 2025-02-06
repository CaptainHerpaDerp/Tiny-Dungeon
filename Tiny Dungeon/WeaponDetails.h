#pragma once
#include "WeaponController.h"
#include "GameObject.h"
#include "WindowEffects.h"
#include "Utils.h"
#include "RichText.h"

using namespace sfe;

class WeaponDetails : public GameObject
{
private:
	static const int textElementCount = 7;

	Font font;

	RichText name;
	RichText rarity;
	RichText attack;
	RichText hitpoints;
	RichText speed;
	RichText healBonus;

	RichText textElement[textElementCount]{ name, rarity, attack, hitpoints, speed, healBonus };

	WeaponController* targetWeapon;

	bool active = false;
	bool fadingIn = false;
	bool fadingOut = false;

	float rectAlpha = 255;
	int hoverTime = 0;
	Vector2f mPos;

	void fadeIn();
	void fadeOut();

public:
	WeaponDetails();
	void Display(WeaponController* weapon, RenderWindow& window, bool skipHover = false);
	void DisplayElements();
	void render(RenderWindow& window) override;
	void update() override;
	void Reset();



};

