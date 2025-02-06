#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.h"
#include <iostream>

using namespace sf;
using namespace std;

constexpr auto MouseHoverTime = 30;

class WindowEffects {
public:
	Color BoneWhite;
	Color DirtyInk;
	Color DifficultRed;
	Color EasyGreen;
	static WindowEffects& Get();
	void ForceBlack();
	void ForceClear();
	void FadeBlack();
	void SlowFadePartial();
	void FadeClear();
	const bool IsFaded();
	const bool IsCleared();
	void render(RenderWindow& window);
private:	
	bool clearing = false;
	WindowEffects();
	float rectAlpha = 0.0f;
	static WindowEffects WindowEffects_Instance;
	RectangleShape rectShape;

};

