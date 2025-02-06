#include "GameObject.h"
#include <SFML/Graphics.hpp> 
#include <iostream>
#include "Utils.h"


using namespace sf;
using namespace std;

GameObject::GameObject()
{
}

GameObject::GameObject(string imgLoc)
{
	if (!cTexture.loadFromFile(imgLoc)) {
		cout << "Could not load image" << endl;
	}

	cSprite.setTexture(cTexture);	

	cSprite.setScale(Utils::GetAppScale());
}

GameObject::GameObject(string imgLoc, bool centered)
{
	if (!cTexture.loadFromFile(imgLoc)) {
		cout << "Could not load image" << endl;
	}

	if (centered) {
		cSprite.setOrigin(cTexture.getSize().x / 2, cTexture.getSize().y / 2);
		this->centered = centered;
	}

	cSprite.setTexture(cTexture);

	cSprite.setScale(Utils::GetAppScale());
}

GameObject::GameObject(Texture& txtr, bool centered)
{
	if (centered) {
		cSprite.setOrigin(txtr.getSize().x / 2, txtr.getSize().y / 2);
		this->centered = centered;
	}

	cSprite.setTexture(txtr);

	cSprite.setScale(Utils::GetAppScale());
}


GameObject::~GameObject()
{
}

void GameObject::SetTexture(Texture& texture)
{
	cSprite.setScale(5, 5);
	cSprite.setTexture(texture);
}

void GameObject::SetColor(Color color)
{
	cSprite.setColor(color);
}

void GameObject::SetColor(int r, int b, int g)
{
	cSprite.setColor(Color(r, b, g));
}

void GameObject::SetColor(int r, int b, int g, int a)
{
	cSprite.setColor(Color(r, b, g, a));
}

void GameObject::SetRectSize(int size)
{
	rectSourceSprite.width = size;
	rectSourceSprite.height = size;
}

void GameObject::SetRectSize(int width, int height)
{
	rectSourceSprite.width = width;
	rectSourceSprite.height = height;
}

void GameObject::Animate(int frames, int rectSizeX, int rectSizeY, float speed, bool boomerang)
{
	SetRectSize(rectSizeX, rectSizeY);

	rectSourceSprite.top = 0;
	if (clock.getElapsedTime().asSeconds() > speed) {
		if (rectSourceSprite.left == rectSourceSprite.width * frames) {
			rectSourceSprite.left = -rectSourceSprite.width;
		}

		rectSourceSprite.left += rectSourceSprite.width;

		cSprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}

}

void GameObject::ReduceOpacity(float am)
{
	if (opacity <= 0)
		return;

	if ((opacity - am) < 0) {
		opacity = 0;
	}
	else {
		opacity -= am;
	}
	
	Color color = cSprite.getColor();
	color.a = opacity;
	cSprite.setColor(color);
}

void GameObject::ResetOpacity()
{
	opacity = 255;
	Color color = cSprite.getColor();
	color.a = opacity;
	cSprite.setColor(color);
}

float GameObject::GetOpacity()
{
	return opacity;
}

void GameObject::update()
{
	cSprite.setPosition(position);
	
}

void GameObject::render(RenderWindow& window)
{
	if (visible)
	window.draw(this->cSprite);
}

