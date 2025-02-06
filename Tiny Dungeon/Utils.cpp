#include "Utils.h"


Vector2f Utils::Normalize(Vector2f v)
{
	float length = Length(v);

	Vector2f newVec;

	if (length != 0)
	{
		newVec.x = v.x / length;
		newVec.y = v.y / length;
	}

	return newVec;
}

double Utils::Length(Vector2f v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2)));
}

Vector2f Utils::SetLength(Vector2f v, float l)
{
	Vector2f norm = Normalize(v);
	norm.x *= l;
	norm.y *= l;

	return norm;
}

const Vector2f Utils::GetAppScale()
{
	return Vector2f(5, 5);
}

void Utils::FillRandUnique(int array[], int length, int min, int max)
{
	srand(time(NULL));

	for (size_t i = 0; i < length; i++)
	{
		array[i] = 0;
	}

	int newRand = 0;
	bool unique = false;

	for (size_t i = 0; i < length; i++)
	{
		do 
		{
			newRand = (rand() % (max - min + 1)) + min;

			unique = true;

			for (auto j= 0; j < length; j++)
			{
				if (array[j] == newRand)
					unique = false;
			}
		}
		while (!unique);

		array[i] = newRand;
	}

	for (size_t i = 0; i < length; i++)
	{
		array[i] --;
	}
}

bool Utils::Chance(int maxVal)
{
	if (maxVal == 0)
		return true;

	int val = rand() % maxVal;

	if (val == 0)
		return true;

	return false;
}

bool Utils::PercentChance(int val)
{
	int roll = rand() % 100;

	cout << roll << " " << val << endl;

	if (roll <= val)
		return true;

	return false;
}

int Utils::RandRange(int maxVal)
{
	return (rand() % maxVal + 1);
}

int Utils::RandRange(int minVal, int maxVal)
{
	return (minVal + (rand() % ((maxVal + 1) - minVal)));
}

//A const within a function constructor indicates that the function will not change the value assigned const (as it cannot be changed)
const bool Utils::MouseBoundsOf(const GameObject& go, const RenderWindow& win) {
	Vector2i mousePos = Mouse::getPosition(win);
	Vector2f worldPos = win.mapPixelToCoords(mousePos);
	//cout << worldPos.x << endl;	cout << worldPos.y << endl;


	float width = go.rectSourceSprite.width;
	float height = go.rectSourceSprite.height;

	if (!go.centered && worldPos.x > go.position.x && worldPos.x < go.position.x + width * 5 &&
		worldPos.y > go.position.y && worldPos.y < go.position.y + height * 5) {		
		return true;
	}
	if (go.centered && worldPos.x > go.position.x - width && worldPos.x < go.position.x + width &&
		worldPos.y > go.position.y - height && worldPos.y < go.position.y + height) {
		return true;
	}
	
	return false;

}

const bool Utils::MouseBoundsOf(Text& txt, RenderWindow& win) {
	Vector2i mousePos = Mouse::getPosition(win);
	Vector2f worldPos = win.mapPixelToCoords(mousePos);

	//cout << mpos.x << endl;	cout << mpos.y << endl;

	float width = txt.getLocalBounds().width;
	float height = txt.getLocalBounds().height;

	if (worldPos.x > txt.getPosition().x && worldPos.x < txt.getPosition().x + width &&
		worldPos.y > txt.getPosition().y + height / 2 && worldPos.y < txt.getPosition().y + height * 2) {
		return true;
	}
	
	return false;
	
}

const float Utils::DistanceTo(Vector2f vec1, Vector2f vec2)
{
	//cout << sqrt(((vec2.x - vec1.x) * 2) + (vec2.y - vec1.y) * 2) << endl;

	float d = pow((vec2.x - vec1.x), 2) + pow((vec2.y - vec1.y), 2);

	return sqrtf(d);
}

string Utils::AutoBreak(Text s, int charPerBr)
{
	string st = (string)s.getString();
	string nSt;
	for (size_t i = 1; i < st.length() - 1; i++)
	{
		nSt += st[i];
		if (i % charPerBr == 0) {
			nSt += "\n";
		}
	}

	return nSt;
}

string Utils::AutoBreak(String s, int charPerBr)
{
	string nSt;
	for (size_t i = 0; i < s.getSize(); i++)
	{
		nSt += s[i];
		if (i > 0 && i % charPerBr == 0) {
			nSt += "\n";
		}
	}

	return nSt;
}

const Vector2f Utils::TextCenter(Text t)
{
	return Vector2f(t.getGlobalBounds().width / 2.f, t.getGlobalBounds().height / 2.f);
}

const float Utils::CenterOf(GameObject& go, char axis)
{
	if (axis == 'x')
	return (float)(go.rectSourceSprite.width * 5) / 2;

	if (axis == 'y')
	return (float)(go.rectSourceSprite.height * 5) / 2;

	return 0;
}

const string Utils::PosOrNeg(int num)
{
	if (num > 0)
		return "+";

	return "";
}

const Color Utils::Cov(int num)
{
	if (num > 0)
		return Color(75, 167, 71);

	if (num < 0)
		return Color(218, 78, 56);

	return Color::Black;
}


