#include "FloatingText.h"

FloatingText::FloatingText(){ 

	if (!font.loadFromFile("Assets/Fonts/typePixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	text.setCharacterSize(25);
	text.setFont(font);
}
void FloatingText::moveText()
{
	//textSize(35);
	//position.y -= 1;
	//reduceOpacity(4);

	Vector2f targetDiff(0, 0);

	targetDiff = position - targetPos;

	float difference = Utils::Length(targetDiff);

	if (floatTime < 70) {
		floatTime++;
		if (movementType == 'd') {
			targetPos += Vector2f(0, moveAm);
		}
		position -= (Utils::SetLength(targetDiff,  difference / 15)); //5.5f
	}
	else {
		reset();
	}

}

const bool FloatingText::IsActive()
{
    return active;
}

void FloatingText::Activate(String textString, Vector2f newPos, char type)
{
    if (active) return;
	active = true;
	int offset = 0;
	int travelDistance = 0;
	movementType = type;

	if (type == 'd') {
		offset = Utils::RandRange(-80, 80);
		moveAm = Utils::RandRange(2, 4);
		Color colour = WindowEffects::Get().DifficultRed;
		colour.a = 200;
		text << colour << "-";
		travelDistance = 75;
	}

	if (type == 'h') {
		Color colour = WindowEffects::Get().EasyGreen;
		colour.a = 200;
		text << colour;
		travelDistance = 40;
	}

	text << textString;
	position = newPos + Vector2f(text.getLocalBounds().width, text.getLocalBounds().height / 2);
	targetPos = newPos + Vector2f((text.getLocalBounds().width) + offset, -travelDistance);
}

void FloatingText::update() {
	//cout << position.x << " : " << position.y << endl;
    text.setPosition(position);
	if (active) {
		visible = true;
		moveText();
		if (opacity <= 0) {
			reset();
		}
	}
}

void FloatingText::render(RenderWindow& window)
{
	if (visible)
    window.draw(text);
}

void FloatingText::reset()
{
	floatTime = 0;
	text.clear();
	visible = false;
    active = false;
	resetOpacity();
}

void FloatingText::textSize(int am)
{
	text.setCharacterSize(am);
}


void FloatingText::reduceOpacity(float am)
{
	if (opacity <= 0)
		return;

	if ((opacity - am) < 0) {
		opacity = 0;
	}
	else {
		opacity -= am;
	}

	//Color color(text.getCharacterColor(1, 1))
	//color.a = opacity;
	//text.setFillColor(color);
}

void FloatingText::resetOpacity()
{
	opacity = 255;
	//Color color = text.getFillColor();
	//color.a = opacity;
	//text.setFillColor(color);
}
