#pragma once
#include <SFML/Graphics.hpp> 
#include <sstream>
#include <iostream>
#include "WindowEffects.h"
#include "RichText.h"

using namespace sfe;

class FloatingText
{
	private:
		Font font;
		RichText text;

		Vector2f position;
		bool active = false;
		bool visible = false;

		float opacity = 255;
		float yMoveDistance = 0.1f;

		int moveAm;
		int floatTime;
		const int floatTimeMax = 40;

		char movementType = 'm';

		Vector2f targetPos;
		void moveText();
		void reduceOpacity(float am);
		void resetOpacity();
		void reset();
		void textSize(int am);


	public:
		FloatingText();
		const bool IsActive();
		void Activate(String text, Vector2f position, char type);
		void update();
		void render(RenderWindow& window);


};

