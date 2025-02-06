#pragma once
#include <SFML/Graphics.hpp> 
#include <iostream>

using namespace sf;
using namespace std;
class GameObject
{
private:
	float opacity = 255;
	float incrAm = 0;
	bool incrOpacity = false;
	bool moving = false;
	Vector2f targPos;

public:
	Texture cTexture;
	Sprite cSprite;
	Clock clock;
	Vector2f position;
	IntRect rectSourceSprite;

	float animationSpeed = 0.125f;

	bool visible = true;
	bool centered = false;

	GameObject();
	GameObject(string imgLoc);
	GameObject(string imgLoc, bool centered);
	GameObject(Texture& txtr, bool centered = true);
	~GameObject();

	void SetTexture(Texture& texture);

	void SetPosition(float posx, float posy) {
		position = Vector2f(posx, posy);
	}

	void SetPosition(Vector2f vector) {
		position = vector;
	}

	void SetColor(Color color);
	void SetColor(int r, int b, int g);
	void SetColor(int r, int b, int g, int a);

	void SetRectSize(int size);
	void SetRectSize(int width, int height);

	void Animate(int frames, int rectSizeX, int rectSizeY, float speed = 0.125f, bool boomerang = false);

	void ReduceOpacity(float am);
	void ResetOpacity();
	float GetOpacity();

	virtual void update();
	virtual void render(RenderWindow& window);

	// READ chapter "lifetime of a class"! (Ch.24?)
	GameObject(const GameObject& go) = delete;
	GameObject& operator = (const GameObject& go) = delete;

};

