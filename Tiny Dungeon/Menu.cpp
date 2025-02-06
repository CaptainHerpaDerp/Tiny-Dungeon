#include "Menu.h"

Menu::Menu()
{

	if (!font.loadFromFile("Assets/Fonts/pixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	if (!typeFont.loadFromFile("Assets/Fonts/typePixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	diffExp.setFont(typeFont);
	diffExp << WindowEffects::Get().BoneWhite;
	diffExp.setCharacterSize(25);
	diffExp.setPosition(950, 220);

	lastSaveDifficulty.setFont(typeFont);
	lastSaveDifficulty << WindowEffects::Get().BoneWhite;
	lastSaveDifficulty.setCharacterSize(25);
	lastSaveDifficulty.setPosition(700, 350);

	ContinuePopup.SetTexture(TextureBank::Get().SaveFound);

	InitializeButtons();
	MenuSelected = false;
}

void Menu::InitializeButtons()
{
	//Title
	menuElement[0].setFont(font);
	menuElement[0].setFillColor(WindowEffects::Get().BoneWhite);
	menuElement[0].setString("TINY DUNGEON");
	menuElement[0].setCharacterSize(100);
	menuElement[0].setPosition(600 - (float)(menuElement[0].getLocalBounds().width / 3), 80 + offset);

	//Start
	menuElement[1].setFont(font);
	menuElement[1].setFillColor(WindowEffects::Get().BoneWhite);
	menuElement[1].setString("start");
	menuElement[1].setCharacterSize(70);
	menuElement[1].setPosition(600, 330 + offset);

	//Permadeath
	menuElement[2].setFont(font);
	menuElement[2].setFillColor(WindowEffects::Get().DifficultRed);
	menuElement[2].setString("permadeath");
	menuElement[2].setLetterSpacing(2);
	menuElement[2].setCharacterSize(70);
	menuElement[2].setPosition(490, 250 + offset);

	//Regular
	menuElement[3].setFont(font);
	menuElement[3].setFillColor(WindowEffects::Get().EasyGreen);
	menuElement[3].setString("regular");
	menuElement[3].setLetterSpacing(2);
	menuElement[3].setCharacterSize(70);
	menuElement[3].setPosition(545, 250 + offset);

	//Exit
	menuElement[4].setFont(font);
	menuElement[4].setFillColor(WindowEffects::Get().BoneWhite);
	menuElement[4].setString("exit");
	menuElement[4].setLetterSpacing(2);
	menuElement[4].setCharacterSize(70);
	menuElement[4].setPosition(600 + 15, 410 + offset);

	//Load Save
	menuElement[5].setFont(typeFont);
	menuElement[5].setFillColor(WindowEffects::Get().BoneWhite);
	menuElement[5].setString("load");
	menuElement[5].setCharacterSize(30);
	menuElement[5].setPosition(760, 400);

	//Delete Save
	menuElement[6].setFont(typeFont);
	menuElement[6].setFillColor(WindowEffects::Get().BoneWhite);
	menuElement[6].setString("delete");
	menuElement[6].setCharacterSize(30);
	menuElement[6].setPosition(540, 400);

}

Menu::~Menu()
{
}

void Menu::start()
{
	scoreOverlay.SetPosition(500, 500);
	ContinuePopup.SetRectSize(85, 60);
	ContinuePopup.SetPosition(487.5, 175);
	lastSaveDate.setFillColor(WindowEffects::Get().BoneWhite);
	lastSaveDate.setFont(typeFont);

	lastSaveLevel.setFillColor(WindowEffects::Get().BoneWhite);
	lastSaveLevel.setFont(typeFont);

	lastSaveDifficulty.setPosition(565, 350);
	lastSaveDifficulty.setCharacterSize(30);

	LoadSaveData();

	started = true;

}

void Menu::LoadSaveData()
{
	lastSaveDifficulty.clear();

	lastSaveDate.setString(SaveFileReader::Get().GetSaveDate());
	lastSaveDate.setPosition(700 - (float)(lastSaveDate.getLocalBounds().width / 2), 300);
	lastSaveLevel.setString(SaveFileReader::Get().GetSaveLevel());
	lastSaveLevel.setPosition(765 - (float)(lastSaveLevel.getLocalBounds().width / 2), 350);

	bool diff = SaveFileReader::Get().GetSaveDifficulty();
	if (diff == 0) {
		pdMode = false;
		lastSaveDifficulty << WindowEffects::Get().EasyGreen << "Reg";
	}
	else if (diff == 1) {
		pdMode = true;
		lastSaveDifficulty << Color(218, 78, 56) << "Pd";
	}
}

void Menu::render(RenderWindow& window)
{
	buttonSelected = 0;

	map.DrawMap(window);
	scoreOverlay.render(window);

	menuCharacter->render(window);
	menuCharacter->update();
	menuCharacter->SetPosition(660, 660);


	for (size_t i = 0; i < menuElemnts; i++)
	{

		if (i != 6 && i != 5 && i != 2 && i != 3) {
			window.draw(menuElement[i]);
		}

		if (i == 0)
			continue;

		if (Utils::MouseBoundsOf(menuElement[i], window)) {
			
			if (selectedElement != &menuElement[i] && i != 6 && i != 5) {
				if (i == 2 && !pdMode)
					continue;
				if (i == 3 && pdMode)
					continue;

				selectedElement = &menuElement[i];
				SoundBank::Get().Play("hover");
			}

			menuElement[i].setFillColor(WindowEffects::Get().BoneWhite);
			buttonSelected = i;
			if (!showContinueOverlay)
			if (i == 2 || i == 3) {
				if (hoverTime < MouseHoverTime + 1) {
					hoverTime++;
				}

				if (hoverTime == MouseHoverTime) {
					if (pdMode) {
						diffExp << "Fallen allies and\ntheir weapons stay\neliminated, though\nthey may be replaced";
					}
					else {
						diffExp << "Fallen allies are\nrevived after every\ncompleted stage";
					}
				}

			}
		}
		//deselection colours
		else {

			if (selectedElement == &menuElement[i]) {
				selectedElement = nullptr;
			}

			if (i == 2) {
				hoverTime = 0;
				diffExp.clear();
				menuElement[i].setFillColor(Color(218, 78, 56));
			}
			else if (i == 3) {
				diffExp.clear();
				hoverTime = 0;
				menuElement[i].setFillColor(WindowEffects::Get().EasyGreen);
			}
			else {
				menuElement[i].setFillColor(Color(100, 100, 100));
				
			}
		}
	}

	if (Utils::MouseBoundsOf(scoreOverlay.clearScoresText, window)) {
		if (!hoveringClear) {
			SoundBank::Get().Play("hover");
			hoveringClear = true;
		}
		scoreOverlay.clearScoresText.setFillColor(WindowEffects::Get().BoneWhite);
		buttonSelected = 7;
	}
	else {
		hoveringClear = false;
		scoreOverlay.clearScoresText.setFillColor(Color(100, 100, 100));
	}

	if (showContinueOverlay) {

		ContinuePopup.render(window);
		window.draw(lastSaveDate);
		window.draw(lastSaveLevel);
		window.draw(menuElement[5]);
		window.draw(menuElement[6]);
		window.draw(lastSaveDifficulty);
	}
	else {

		if (pdMode) {
			window.draw(menuElement[2]);
		}
		else {
			window.draw(menuElement[3]);
		}
		window.draw(diffExp);
	}
}

void Menu::Reset() {
	StartSelected = false;
	MenuSelected = false;
}

void Menu::update(RenderWindow& window)
{
	if (!started)
		start();

	ContinuePopup.update();
	scoreOverlay.update();
	PlayMusic();

}

void Menu::HandleEvents(Event& ev, RenderWindow& window)
{
	switch (ev.type) {
	case Event::MouseButtonReleased:

		if (Utils::MouseBoundsOf(*menuCharacter, window)) {
			SoundBank::Get().Play("selectCharacter");
			selectedChar++;
			if (selectedChar > 3)
				selectedChar = 0;

			switch (selectedChar) {
			case 0:
				menuCharacter->Transmog(Enums::AllyTypes::KnightM, false);
				break;

			case 1:
				menuCharacter->Transmog(Enums::AllyTypes::KnightF, false);
				break;

			case 2:
				menuCharacter->Transmog(Enums::AllyTypes::KnightP, false);
				break;

			case 3:
				menuCharacter->Transmog(Enums::AllyTypes::KnightG, false);
				break;
			}

		}

		switch (buttonSelected) {
			//start
		case 1:
			if (showContinueOverlay)
				return;

			if (SaveFileReader::Get().HasSave()) {
				showContinueOverlay = true;
				break;
			}
			else {
				WindowEffects::Get().ForceBlack();
				StartSelected = true;
				break;
			}
			break;

		case 2:
		case 3:
			if (showContinueOverlay)
				return;

			diffExp.clear();
			hoverTime = MouseHoverTime - 1;
			pdMode = !pdMode;
			break;

			//exit
		case 4:
			if (!showContinueOverlay) {
				window.close();
			}
			break;

			//load save
		case 5:
			if (!showContinueOverlay)
			return;
			ExitMenu();
			break;

			//delete save
		case 6:
			if (!showContinueOverlay)
				return;			
			SaveFileReader::Get().ClearSave();
			ExitMenu();
			break;

			//clear score
		case 7:
			cout << "clear";
			scoreOverlay.ClearScores();
			break;

		default:
			break;
		}

		break;
	}
}

void Menu::ExitMenu()
{
	StopMusic();
	WindowEffects::Get().ForceBlack();
	showContinueOverlay = false;
	StartSelected = true;
}

void Menu::PlayMusic()
{
	if (!playingMusic) {
		if (SoundBank::Get().IsMuted())
			return;

		SoundBank::Get().menuMusic.play();
		SoundBank::Get().menuMusic.setLoop(true);
		playingMusic = true;
	}	
}

void Menu::StopMusic()
{
	SoundBank::Get().menuMusic.stop();
	playingMusic = false;
}

const bool Menu::GetPermaDeath()
{
	return pdMode;
}

const bool Menu::IsMenuSelected() {
	return MenuSelected;
}

const bool Menu::IsStartSelected() {
	return StartSelected;
}
