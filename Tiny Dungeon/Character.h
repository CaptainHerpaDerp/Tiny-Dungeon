#pragma once
#include "TextureBank.h"
#include "GameObject.h"
#include "Utils.h"
#include "HealthStaminaBar.h"
#include "RearrangeIndicator.h"
#include "Enums.h"
#include "Projectile.h"
#include "Moves.h"
#include "EffectsOverlay.h"
#include "GlobalMoveAnimator.h"
#include "FloatingText.h"
#include "WeaponController.h"
#include "SoundBank.h"

using namespace sf;
using namespace std;

namespace CharacterGroup {

	class Character : public GameObject
	{

	private:
		bool ranged = false;
		int selectedMove = 1;
		int projectileStep = 0;
		void CheckProjHit();
		void Start();
		bool ranStart = false;
		int DeathCycle();
		bool deathCycleActive = false;
		void UnsetTarget();
		void displayFloatText(string text, char type);
		int applyDamageTo(Character* targ, int am);
		int applyDamageTo(Character* targ);
		void applyRandomEffect(char type);
		bool detectTargetDeath = false;
		bool disableEffectMHover = false;
		vector<shared_ptr<FloatingText>> floatingTexts;
		FloatingText floatingText;
		Vector2f weaponPos = Vector2f(0, 0);
		const float baseMoveSpeed = 15.5f;
		float moveSpeed = 15.5f; // 15.5f
		float hitPointsMax = 0;

	protected:
		void setMaxHp(int val);

	public:
		Character();
		/// <summary>
		/// Board Character
		/// </summary>
		/// <param name="imgLoc">Character spitesheet location</param>
		/// <param name="charSize">'s' for small enemies, 'm', for medium size enemies and all ally characters, 'l' for bosses</param>
		/// <param name="Affinity">'a' for allies, 'e' for enemies</param>
		/// <param name="speed">characters attack bar increase per tick</param>
		Character(string imgLoc, char charSize, char Affinity, int speed, float damage);
		virtual ~Character();

		EffectsOverlay effectOverlay;
		RearrangeIndicator ArrangeIndicator;
		HealthStaminaBar hpBar;

		Enums::cState state = Enums::cState::Idle;
		Character* target = nullptr;

		//Enums::PassiveEffects passiveEffect = Enums::PassiveEffects::None;

		//Enums::PrimaryMove primaryMove = Enums::PrimaryMove::KnightPrimary;
		//Enums::SecondaryMove secondaryMove = Enums::SecondaryMove::KnightSecondary;

		//Texture primaryMoveTexture;
		//Texture secondaryMoveTexture;

		PrimaryMove primaryMove;
		SecondaryMove secondaryMove;
		SecondaryMove originalSecondary;

		int attackVariations = 0;
		string attackNameGroup;
		int hitVariations = 0;
		string hitNameGroup;
		Vector2f widthOffset = Vector2f(0, 0);

		vector<GameObject*> GameObjects;
		vector<pair<MoveEffect, int>> ActiveBuffs;

		Vector2f BasePos;

		Projectile projectile;
		WeaponController weaponCtrl;

		int basePosOffset = 0;

		bool targetSet = false, hasBasePos = false, hit = false, active = true, passiveSecondary = false, justKilled = false;

		int hitCounter = 0;

		//Stats
		char Affinity = 'n';
		float StaPointsMax = 100;
		float HitPointsCurrent = 1;
		float StaPointsCurrent = 0;
		float Damage = 1;
		int Speed = 1;
		int IndexPosition = 0;

		float SpeedModifier = 1;
		float ShieldPortion = 1;
		float DamageModifier = 1;

		//Intakes (x * 100) percent of incoming damage ex. intaking 100pts with 0.5 portion, resulting amount is 50pts

		int SecondaryCooldown = 0;

		void ApplyEffect(PrimaryMove move, int healModifier = 0);
		void ApplyEffect(SecondaryMove move, int healModifier = 0);
		void ApplyEffect(MoveEffect effect);
		void ApplyEffect(MoveEffect effect, int duration);
		bool CheckHasStun();
		void ApplyEffectTo(Character* target, PrimaryMove move);
		void ApplyRandomEffectTo(CharacterGroup::Character* target);
		void ApplyEffectTo(Character* target, SecondaryMove move);
		void ApplyEffectTo(Character* target, MoveEffect effect);
		void RemoveAllDebuffs();
		void RemoveBuff();
		void RemoveAllBuffs();
		void AddToActiveEffects(MoveEffect effect);
		void AddToActiveEffects(MoveEffect effect, int duration);

		bool ApplySecondaryEffect(vector<Character*> allies, vector<Character*> targets);
		bool ApplyPrimaryEffect(vector<Character*> allies, vector<Character*> targets, Character* mainTarget = nullptr);

		void ClearBuffs();
		void ApplyActiveBuffs(bool reduceDurations = true);
		void ApplySecondaryCooldown();
		void ApplyPassiveEffect(Character* target);
		void ReloadBuffs();
		void SetState(Enums::cState state);
		void SetMoveSpeed(float val);

		void ResetEffectOverlayPos();

		void HealFor(float val);
		void IncreaseStaminaBar();
		void recieveHit();
		int IntakeDamage(float value, bool ignoreArmour = false);
		float ResultingHitpoints(float hitpoints);\
		float TotalDamage();
		string TotalDamageWeaponIncl();
		void ChangePosition(int newIndex, Vector2f newPosition);
		void GiveWeapon(Weapon weapon);

		const float HitPointsMax();

		virtual void moveTo(Vector2f targetPos, float stopDistance);

		const sf::Vector2f& WidthOffset();

		void SetWidthOffset();

		void ResetRectPosition();

		/// <summary>
		/// Attacking a provided target with a selected move
		/// </summary>
		/// <param name="character"></param>
		/// <param name="move"></param>
		virtual void Attack(Character* character, int move = 0, vector<Character*> allies = vector<Character*>(5), vector<Character*> targets = vector<Character*>(5));

		/// <summary>
		/// Automatically attacking the best target amongst an array of provided targets
		/// </summary>
		/// <param name="targets"></param>
		virtual void AutoMove(vector<Character*> attackableTargets, vector<Character*> allTargets, vector<Character*> allies, GlobalMoveAnimator& globalEffect);

		virtual void hitTarget();
		virtual void IdleAnimation();
		virtual void MoveAnimation();

		void IsRanged(bool condition);

		void ApplyColorEffect();
		void RemoveAllActiveBuffs();
		void Reset();

		void update() override;
		void render(RenderWindow& window) override;

		Weapon EquippedWeapon();
		const WeaponEffects WeaponStats();
		const bool HasWeapon();
		void WpnSecondaryOverride();

		const bool AtBasePosition();
		const bool DeathCycleActive();
		const bool HasHealPrevention();
		const bool IsRanged();
		const bool HasSecondary();
	};
}
