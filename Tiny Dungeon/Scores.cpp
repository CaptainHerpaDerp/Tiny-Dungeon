#include "Scores.h"

Scores& Scores::Get() {
	return scores_Instance;
}

void Scores::AddScore(string name, int score, int difficulty)
{
	ofstream ifs("Config/Scores.cmgt");
	int indexScoreZero = 0;

	bool foundIndex = false;
	int d = 1;
	for (size_t i = 0; i < playerInfo.size(); i++)
	{
		//Replaces existing user's score, if the score is higher
		if (name != "null" && playerInfo[i].name == name && playerInfo[i].difficulty == difficulty) {
			if (score > playerInfo[i].score)
			playerInfo[i].score = score;
			foundIndex = true;
			break;
		}

		//Adds a new entry on one of the empty player slots if the user name doesnt exist
		else if (playerInfo[i].name == "null" || playerInfo[i].name == "" || playerInfo[i].name == "0") {
			if (name == "" || name == "enter name") {
				playerInfo[i].name = "unnamed";
			}
			else if (name == "null") {
				playerInfo[i].name = "notcool";
			}
			else {
				playerInfo[i].name = name;
			}
			playerInfo[i].score = score;
			playerInfo[i].difficulty = difficulty;
			foundIndex = true;
			break;
		}
	}

	if (ifs.is_open())
	{
		for (size_t i = 0; i < ScoresCount; i++)
		{
			cout << playerInfo[i].name << endl;
			ifs << playerInfo[i].name << " " << playerInfo[i].score << " " << playerInfo[i].difficulty << "\n";
		}
	}
}

Scores::Scores()
{
	ifstream ifs("Config/Scores.cmgt");

	if (ifs.fail()) {
		cout << "failed to open windowPrefs";
	}

	string current;
	int current2;
	if (ifs.is_open()) {
		for (size_t i = 0; i < ScoresCount; i++)
		{
			ifs >> playerInfo[i].name;
			ifs >> playerInfo[i].score;
			ifs >> playerInfo[i].difficulty;
		}
	}
}

const vector<PlayerInfo> Scores::GetPlayerInfo()
{
	return playerInfo;
}

void Scores::ClearAll()
{
	ofstream ifs("Config/Scores.cmgt");

	if (ifs.is_open()) {

		for (size_t i = 0; i < ScoresCount; i++)
		{
			playerInfo[i].name = "null";
			playerInfo[i].score = 0;
			ifs << playerInfo[i].name << " " << playerInfo[i].score << "\n";
		}
	}
}

void Scores::ClearSave()
{
	ofstream ifs("Config/Continue.cmgt");

	if (ifs.is_open()) {
		for (size_t i = 0; i < 20; i++)
		{
			ifs << "";
		}
	}
}

Scores Scores::scores_Instance;
