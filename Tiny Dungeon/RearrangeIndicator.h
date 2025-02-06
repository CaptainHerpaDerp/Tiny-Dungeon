#pragma once

#include <SFML/Graphics.hpp> 
#include <iostream>
#include "GameObject.h"
#include "TextureBank.h"
#include "Enums.h"
#include "WindowEffects.h"

using namespace sf;
using namespace std;

namespace CharacterGroup {

	class RearrangeIndicator : public GameObject
	{

	private:

	public:
		RearrangeIndicator();

		~RearrangeIndicator();

		void update() override;

		void ToggleSelected(bool condition);

		//temp
		bool moved = false;
		bool added = false;

	};
}

