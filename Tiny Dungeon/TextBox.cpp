#include "TextBox.h"
#include "GameObject.h"

TextBox::TextBox(int size, Color color, bool selectable, bool selected)
{
	textbox.setCharacterSize(size);
	isSelected = selected;
	this->selectable = selectable;
	//textbox.setColor(color);
	if (selected && selectable) {
		textbox.setString(clearText);
	}
	else {
		textbox.setString("");
	}
}

TextBox::TextBox()
{
	textbox.setCharacterSize(15);
	isSelected = true;
	selectable = true;
	textbox.setFillColor(Color(253, 247, 237));
	if (isSelected && selectable) {
		textbox.setString(clearText);
	}
	else {
		textbox.setString("");
	}
}

TextBox::~TextBox()
{
}

void TextBox::SetFont(Font& font)
{
	textbox.setFont(font);
}

void TextBox::SetPosition(Vector2f pos, bool centered)
{
	if (centered)
	textbox.setPosition(Vector2f(pos.x - textbox.getLocalBounds().width / 2, pos.y));
	else
		textbox.setPosition(Vector2f(pos.x - textbox.getLocalBounds().width / 2, pos.y));
}

const string TextBox::GetString()
{
	return textbox.getString();
}

inline void TextBox::setLimit(bool trueFalse) {
	hasLimit = trueFalse;
}

inline void TextBox::setLimit(bool trueFalse, int lim) {
	hasLimit = trueFalse;
	limit = lim;
}

void TextBox::setLimit(int lim) {
	hasLimit = true;
	limit = lim;
}

void TextBox::render(RenderWindow& window)
{
	window.draw(this->textbox);
}

void TextBox::SetCharacterSize(int size)
{
	textbox.setCharacterSize(size);
}

void TextBox::Clear()
{	
	textbox.setString("enter name");
	text.str("");
}

void TextBox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel) {
		string t = text.str();
		string newT = "";
		for (size_t i = 0; i < t.length() - 1; i++)
		{
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

inline string TextBox::getText() {
	return text.str();
}

void TextBox::typedOn(Event input)
{
	if (isSelected) {
		int charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (text.str().length() <= limit) {
					this->input(charTyped);
				}
				else if (text.str().length() > limit && charTyped == DELETE_KEY) {
					deleteLast();
				}
			}
			else {
				this->input(charTyped);
			}
		}
	}
}

void TextBox::input(int charTyped)
{
	if (charTyped != TAB_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY && charTyped != DELETE_KEY) {
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY) {
		if (text.str().length() > 0) {
			deleteLast();
		}
	}
	textbox.setString(text.str());
}

void TextBox::deleteLast()
{
	string t = text.str();
	string newT = "";
	for (size_t i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	text.str("");
	text << newT;

	textbox.setString(text.str());
}
