#include "GameEndOverlay.h"

GameEndOverlay& GameEndOverlay::Get()
{
	return GameEndOverlay_Instance;
}

GameEndOverlay::GameEndOverlay()
{
	if (!font.loadFromFile("Assets/Fonts/pixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	if (!typeFont.loadFromFile("Assets/Fonts/typePixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	textElements[0].setString("GAME");
	textElements[1].setString("OVER");
	textElements[2].setString("Return");
}

void GameEndOverlay::HandleEvents(Event& ev, RenderWindow& window)
{
	if (displayStep < 3)
		return;

	switch (ev.type)
	{	
	case Event::TextEntered:
		playerNameInput.typedOn(ev);
		break;

	case Event::KeyReleased:
		if (ev.key.code == Keyboard::Enter) {
			returnedName = playerNameInput.GetString();
		}

		if (ev.key.code == Keyboard::Delete) {
			playerNameInput.Clear();
		}
		break;
	case Event::MouseButtonReleased:
		if (Utils::MouseBoundsOf(textElements[2], window)) {
			returnedName = playerNameInput.GetString();
		}
		break;
	}
}

void GameEndOverlay::start()
{
	playerNameInput.SetFont(typeFont);
	playerNameInput.setLimit(5);
	playerNameInput.SetCharacterSize(60);

	for (size_t i = 0; i < EndOverlayElements; i++)
	{
		textElements[i].setFont(font);
		textElements[i].setFillColor(WindowEffects::Get().BoneWhite);
		textElements[i].setCharacterSize(200);
	}

	textElements[0].setPosition(210, 300);
	textElements[1].setPosition(760, 300);
	textElements[2].setCharacterSize(75);
	textElements[2].setPosition(485, 650);
	started = true;
}

void GameEndOverlay::update()
{
	if (!started)
		start();
	textElements[2].setPosition(485 + (textElements[2].getGlobalBounds().width / 2) - 30, 650);

	playerNameInput.SetPosition(Vector2f(695, 550));

	if (displayStep == 2) {
		if (SoundBank::Get().IsMuted())
			return;

		SoundBank::Get().Play("bellRing");
		SoundBank::Get().deathMusic.play();
		SoundBank::Get().deathMusic.setLoop(true);
	}

}

void GameEndOverlay::render(RenderWindow& window)
{
	if (!visible) {
		return;
	}

	if (displayStep >= 1) {
		window.draw(textElements[0]);
	}

	if (displayStep >= 2) {
		window.draw(textElements[1]);
	}

	if (gameOverLock && displayStep >= 3) {
		playerNameInput.render(window);
		window.draw(textElements[2]);

		if (Utils::MouseBoundsOf(textElements[2], window)) {
			textElements[2].setFillColor(WindowEffects::Get().BoneWhite);
		}
		else {
			textElements[2].setFillColor(Color(100, 100, 100));
		}
	}
}

void GameEndOverlay::Reset()
{
	visible = false;
	gameOverLock = false;
	displayStep = 0;
	returnedName = "";
	playerNameInput.Clear();

}

const bool GameEndOverlay::Locked()
{
	return gameOverLock;
}

const string GameEndOverlay::GetName()
{
	return returnedName;
}

void GameEndOverlay::SetLock(bool condition)
{
	gameOverLock = condition;
}

void GameEndOverlay::DisplayElements()
{
	gameOverLock = true;

	if (!visible) {
		clock.restart();
		visible = true;
	}

	if (clock.getElapsedTime().asSeconds() > 0.9f) {
		displayStep = 1;
	}

	if (clock.getElapsedTime().asSeconds() > 1.8f) {
		displayStep = 2;
	}

	if (clock.getElapsedTime().asSeconds() > 2.2f) {
		displayStep = 3;
	}
}

GameEndOverlay GameEndOverlay::GameEndOverlay_Instance;
