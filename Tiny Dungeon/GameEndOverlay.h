#pragma once
#include "TextureBank.h"
#include "TextBox.h"
#include "Button.h"
#include "Utils.h"

constexpr auto EndOverlayElements = 4;
class GameEndOverlay
{
private:
	Font font;
	Font typeFont;
	Text Game;
	Text Over;
	Text Return;
	Text textElements[EndOverlayElements]{Game, Over, Return};
	Clock clock;
	TextBox playerNameInput;
	bool started = false;
	bool visible = false;
	bool gameOverLock = false;
	int displayStep = 0;
	string returnedName = "";

public:
	static GameEndOverlay& Get();
	GameEndOverlay();
	void HandleEvents(Event& ev, RenderWindow& window);
	void DisplayElements();
	void start();
	void update();
	void render(RenderWindow& window);
	void Reset();
	const bool Locked();
	const string GetName();
	void SetLock(bool condition);
	static GameEndOverlay GameEndOverlay_Instance;
};

