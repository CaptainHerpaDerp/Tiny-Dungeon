#include "Button.h"

Button::Button()
{
	type = Enums::ButtonTypes::Clear;
	SetRectSize(14);
}

Button::~Button()
{
}

const Enums::ButtonTypes Button::GetType()
{
	return type;
}

void Button::SetType(Enums::ButtonTypes Type)
{
	type = Type;
	switch (type) {
	case Enums::ButtonTypes::AutoPlay:
		untoggledTex = TextureBank::Get().AutoPlayButton;
		toggledTex = TextureBank::Get().AutoPlayPauseButton;
		visualToggle = true;
		break;

	case Enums::ButtonTypes::Audio:
		untoggledTex = TextureBank::Get().AudioButton;
		toggledTex = TextureBank::Get().MuteButton;
		visualToggle = true;
		break;

	case Enums::ButtonTypes::Menu:
		untoggledTex = TextureBank::Get().MenuButton;
		popup = true;
		visualToggle = false;
		break;

	case Enums::ButtonTypes::Play:
		untoggledTex = TextureBank::Get().PlayButton;
		hoverTex = TextureBank::Get().PlayButtonSelected;
		alternateHover = true;
		SetRectSize(43, 20);
		visualToggle = false;
		break;

	case Enums::ButtonTypes::Return:
		untoggledTex = TextureBank::Get().ReturnButton;
		hoverTex = TextureBank::Get().ReturnButtonSelected;
		alternateHover = true;
		SetRectSize(49, 20);
		visualToggle = false;
		break;

	case Enums::ButtonTypes::MainMenu:
		untoggledTex = TextureBank::Get().HelpButton;
		hoverTex = TextureBank::Get().HelpButtonSelected;
		SetRectSize(43, 20);
		alternateHover = true;
		visualToggle = false;
		break;

	case Enums::ButtonTypes::Options:
		untoggledTex = TextureBank::Get().RestartButton;
		hoverTex = TextureBank::Get().RestartButtonSelected;
		SetRectSize(48, 20);
		alternateHover = true;
		visualToggle = false;
		break;

	case Enums::ButtonTypes::Exit:
		untoggledTex = TextureBank::Get().ExitButton;
		hoverTex = TextureBank::Get().ExitButtonSelected;
		SetRectSize(43, 20);
		alternateHover = true;
		visualToggle = false;
		break;

	case Enums::ButtonTypes::NextLevel:
		untoggledTex = TextureBank::Get().ContinueButton;
		hoverTex = TextureBank::Get().ContinueButtonSelected;
		SetRectSize(65, 22);
		alternateHover = true;
		visualToggle = false;
		break;
	}

	SetTexture(untoggledTex);
}

void Button::EnterHover()
{
	if (enteredHover)
		return;

	if (!visible)
		return;

	enteredHover = true;
	if (!playedSound) {
		playedSound = true;
		SoundBank::Get().Play("selectSound");
	}
	if (!alternateHover)
	SetColor(175, 175, 175);
	else {
		SetTexture(hoverTex);
	}
}

void Button::Activate()
{		
	if (isLocked) {
		return;
	}

	if (popup) {
		toggled = !toggled;
		return;
	}
	
	toggled = !toggled;

	if (!visualToggle)
		return;

	if (IsToggled())
	SetTexture(toggledTex);
	if (!IsToggled())
	SetTexture(untoggledTex);
	
}

void Button::ExitHover()
{
	enteredHover = false;
	playedSound = false;
	if (!alternateHover)
		SetColor(WindowEffects::Get().BoneWhite);
	else {
		SetTexture(untoggledTex);
	}
}

const bool Button::IsToggled()
{
	return toggled;
}

void Button::IsToggled(bool condition)
{
	toggled = condition;
}

void Button::Lock()
{
	if (!isLocked)
	SetTexture(untoggledTex);
	isLocked = true;
}

void Button::Unlock()
{
	SetTexture(untoggledTex);
	toggled = false;
	isLocked = false;
}


