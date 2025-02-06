#pragma once
#include "GameObject.h"
#include "Button.h"
#include <Windows.h>
#include "Utils.h"
#include "SoundBank.h"

class MenuOverlay : public GameObject
{

private:
	bool returnMenu = false;

	Button playButton;
	Button returnButton;
	Button menuButton;
	Button exitButton;

	vector<Button*> buttons;

	int selectedButton = 0;
	bool playSound = false;
	bool started = false;
	bool open = false;
	bool lockAll = false;

public:

	MenuOverlay();
	~MenuOverlay();

	Button mainMenuButton;
	Button restartButton;
	bool exit = false;
	bool toClose = false;
	const bool IsReturnMenu();
	void IsReturnMenu(bool condition);
	const bool IsOpen();
	void OpenMenu();
	void CloseMenu();
	void ResetSelectedButton();
	void HandleEvents(Event& ev, RenderWindow& window);
	void start();
	void update(RenderWindow& window);
	void render(RenderWindow& window) override;
	void LockAll();
	void UnlockAll();
};

