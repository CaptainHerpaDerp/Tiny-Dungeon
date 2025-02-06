#pragma once
#include "TextureBank.h"
#include <SFML/Graphics.hpp> 
#include <iostream>
#include "Utils.h"

using namespace sf;
using namespace std;

class Map
{
private:	
	Clock clock;

public:
	Texture mTexture;

	Sprite mSprite;

	Map();

	Map(Texture& texture);

	void DrawMap(RenderWindow(&window));

	void SetPosition(Vector2f pos);
};

