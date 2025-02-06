#pragma once

#include "Character.h"
#include <SFML/Graphics.hpp> 
#include "Utils.h"
#include "Enums.h"

namespace CharacterGroup {
	class Ally : public Character
	{
	private:

	public:
		Ally(Enums::AllyTypes type);
		~Ally();

		Enums::AllyTypes type = Enums::AllyTypes::ElfF;

		void LoadAttributes();

		void Transmog(Enums::AllyTypes newType, bool reloadRect = true);

	};

}


