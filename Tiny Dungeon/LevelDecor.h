#pragma once

#include "GameObject.h"
#include "TextureBank.h"
#include "Utils.h"
class LevelDecor
{
private:
	bool centerPillars = false;
	bool bossFountain = false;
	Clock clock;
public:
	LevelDecor();

	vector<shared_ptr<GameObject>> elements;
	vector<shared_ptr<GameObject>> animElements;

	void SetBossFountain(bool cond = true);
	void Randomize();
	void render(RenderWindow& win);
	void update();
};

