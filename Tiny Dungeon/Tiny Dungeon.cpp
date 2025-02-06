/*


will return a const variable

const int something()
{
	return 0;
}


int addToX() const           //constant member function
	{
		++x;                 // Error while attempting to modify the data member
		return x;
	}

void setNum(const int newNum, int otherNum){ //ensures newNum will not be changed
otherNum += newNum;
}


reference cannot be null

pointer can change what they're referencing

references need to be initialized


initializing list

class(Someting& something) : className(something) { } only time to check if a reference is valid


class Class { }; 4 methods exist in this class already, these are:

Default constructor
Class();

Destructor
~Class()

Copy constructor
Class(const Class& other)
excecuted when:
Class a;
Class b = a;

int getVariable() const { return variable }

Copy Assignment Operator
Class& operator={const SimpleClass& other { 
variable = other.getVariable();
}
excecuted when:
Class a = b;

*/




//Moves texturebank problem

//tons of load warnings

//only use smart pointers?

#include "TextureBank.h"
#include <iostream>
#include "HealthStaminaBar.h"
#include "Menu.h"
#include "TextBox.h"
#include <Windows.h>
#include "Scores.h"
#include <fstream>
#include <sstream>
#include "WindowEffects.h"
#include "GameEndOverlay.h"
#include "level.h"
#include "Ally.h"
#include "Enemy.h"

