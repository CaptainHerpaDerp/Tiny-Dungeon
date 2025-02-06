#pragma once

#include "GameObject.h"
#include "RichText.h"
#include "TextureBank.h"
#include "Utils.h"
#include "WindowEffects.h"

using namespace sfe;

class MoveDetails : GameObject
{
private:

	int moveSelectionCounter = 0;

	int selectedMove = 0;

	Font typeFont;

	RichText moveInfoName;
	RichText moveInfoText;

	GameObject moveDetailsFrame;
	GameObject uiMoveCardPrimary;
	GameObject uiMoveCardSecondary;
	GameObject uiMovePassiveBorder;
	GameObject uiMoveSelectedBorder;

public:

	MoveDetails();

	void update(RenderWindow& window);
	void render(RenderWindow& window) override;
	void ResetInfoText(bool resetTimer);


};

