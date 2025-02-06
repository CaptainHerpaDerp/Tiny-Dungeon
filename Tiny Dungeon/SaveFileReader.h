#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Ally.h"
#include "Enemy.h"

using namespace sf;
using namespace std;
using namespace CharacterGroup;

class SaveFileReader {
private:
	SaveFileReader();
	static SaveFileReader SaveFileReader_Instance;

public:
	static SaveFileReader& Get();	
	void ClearSave();
	const bool HasSave();
	void SaveGame(int currentLevel, vector<Ally*> Allies, vector<Enemy*> Enemies, Ally* rewardCharacter, bool toRewardChar, bool toRewardWeapon, int difficulty);
	void LoadGame(int& currentLevel, vector <Ally*>& ally, vector <Enemy*>& enemy, Enums::AllyTypes& rewardCharType, bool& difficulty);
	string GetSaveDate();
	string GetSaveLevel();
	int GetSaveDifficulty();
};