using namespace sf;
using namespace std;
using namespace CharacterGroup;
int main()
{
	bool atMenu = true;

	//to hide console
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOW);

	WINDOWINFO wiInfo;

	string title = "None";
	int framerate = 60;
	int windowHeight = 0;
	int windowWidth = 0;
	float zoom = 1;
	int offsetY = 0;
	string none;

	ifstream ifs("Config/windowPrefs.ini");

	if (ifs.fail()) {
		cout << "failed to open windowPrefs";
	}

	if (ifs.is_open()) {

		getline(ifs, title);
		getline(ifs, none);
		getline(ifs, none);

		ifs >> none >> windowWidth;
		ifs >> none >> windowHeight;
		ifs >> none >> framerate;
	}

	auto desktop = VideoMode::getDesktopMode();

	if (windowWidth == 0 || windowHeight == 0)
		switch (VideoMode::getDesktopMode().height) {
		case 720:
			windowHeight = 720;
			windowWidth = 1200;
			zoom = 1.8;
			offsetY = 250;
			break;

		case 1080:
			windowHeight = 1000;
			windowWidth = 1400;
			zoom = 1.2;
			offsetY = 100;
			break;

		case 1200:
			windowHeight = 1000;
			windowWidth = 1200;
			zoom = 1.2;
			offsetY = 100;
			break;

		case 1440:
		case 2160:
			windowHeight = 1200;
			windowWidth = 1400;
			break;
		}

	View view(sf::Vector2f(windowWidth / 2, windowHeight / 2 + offsetY), sf::Vector2f(windowWidth, windowHeight));
	view.zoom(zoom);
	RenderWindow window(VideoMode(windowWidth, windowHeight), title, Style::Titlebar | Style::Close);
	window.setPosition(Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(framerate);

	sf::Image icon;
	icon.loadFromFile("Assets/Knight/knight_m_hit_anim_f0.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

#pragma region Object_Instantiation
	Clock clock;

	unique_ptr<Level> level (new Level());

	Menu menuScene;

	Event event;

	Map gameMap(TextureBank::Get().GameMap);

	Map menuMap(TextureBank::Get().MenuMap);

	GameObject Door(TextureBank::Get().Door, true);
	Door.SetPosition(700, 101);
	Door.SetRectSize(32 * 2, 36 * 2);

	GameObject UiFrame(TextureBank::Get().UiFrame);
	UiFrame.SetPosition(700, 1101);

	GameObject AllyTurnCircle(TextureBank::Get().TurnCircle);

	GameObject AllyCastIndicator(TextureBank::Get().AllyCastIndicator);
	AllyCastIndicator.visible = false;

	GameObject EnemyCastIndicator(TextureBank::Get().EnemyCastIndicator);
	EnemyCastIndicator.visible = false;

	GameObject UiMoveCardPrimary(TextureBank::Get().KnightPrimary);
	UiMoveCardPrimary.SetPosition(640, 1101);
	UiMoveCardPrimary.SetRectSize(50);

	GameObject UiMoveCardSecondary(TextureBank::Get().KnightSecondary);
	UiMoveCardSecondary.SetPosition(760, 1101);
	UiMoveCardSecondary.SetRectSize(50);

	GameObject MoveDetails(TextureBank::Get().MoveDetails);

	GameObject UiMoveSelectedBorder(TextureBank::Get().UiMoveSelectedBorder);

	GameObject UiMovePassiveBorder(TextureBank::Get().UiMovePassiveBorder);

	GameObject UiCooldownRectP(TextureBank::Get().UiCooldownRect);
	UiCooldownRectP.SetPosition(640, 1101);

	GameObject UiCooldownRectS(TextureBank::Get().UiCooldownRect);
	UiCooldownRectS.SetPosition(760, 1101);

	GameObject CurrentLevelCard(TextureBank::Get().CurrentLevelCard);
	GameObject CurrentLevelCardExtended(TextureBank::Get().CurrentLevelCardExtended);

	gameMap.SetPosition(Vector2f(700, 591));

	menuMap.SetPosition(Vector2f(700, 800));

	Ally menuChar(Enums::AllyTypes::KnightM);
	menuScene.menuCharacter = &menuChar;

	menuScene.setMap(menuMap);

	Ally rewardChar(Enums::AllyTypes::KnightM);
	rewardChar.hpBar.visible = false;
#pragma endregion

#pragma region Level_Linking
	level->RewardChar = &rewardChar;

	level->setMap(gameMap);

	level->door = &Door;
	level->AddGameObject(Door);

	level->AddGameObject(UiCooldownRectP);

	level->uiAllyCircle = &AllyTurnCircle;
	level->AddGameObject(AllyTurnCircle);

	level->allyCastIndicator = &AllyCastIndicator;
	level->AddGameObject(AllyCastIndicator);

	level->enemyCastIndicator = &EnemyCastIndicator;
	level->AddGameObject(EnemyCastIndicator);

	level->uiMoveCardPrimary = &UiMoveCardPrimary;
	level->uiMoveCardSecondary = &UiMoveCardSecondary;

	level->uiMoveSelectedBorder = &UiMoveSelectedBorder;
	level->AddGameObject(UiMoveSelectedBorder);

	level->uiMovePassiveBorder = &UiMovePassiveBorder;
	level->AddGameObject(UiMovePassiveBorder);

	level->uiCooldownRect = &UiCooldownRectS;
	level->AddGameObject(UiCooldownRectS);

	level->moveDetailsFrame = &MoveDetails;
	level->AddGameObject(MoveDetails);

	level->currentLevelCard = &CurrentLevelCard;
	level->AddGameObject(CurrentLevelCard);

	level->currentLevelCardExtended = &CurrentLevelCardExtended;
	level->AddGameObject(CurrentLevelCardExtended);

	level->uiFrame = &UiFrame;
	level->AddGameObject(UiFrame);

	//Allies
	unique_ptr<Ally> player1(new Ally(Enums::AllyTypes::KnightM));
	level->AddCharacter(*player1, 3);

	unique_ptr<Ally> player2(new Ally(Enums::AllyTypes::KnightM));
	level->AddCharacter(*player2, 4, false);

	unique_ptr<Ally> player3(new Ally(Enums::AllyTypes::KnightM));
	level->AddCharacter(*player3, 1, false);

	unique_ptr<Ally> player4(new Ally(Enums::AllyTypes::KnightM));
	level->AddCharacter(*player4, 2, false);

	//Enemies
	unique_ptr<Enemy> enemy1(new Enemy(Enums::EnemyTypes::MiniForester));
	level->AddCharacter(*enemy1, -1);

	unique_ptr<Enemy> enemy2(new Enemy(Enums::EnemyTypes::MiniForester));
	level->AddCharacter(*enemy2, -2);

	unique_ptr<Enemy> enemy3(new Enemy(Enums::EnemyTypes::MiniForester));
	level->AddCharacter(*enemy3, -3);

	unique_ptr<Enemy> enemy4(new Enemy(Enums::EnemyTypes::MiniForester));
	level->AddCharacter(*enemy4, -4);

	unique_ptr<Enemy> enemy5(new Enemy(Enums::EnemyTypes::MiniForester));
	level->AddCharacter(*enemy5, -5);

#pragma endregion

	while (window.isOpen())
	{
		window.setView(view);

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (!atMenu)
				level->HandleEvents(event, window);

			if (atMenu)
				menuScene.HandleEvents(event, window);

			GameEndOverlay::Get().HandleEvents(event, window);
		}

		if (event.type == Event::KeyPressed) {
			menuScene.scoreOverlay.reloadScores();
		}

		window.clear(Color::Black);

		if (menuScene.IsStartSelected()) {
			SoundBank::Get().menuMusic.stop();
		//	transforms the first player into the selected menu character
			player1->Transmog(menuScene.menuCharacter->type);

			level->SetPdMode(menuScene.GetPermaDeath());

			player1->Reset();
			atMenu = false;
			menuScene.Reset();
		}

		//at main menu
		if (atMenu) {
			menuScene.update(window);
			menuScene.render(window);
		}

		//in game
		if (!atMenu) {
			level->update(window);
			level->render(window);
			
			if (level->RequestReturnMenu()) {
				SoundBank::Get().StopSongs();
				level->ResetAll();		
				level->SetStartRoutine(false);
				menuScene.LoadSaveData();
				atMenu = true;
			}
		}

		//If loss
		if (level->LevelStatus() == 2 && !atMenu) {
			SoundBank::Get().bossSong.stop();
			WindowEffects::Get().SlowFadePartial();
			GameEndOverlay::Get().DisplayElements();
			if (GameEndOverlay::Get().GetName() != "") {
				Scores::Get().ClearSave();
				Scores::Get().AddScore(GameEndOverlay::Get().GetName(), level->currentLevel, level->GetPdMode());
				GameEndOverlay::Get().Reset();
				WindowEffects::Get().ForceClear();
				menuScene.scoreOverlay.reloadScores();
				atMenu = true;
				SoundBank::Get().deathMusic.stop();
				level->ResetAll();
				level->SetStartRoutine(false);
			}
		}

		//If level is beaten
		if (level->LevelStatus() == 1) {
			level->NextLevel();
		}

		WindowEffects::Get().render(window);
		GameEndOverlay::Get().update();
		GameEndOverlay::Get().render(window);

		window.display();
	}

	return 0;
}
