#pragma once
#include "GameObject.h"
#include "TextureBank.h"
#include "Enums.h"
#include "Moves.h"

namespace CharacterGroup {

	class EffectsOverlay : public GameObject
	{
	private:
		bool setTex = false;
		bool isAnimating = false;
		int frames = 0;
		float speedModifier = 1;
	public:
		EffectsOverlay();
		~EffectsOverlay();

		void RunEffect(PrimaryMove move, char targetAff = 'n');
		void RunEffect(SecondaryMove move);
		void RunEffect(Enums::Effects effect);

		void EnableEffect();
		void AnimEffect(int frames);
		void DisableEffect();
		void update() override;

		const bool FinishedAnim();

	};
}
