#include "ScoreOverlay.h"



ScoreOverlay::ScoreOverlay()
{
	ScoresTitle.SetTexture(TextureBank::Get().ScoresTitleElement);

	if (!font.loadFromFile("Assets/Fonts/pixelFont.ttf")) {
		cout << "Font not found" << endl;
	}
}

void ScoreOverlay::reloadScores()
{
	int activeScores = 0;

	for (size_t i = 0; i < ScoresCount; i++)
	{
		scoreNames[i].clear();
		scoreValues[i].clear();

		if (Scores::Get().GetPlayerInfo()[i].name == "null" || Scores::Get().GetPlayerInfo()[i].score == 0)
			continue;

		scoreNames[i].setFont(font);
		scoreNames[i].setCharacterSize(40);
		scoreNames[i].setPosition(55, 280 + (activeScores * 50));
		
		if(Scores::Get().GetPlayerInfo()[i].difficulty == 0)
		scoreNames[i] << WindowEffects::Get().BoneWhite;

		if (Scores::Get().GetPlayerInfo()[i].difficulty == 1)
			scoreNames[i] << Color(218, 78, 56);

		scoreNames[i] << Scores::Get().GetPlayerInfo()[i].name;

		scoreValues[i].setFont(font);
		scoreValues[i].setCharacterSize(40);
		scoreValues[i].setPosition(255, 280 + (activeScores * 50));
		scoreValues[i] << WindowEffects::Get().BoneWhite << to_string(Scores::Get().GetPlayerInfo()[i].score);
		activeScores++;
	}

	clearScoresText.setString("Clear");
	clearScoresText.setFont(font);
	clearScoresText.setFillColor(WindowEffects::Get().BoneWhite);
	clearScoresText.setCharacterSize(35);
	clearScoresText.setPosition(120, 275 + (activeScores * 50));
}

void ScoreOverlay::ClearScores()
{
	Scores::Get().ClearAll();
	reloadScores();
}

void ScoreOverlay::render(RenderWindow& window)
{
	if (!this->visible)
		return;

	window.draw(this->cSprite);
	ScoresTitle.render(window);
	ScoresTitle.SetPosition(150, 150);
	window.draw(clearScoresText);
	for (size_t i = 0; i < ScoresCount; i++)
	{
		window.draw(scoreNames[i]);
		window.draw(scoreValues[i]);
	}
}

void ScoreOverlay::start()
{
	reloadScores();
	started = true;
}

void ScoreOverlay::update()
{
	if (!started)
		start();
	ScoresTitle.SetPosition(50, 180);
	ScoresTitle.update();
	cSprite.setPosition(position);
}
