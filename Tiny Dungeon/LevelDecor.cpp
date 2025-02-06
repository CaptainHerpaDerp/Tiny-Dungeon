#include "LevelDecor.h"

LevelDecor::LevelDecor()
{
}

void LevelDecor::Randomize()
{
	elements.clear();
	int floorElements = Utils::RandRange(3, 8);

	for (size_t i = 0; i < floorElements; i++)
	{
		shared_ptr<GameObject> floorElement(new GameObject());
		int texture = Utils::RandRange(7) - 1;
		floorElement->SetPosition(((76 + (Utils::RandRange(8) - 1) * 16) * 5), ((38 + (Utils::RandRange(10) - 1) * 16) * 5) + 1);

		int randRotation = Utils::RandRange(2) - 1;

		switch (texture) {
		case 0:
			floorElement->SetTexture(TextureBank::Get().FloorStain1);
			break;

		case 1:
			floorElement->SetTexture(TextureBank::Get().FloorStain2);
			break;

		case 2:
			floorElement->SetTexture(TextureBank::Get().FloorStain3);
			break;

		case 3:
			floorElement->SetTexture(TextureBank::Get().FloorStain4);
			break;

		case 4:
			floorElement->SetTexture(TextureBank::Get().FloorStain5);
			break;

		case 5:
			floorElement->SetTexture(TextureBank::Get().FloorStain6);
			break;

		case 6:
			floorElement->SetTexture(TextureBank::Get().FloorStain7);
			break;
		}
		elements.push_back(floorElement);

	}

	int centerPillars = (bossFountain) ? 1 : Utils::RandRange(2) - 1;

	if (centerPillars)
		for (size_t i = 0; i < 4; i++)
		{
			shared_ptr<GameObject> pillar(new GameObject());
			switch (i) {
			case 0:
				pillar->SetPosition(76 * 5, (38 * 5) + 1);
				break;
			case 1:
				pillar->SetPosition(188 * 5, (38 * 5) + 1);
				break;
			case 2:
				pillar->SetPosition(76 * 5, (134 * 5) + 1);
				break;
			case 3:
				pillar->SetPosition(188 * 5, (134 * 5) + 1);
				break;
			}
			pillar->SetTexture(TextureBank::Get().CenterRoomPillar);
			elements.push_back(pillar);
		}

	if (!centerPillars)
		for (size_t i = 0; i < 2; i++)
		{
			shared_ptr<GameObject> backPillar(new GameObject());
			switch (i) {
			case 0:
				backPillar->SetPosition(76 * 5, (6 * 5) + 1);
				break;
			case 1:
				backPillar->SetPosition(188 * 5, (6 * 5) + 1);
				break;
			}
			backPillar->SetTexture(TextureBank::Get().BackWallPillar);
			elements.push_back(backPillar);
		}

	int element = (bossFountain) ? 3 : Utils::RandRange(2) - 1;

	if (element == 0) {
		shared_ptr<GameObject> wallSlime(new GameObject());
		int rand = Utils::RandRange(2) - 1;
		switch (rand) {
		case 0:
			wallSlime->SetPosition((92 * 5), (22 * 5) + 1);
			break;

		case 1:
			wallSlime->SetPosition((172 * 5), (22 * 5) + 1);
			break;
		}
		wallSlime->SetTexture(TextureBank::Get().WallSlime);
		elements.push_back(wallSlime);
	}

	if (element == 1) {
		shared_ptr<GameObject> wallFlag1(new GameObject());
		shared_ptr<GameObject> wallFlag2(new GameObject());

		wallFlag1->SetPosition((92 * 5), (22 * 5) + 1);
		wallFlag2->SetPosition((172 * 5), (22 * 5) + 1);

		int rand = Utils::RandRange(4) - 1;
		switch (rand) {

		case 0:
			wallFlag1->SetTexture(TextureBank::Get().RedFlag);
			wallFlag2->SetTexture(TextureBank::Get().RedFlag);
			break;

		case 1:
			wallFlag1->SetTexture(TextureBank::Get().BlueFlag);
			wallFlag2->SetTexture(TextureBank::Get().BlueFlag);
			break;

		case 2:
			wallFlag1->SetTexture(TextureBank::Get().GreenFlag);
			wallFlag2->SetTexture(TextureBank::Get().GreenFlag);
			break;

		case 3:
			wallFlag1->SetTexture(TextureBank::Get().YellowFlag);
			wallFlag2->SetTexture(TextureBank::Get().YellowFlag);
			break;
		}
		elements.push_back(wallFlag1);
		elements.push_back(wallFlag2);

	}

	if (element == 3) {
		shared_ptr<GameObject> fountain1(new GameObject());
		shared_ptr<GameObject> fountain2(new GameObject());

		fountain1->SetRectSize(16, 50);
		fountain2->SetRectSize(16, 50);

		int randTex = Utils::RandRange(2) - 1;

		if (randTex == 0) {
			fountain1->SetTexture(TextureBank::Get().AnimWallFountainBlue);
			fountain2->SetTexture(TextureBank::Get().AnimWallFountainBlue);
		}
		
		if (randTex == 1) {
			fountain1->SetTexture(TextureBank::Get().AnimWallFountainRed);
			fountain2->SetTexture(TextureBank::Get().AnimWallFountainRed);
		}

		fountain1->SetPosition((92 * 5), (13 * 5) + 1);
		fountain2->SetPosition((172 * 5), (13 * 5) + 1);

		fountain1->rectSourceSprite.left - fountain1->rectSourceSprite.width;
		fountain1->cSprite.setTextureRect(fountain1->rectSourceSprite);

		fountain2->rectSourceSprite.left - fountain1->rectSourceSprite.width;
		fountain2->cSprite.setTextureRect(fountain1->rectSourceSprite);

		elements.push_back(fountain1);
		elements.push_back(fountain2);

		animElements.push_back(fountain1);
		animElements.push_back(fountain2);

	}

	bossFountain = false;
}

void LevelDecor::SetBossFountain(bool condition)
{
	bossFountain = condition;
}

void LevelDecor::render(RenderWindow& win)
{
	for (size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->render(win);
	}
}

void LevelDecor::update()
{
	for (auto&& element : animElements)
	{
		element->Animate(2, 16, 50);

	}

	if (elements.size() > 0)
		for (auto&& element : elements)
		{
			element->update();
		}


}
