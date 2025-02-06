#include "MoveDetails.h"

MoveDetails::MoveDetails()
{
	if (!typeFont.loadFromFile("Assets/Fonts/typePixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	SetTexture(TextureBank::Get().MoveDetails);

	moveInfoName.setFont(typeFont);

	moveInfoName.setCharacterSize(22);

	moveInfoText.setCharacterSize(16);

	moveInfoText.setFont(typeFont);
	moveInfoText.setPosition(760 - (moveInfoText.getLocalBounds().width) / 2, 1086);

	uiMovePassiveBorder.SetPosition(760 + (77 * 5), 1101);
	this->SetPosition(700, 911);

	//	UiFrame.SetPosition(700, 1101);

	uiMoveCardPrimary.SetPosition(640, 1101);
	uiMoveCardPrimary.SetRectSize(50);

	uiMoveCardSecondary.SetPosition(760, 1101);
	uiMoveCardSecondary.SetRectSize(50);

	moveInfoText.setPosition((this->position - Vector2f(155.0f, 40.0f)));

	moveInfoName.setPosition(698 - (moveInfoName.getLocalBounds().width) / 2, 828.5f);

}

void MoveDetails::update(RenderWindow& window)
{
	cSprite.setPosition(position);

	//Moves the move border's "selected" indicator based on the move clicked upon
	if (selectedMove == 2) {
		this->SetPosition(760, 1101);
	}
	if (selectedMove == 1) {
		this->SetPosition(640, 1101);
	}

	uiMovePassiveBorder.Animate(7, 22, 22, 0.08f);
	uiMoveCardPrimary.update();
	uiMoveCardSecondary.update();

	//Displays information about the hovered move
	if (Utils::MouseBoundsOf(uiMoveCardPrimary, window)) {

		if (moveSelectionCounter >= MouseHoverTime)
		{
			//DisplayMoveInfo(1);
		}
		else {
			moveSelectionCounter++;
		}
	}
	else if (Utils::MouseBoundsOf(uiMoveCardSecondary, window)) {

		if (moveSelectionCounter >= MouseHoverTime) {
			//DisplayMoveInfo(2);
		}
		else {
			moveSelectionCounter++;
		}
	}
	else {
		//ResetInfoText();
	}

}

void MoveDetails::render(RenderWindow& window)
{
	if (visible) {
		window.draw(this->cSprite);
	}

	uiMoveCardPrimary.render(window);
	uiMoveCardSecondary.render(window);
	uiMovePassiveBorder.render(window);
	uiMoveSelectedBorder.render(window);

	window.draw(moveInfoName);
	window.draw(moveInfoText);

}

//Resets the info displayed when hovering over a move as well as the time required to trigger the display of info to zero
void MoveDetails::ResetInfoText(bool resetTimer)
{
	if (resetTimer)
		moveSelectionCounter = 0;

	visible = false;
	moveInfoText.clear();
	moveInfoName.clear();
}