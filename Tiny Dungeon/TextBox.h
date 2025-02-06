#pragma once
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include "WindowEffects.h"

#define TAB_KEY 9
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

using namespace sf;
using namespace std;

class TextBox
{
public:
	TextBox(int size, Color color, bool selectable, bool selected = false);

	TextBox();

	~TextBox();

	void SetFont(Font& font);
	void SetPosition(Vector2f pos, bool centered = true);
	const string GetString();
	void setLimit(bool trueFalse);
	void setLimit(bool trueFalse, int lim);
	void setLimit(int lim);
	void setSelected(bool sel);
	string getText();
	void typedOn(Event input);
	void render(RenderWindow& window);
	void SetCharacterSize(int size);
	void Clear();

private:
	Text textbox;
	ostringstream text;
	string clearText = "enter name";
	bool isSelected = false;
	bool selectable = false;
	bool hasLimit = false;
	int limit = 0;

	void input(int charTyped);

	void deleteLast();

};

