#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <fstream>
#include <limits>

using namespace sf;
using namespace std;

static class Utils {
public: 
	 static Vector2f Normalize(Vector2f);
	 static double Length(Vector2f);
	 static Vector2f SetLength(Vector2f, float l);

	 const static Vector2f GetAppScale();

	 static void FillRandUnique(int array[], int length, int min, int max);

	 /// <summary>
	 /// Returns true if a number lands within the number provided
	 /// </summary>

	 static bool Chance(int maxVal);
	 static bool PercentChance(int val);

	 static int RandRange(int maxVal);
	 static int RandRange(int minVal, int maxVal);

	 const static bool MouseBoundsOf(const GameObject& go, const RenderWindow& win);

	 const static bool MouseBoundsOf(Text& txt, RenderWindow& win);

	 const static float DistanceTo(Vector2f vec1, Vector2f vec2);

	 static string AutoBreak(Text s, int charPerBr);

	 static string AutoBreak(String s, int charPerBr);

	 const Vector2f TextCenter(Text t);

	 const static float CenterOf(GameObject& go, char axis);

	 const static string PosOrNeg(int num);

	 const static Color Cov(int num);

};
