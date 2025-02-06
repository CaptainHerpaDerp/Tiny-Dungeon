#pragma once
#include "TextureBank.h"
#include <iostream>
#include "GameObject.h"
#include "Enums.h"
#include "Utils.h"
#include "WindowEffects.h"
#include "MoveEffects.h"

using namespace sf;
using namespace std;

constexpr auto MaxEffects = 6;

namespace CharacterGroup {

	class HealthStaminaBar : public GameObject
	{

	private:
		float displayHp = 0;
		float displayStam = 0;

		float dispHpChange = 2;
		float displayStamChange = 5;

		float stamFlashCount;
		float stamFlashDuration = 0.5;
		bool flashed = false;

	public:
		HealthStaminaBar();

		~HealthStaminaBar();

		void BalanceDisplayBars(float hp, float stam);
		void ChangeHealthBarSize(int change);
		void ChangeStaminaBarSize(int change);
		void render(RenderWindow& window);
		void update(float hp, float hpMax, float stam);
		void reloadEffects(vector<pair<MoveEffect, int>> vec);
		void ClearBuffs();
		void DetectMouse(vector<pair<MoveEffect, int>> vec, RenderWindow& window);
		void FlashStamBar();

		//temp
		bool moved = false;
		bool added = false;

		RectangleShape healthRect;
		RectangleShape speedRect;

		GameObject BuffDisplays[6];
	};
}

