#include "MenuOverlay.h"

MenuOverlay::MenuOverlay()
{
	SetTexture(TextureBank::Get().MenuPopup);
	SetRectSize(78, 112);
}

MenuOverlay::~MenuOverlay()
{
}

const bool MenuOverlay::IsReturnMenu()
{
	return returnMenu;
}

void MenuOverlay::IsReturnMenu(bool condition)
{
	returnMenu = condition;
}

const bool MenuOverlay::IsOpen()
{
	return open;
}

void MenuOverlay::OpenMenu()
{
	if (!open) {
		SoundBank::Get().Play("openMenu");
		open = true;
	}
}

void MenuOverlay::CloseMenu()
{
	if (open) {
		ResetSelectedButton();
		returnButton.IsToggled(false);
		SoundBank::Get().Play("closeMenu");
		open = false;
		lockAll = false;
	}

}

void MenuOverlay::ResetSelectedButton()
{
	selectedButton = -1;
}

void MenuOverlay::start() {

	if (!returnMenu) {
		playButton.SetType(Enums::ButtonTypes::Play);
		playButton.SetPosition(position + Vector2f(18 * 5, 11 * 5));
		buttons.push_back(&playButton);
	}
	if (returnMenu) {
		returnButton.SetType(Enums::ButtonTypes::Return);
		returnButton.SetPosition(position + Vector2f(15 * 5, 11 * 5));
		buttons.push_back(&returnButton);
	}

	mainMenuButton.SetType(Enums::ButtonTypes::MainMenu);
	mainMenuButton.SetPosition(position + Vector2f(18 * 5, 35 * 5));

	restartButton.SetType(Enums::ButtonTypes::Options);
	restartButton.SetPosition(position + Vector2f(15 * 5, 59 * 5));

	exitButton.SetType(Enums::ButtonTypes::Exit);
	exitButton.SetPosition(position + Vector2f(18 * 5, 83 * 5));

	//keep in this order
	buttons.push_back(&mainMenuButton);
	buttons.push_back(&restartButton);
	buttons.push_back(&exitButton);

	started = true;
}

void MenuOverlay::render(RenderWindow& window)
{
	if (!visible)
		return;

	if (!open)
		return;

	window.draw(this->cSprite);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons[i]->render(window);
	}
}

void MenuOverlay::LockAll()
{
	lockAll = true;
}

void MenuOverlay::UnlockAll()
{
	open = false;
	lockAll = false;
	selectedButton = 0;
}


void MenuOverlay::update(RenderWindow& window)
{
	if (!started)
		start();

	if (!open)
		return;

	restartButton.SetPosition(position + Vector2f(13 * 5, 59 * 5));


	cSprite.setPosition(position);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		buttons[i]->update();
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (Utils::MouseBoundsOf(*buttons[i], window)) {
			ResetSelectedButton();
			buttons[i]->EnterHover();
			selectedButton = i + 1;
		}

		if (selectedButton != i + 1) {
			buttons[i]->ExitHover();
		}
	}

	if (restartButton.IsToggled()) {
		toClose = true;
		CloseMenu();
	}

	if (returnButton.IsToggled()) {
		toClose = true;
		CloseMenu();
	}

	if (exitButton.IsToggled()) {

		exit = true;

		//window.close();
	}

	if (selectedButton > 4) {
		selectedButton = 1;
	}

	if (selectedButton == 0) {
		selectedButton = 4;
	}

	switch (selectedButton) {
	case 1:
		buttons[0]->EnterHover();
		break;

	case 2:
		buttons[1]->EnterHover();
		break;

	case 3:
		buttons[2]->EnterHover();
		break;

	case 4:
		buttons[3]->EnterHover();
		break;
	}
}

void MenuOverlay::HandleEvents(Event& ev, RenderWindow& window)
{
	if (!open)
		return;

	if (lockAll)
		return;

	switch (ev.type) {
	case Event::MouseButtonReleased:
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (Utils::MouseBoundsOf(*buttons[i], window)) {
				buttons[i]->Activate();
			}
		}
		break;

		//Pressing enter while a button is selected with arrowkeys
	case Event::KeyPressed:
		if (ev.key.code == Keyboard::Down) {
			if (selectedButton == -1) {
				selectedButton = 1;
				break;
			}
			selectedButton++;
		}

		if (ev.key.code == Keyboard::Up) {
			if (selectedButton == -1) {
				selectedButton = 4;
				break;
			}
			selectedButton--;
		}

		if (ev.key.code == Keyboard::Enter) {
			if (selectedButton != -1)
				buttons[selectedButton - 1]->Activate();
		}

		break;
	}
}