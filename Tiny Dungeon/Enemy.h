#pragma once

#include "Character.h"
#include <SFML/Graphics.hpp> 
#include "Utils.h"

namespace CharacterGroup {

	class Enemy : public Character
	{
	private:


	public:
		Enemy(Enums::EnemyTypes type);
		~Enemy();

		void LoadAttributes();

		Enums::EnemyTypes type = Enums::EnemyTypes::MiniOrc;

		void Transmog(Enums::EnemyTypes newType);

	};

}