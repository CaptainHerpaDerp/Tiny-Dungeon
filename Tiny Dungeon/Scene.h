#pragma once
#include <SFML/Graphics.hpp> 
#include <iostream>
#include "Map.h"
#include <unordered_map>
#include <list>

using namespace sf;

struct CharPositionData
{
	Vector2f charPos;
	Vector2f hpBarPos;
	Vector2f castPos;
};

class Scene
{
public:

	unordered_map<int, CharPositionData> charPositions;
	Map map;

	Scene();
	~Scene();

	void setMap(Map map);

	virtual void render(RenderWindow& window);
	virtual void update(RenderWindow& window);

};

