#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;
constexpr auto ScoresCount = 6;

struct PlayerInfo {
	string name;
	int score;
	int difficulty;
};

class Scores {
public:
	static Scores& Get();
	void AddScore(string name, int score, int difficulty);
	const vector<PlayerInfo> GetPlayerInfo();
	void ClearAll();
	void ClearSave();
private:
	Scores();
	int currentScores = 0;
	static Scores scores_Instance;
	vector<PlayerInfo> playerInfo{ ScoresCount };
};

