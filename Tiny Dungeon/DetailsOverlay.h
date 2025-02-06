#pragma once

#include <SFML/Graphics.hpp> 
#include "Utils.h"
#include <iostream>
#include "GameObject.h"

using namespace sf;
using namespace std;

class DetailsOverlay {
private:
	GameObject detailsFrame;
	Text InfoName;
	Text InfoText;

public:
	static DetailsOverlay DetailsOverlay_Instance;
	static DetailsOverlay& Get();
	void update();
	void render(RenderWindow& window);
};

