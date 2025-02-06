#pragma once
#include "Scores.h"
#include "TextureBank.h"
#include "GameObject.h"
#include "WindowEffects.h"
#include "RichText.h"

#define ScoreElements ScoresCount

using namespace sfe;
class ScoreOverlay : public GameObject
{
private:
	
	Font font;
	RichText scoreNames[ScoreElements];
	RichText scoreValues[ScoreElements];
	GameObject ScoresTitle;
	void start();
	bool started = false;

public:

	Text clearScoresText;
	ScoreOverlay();
	void reloadScores();
	void ClearScores();
	void render(RenderWindow& window) override;
	void update() override;
};

