#include "Map.h"
#include <SFML/Graphics.hpp> 
#include <iostream>
using namespace sf;
using namespace std;

Map::Map()
{
}

Map::Map(Texture& texture)
{
	mSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	mSprite.setScale(Utils::GetAppScale());
	mSprite.setTexture(texture);
}

void Map::DrawMap(RenderWindow(&window))
{
	window.draw(mSprite);
}

void Map::SetPosition(Vector2f pos)
{
	mSprite.setPosition(pos);
}
