#pragma once
#include "Scene.h"
#include "Utils.h"
#include "Ally.h"
#include "WindowEffects.h"
#include "ScoreOverlay.h"
#include "SaveFileReader.h"
#include <fstream>
#include <sstream>
#include "RichText.h"
#include "SoundBank.h"

using namespace sfe;
using namespace std;
using namespace sf;
using namespace CharacterGroup;


class Menu : public Scene
{
private:
	float hoverTime;
	bool pdMode = false;
	bool started = false;
	bool MenuSelected = false;
	bool StartSelected = false;
	bool showContinueOverlay = false;
	bool hoveringClear;
	int offset = -50;
	bool playingMusic = false;
	const static int menuElemnts = 7;
	string test;
	GameObject ContinuePopup;

	Font font;
	Font typeFont;
	vector<Text> renderedElements;
	Text menuElement[menuElemnts];
	Text* selectedElement;
	Text SaveGameLevel;
	Text lastSaveDate;
	Text lastSaveLevel;

	RichText lastSaveDifficulty;
	RichText diffExp;

public:

	Menu();
	void InitializeButtons();
	~Menu();
	
	int buttonSelected;

	Ally* menuCharacter;

	ScoreOverlay scoreOverlay;

	int selectedChar = 0;

	Event event;

	void render(RenderWindow& window) override;

	void start();

	void LoadSaveData();

	void Reset();

	void update(RenderWindow& window);

	void HandleEvents(Event& ev, RenderWindow& window);

	void ExitMenu();

	void PlayMusic();
	void StopMusic();

	const bool GetPermaDeath();
	const bool IsMenuSelected();
	const bool IsStartSelected();
};



