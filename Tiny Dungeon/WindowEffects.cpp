#include "WindowEffects.h"

WindowEffects& WindowEffects::Get() {
	return WindowEffects_Instance;
}

void WindowEffects::ForceBlack()
{
	rectAlpha = 255;
	rectShape.setFillColor(Color(0, 0, 0, rectAlpha));
}

void WindowEffects::ForceClear()
{
	rectAlpha = 0;
	rectShape.setFillColor(Color(0, 0, 0, rectAlpha));
}

void WindowEffects::FadeBlack()
{
	if (rectAlpha < 255)
		rectAlpha += (4.25f);
	rectShape.setFillColor(Color(0, 0, 0, rectAlpha));
}

void WindowEffects::SlowFadePartial()
{	
	if (rectAlpha < 230)
		rectAlpha += (2.555f);
	rectShape.setFillColor(Color(0, 0, 0, rectAlpha));
}

void WindowEffects::FadeClear()
{
	clearing = true;
	if (rectAlpha > 0)
		rectAlpha -= (6.375f);
	else
		clearing = false;
	rectShape.setFillColor(Color(0, 0, 0, rectAlpha));
}

const bool WindowEffects::IsFaded()
{
	if (rectAlpha > 254)
		return true;

	else
		return false;
}

const bool WindowEffects::IsCleared()
{
	if (rectAlpha < 1)
		return true;

	else
		return false;
}

WindowEffects::WindowEffects()
{
	BoneWhite = Color(253, 247, 237);

	DirtyInk = Color(72, 59, 58);

	DifficultRed = Color(218, 78, 56);
	
	EasyGreen = Color(75, 167, 71);

	rectShape.setSize(Vector2f(1400, 1200));
	rectShape.setFillColor(Color(110, 110, 110, rectAlpha));
}

void WindowEffects::render(RenderWindow& window) {
	window.draw(rectShape);

	if (clearing) {
		FadeClear();
	}
}

WindowEffects WindowEffects::WindowEffects_Instance;
