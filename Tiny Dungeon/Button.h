#pragma once
#include "GameObject.h"
#include "TextureBank.h"
#include "Enums.h"
#include "WindowEffects.h"
#include "SoundBank.h"

class Button : public GameObject
{
private:
	bool toggled = false;
	Enums::ButtonTypes type;
	bool visualToggle = false;
	bool popup = false;
	bool alternateHover = false;
	bool quickUntoggle = false;
	bool playedSound = false;
	bool enteredHover = false;

	Texture toggledTex;
	Texture untoggledTex;
	Texture hoverTex;

public:
	bool isLocked = false;
	const Enums::ButtonTypes GetType();
	void SetType(Enums::ButtonTypes Type);
	void EnterHover();
	void Activate();
	void ExitHover();
	const bool IsToggled();
	void IsToggled(bool condition);
	void Lock();
	void Unlock();
	Button();
	~Button();

};

