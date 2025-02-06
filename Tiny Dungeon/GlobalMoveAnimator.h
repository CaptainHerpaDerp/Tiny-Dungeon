#pragma once
#include "GameObject.h"
#include "Moves.h"
class GlobalMoveAnimator : public GameObject
{
private:
	bool setType = false;
	int frames = 0;
	bool animating = false;
	SecondaryMove move;
	int offsetX = 0;
	int offsetY = 0;
	Vector2f originalPos;
public:

	GlobalMoveAnimator();
	int Animate(SecondaryMove move);
	const bool IsAnimating();
	void Reset();
	void update() override;
};


