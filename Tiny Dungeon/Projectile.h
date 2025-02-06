#pragma once

#include <SFML/Graphics.hpp> 
#include "GameObject.h"
#include "Enums.h"
#include "Utils.h"
#include "TextureBank.h"
#include "GameObject.h"
#include "SoundBank.h"

using namespace sf;
using namespace std;

namespace CharacterGroup {

	class Projectile : public GameObject
	{
	private:
		float projSpeed = 6;
		GameObject* target;
		GameObject* origin;
		string startSound;
		string hitSound;
		bool hasHitSound = false;
		bool targetSet = false;
		bool isAnimated = true;
		bool rotateTowards = false;
		bool accelerate = false;
		bool positionSet = false;
		float offset = 5;

	public:	

		Enums::ProjectileTypes type;

		Projectile();

		~Projectile();

		void SetType(Enums::PrimaryMove move);

		void AnimationLoop();

		void MoveToObject(GameObject& originGo, GameObject& targetGo, RenderWindow& rw);

		const bool AtTargetPosition();

		void SetTarget(GameObject& originGo, GameObject& targetGo);
		GameObject* GetTarget() const;
		void ClearTarget();

		void update(RenderWindow& window);
		void render(RenderWindow& window) override;

	};

}