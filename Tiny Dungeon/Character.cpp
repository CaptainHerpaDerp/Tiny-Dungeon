#include "Character.h"

using namespace sf;
using namespace std;
using namespace CharacterGroup;


void CharacterGroup::Character::setMaxHp(int val)
{
	hitPointsMax = val;
}

Character::Character()
{

}

Character::Character(string imgLoc, char charSize, char Affinity, int speed, float damage) : GameObject(imgLoc)
{
	switch (charSize) {
	case 's':
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 16;
		break;

	case 'm':
		rectSourceSprite.width = 16;
		rectSourceSprite.height = 28;
		break;

	case 'l':
		rectSourceSprite.width = 32;
		rectSourceSprite.height = 32;
		break;
	}

	this->Speed = speed;

	this->Damage = damage;

	this->Affinity = Affinity;

	cSprite.setTextureRect(rectSourceSprite);

}

//Runs on the very fist frame
void CharacterGroup::Character::Start()
{
	cSprite.setPosition(position);

	ResetEffectOverlayPos();

	weaponCtrl.SetAnimSpeed(animationSpeed);

	ranStart = true;
}

void CharacterGroup::Character::ResetEffectOverlayPos()
{
	if (rectSourceSprite.height == 16) {	
		effectOverlay.SetPosition(Vector2f(BasePos.x - 40, hpBar.position.y - 125));
		weaponPos = Vector2f(45, -95);
	}

	else if (rectSourceSprite.height == 32 && rectSourceSprite.width == 16) {
		effectOverlay.SetPosition(Vector2f(BasePos.x - 40, hpBar.position.y - ((rectSourceSprite.height * 5) - (25))));
		weaponPos = Vector2f(45, -15);
	}

	else if (rectSourceSprite.height == 32 && rectSourceSprite.width == 32) {
		effectOverlay.SetPosition(Vector2f(BasePos.x - 40, hpBar.position.y - ((rectSourceSprite.height * 5) - (25))));
		weaponPos = Vector2f(60, -15);
	}
}

int CharacterGroup::Character::DeathCycle()
{
	ReduceOpacity(5);
	hpBar.visible = false;
	if (GetOpacity() <= 0) {
		deathCycleActive = false;
		active = false;
		return 0;
	}
	return 1;
}

void CharacterGroup::Character::UnsetTarget()
{
	//Ending a turn when a particular target was never set (beneficial effect cast, global effect)
	targetSet = false;
}

void CharacterGroup::Character::displayFloatText(string text, char type)
{
	shared_ptr<FloatingText> newFloating(new FloatingText());
	floatingTexts.push_back(newFloating);
	newFloating->Activate(text, BasePos, type);
}

int CharacterGroup::Character::applyDamageTo(Character* targ, int am)
{
	float val = am + (WeaponStats().Attack) * DamageModifier;
	targ->IntakeDamage(val);
	return val;
}

int CharacterGroup::Character::applyDamageTo(Character* targ)
{
	float val = TotalDamage();
	targ->IntakeDamage(val);
	return val;
}

float CharacterGroup::Character::TotalDamage()
{
	return (Damage + (WeaponStats().Attack)) * DamageModifier;
}

string CharacterGroup::Character::TotalDamageWeaponIncl()
{
	float damModDisplay = ((DamageModifier * 100) - 100);
	string weaponSt = "";
	string damModSt = "";
	string damSt = "";
	int filled = 0;

	if (WeaponStats().Attack == 0 && DamageModifier == 1)
		return to_string((int)Damage) + " Damage";

	if (WeaponStats().Attack < 0) {
		filled++;
		weaponSt = "(" + to_string(WeaponStats().Attack) + ")";
	}

	if (WeaponStats().Attack > 0) {
		filled++;
		weaponSt = "(+" + to_string(WeaponStats().Attack) + ")";
	}

	if (DamageModifier < 1) {
		filled++;
		damModSt = "(" + to_string((int)damModDisplay) + "%)";
	}

	if (DamageModifier > 1) {
		filled++;
		damModSt = "(+" + to_string((int)damModDisplay) + "%)";
	}

	if (filled == 1)
		damSt = " Damage";

	if (filled == 2)
		damSt = " Dam";

	return to_string((int)TotalDamage()) + weaponSt + damModSt + damSt;
}

void CharacterGroup::Character::applyRandomEffect(char type)
{
	if (type == 'b') {
		int rand = Utils::RandRange(4);

		switch (rand) {
		case 1:
			ApplyEffect(MoveEffects::Get().AddShield);
			break;

		case 2:
			ApplyEffect(MoveEffects::Get().AddSpeed);
			break;

		case 3:
			ApplyEffect(MoveEffects::Get().AddAttack);
			break;

		case 4:
			ApplyEffect(MoveEffects::Get().NextTurnHeal);
			break;
		}
	}

	if (type == 'h') {
		int rand = Utils::RandRange(6);

		switch (rand) {
		case 1:
			ApplyEffect(MoveEffects::Get().BreakShield);
			break;

		case 2:
			ApplyEffect(MoveEffects::Get().Stun);
			break;

		case 3:
			ApplyEffect(MoveEffects::Get().Poison);
			break;

		case 4:
			ApplyEffect(MoveEffects::Get().BreakSpeed);
			break;

		case 5:
			ApplyEffect(MoveEffects::Get().BlockHeal);
			break;

		case 6:
			ApplyEffect(MoveEffects::Get().BreakAttack);
			break;
		}
	}
}

void Character::update()
{
	if (!ranStart)
		Start();

	cSprite.setPosition(position - WidthOffset());


	if (detectTargetDeath) {
		if (target->GetOpacity() <= 0) {
			targetSet = false;
			detectTargetDeath = false;
		}
	}

	switch (state) {
	case Enums::cState::Idle:
		IdleAnimation();
		break;

	case Enums::cState::Move:
		MoveAnimation();
		break;
	}

	if (targetSet) {
		if (target == nullptr)
			return;

		if (!IsRanged())
			moveTo(target->position, 50);
	}

	if (!targetSet && !AtBasePosition()) {
		moveTo(BasePos, 10);
	}

	if (AtBasePosition() && state != Enums::cState::Idle) {
		SetState(Enums::cState::Idle);
		hpBar.visible = true;
	}

	if (StaPointsCurrent > StaPointsMax) {
		StaPointsCurrent = StaPointsMax;
	}

	if (StaPointsCurrent < 0) {
		StaPointsCurrent = 0;
	}

	if (HitPointsCurrent > HitPointsMax()) {
		HitPointsCurrent = HitPointsMax();
	}

	if (!AtBasePosition()) {
		hpBar.visible = false;
	}

	if (deathCycleActive)
		DeathCycle();

	if (active == false) {
		visible = false;
	}

	if (active == true) {
		visible = true;
	}

	if (HitPointsCurrent <= 0) {
		ClearBuffs();
		deathCycleActive = true;
	}

	if (hit) {
		recieveHit();
	}


	weaponCtrl.update(position + weaponPos);

	effectOverlay.update();
	hpBar.update(HitPointsCurrent, HitPointsMax(), StaPointsCurrent);
	ArrangeIndicator.SetPosition(BasePos + Vector2f(0, 111));
	ArrangeIndicator.update();
	for (size_t i = 0; i < floatingTexts.size(); i++)
	{
		floatingTexts[i]->update();
	}

	CheckProjHit();

	for (size_t i = 0; i < unsigned(ActiveBuffs.size()); i++)
	{
		if (ActiveBuffs[i].first.action == Enums::Effects::Stun && ActiveBuffs[i].second > 0) {
			cSprite.setColor(Color(125, 125, 125));
		}
	}
}

void Character::render(RenderWindow& window)
{
	ArrangeIndicator.render(window);

	if (visible) {
		weaponCtrl.render(window);
		hpBar.render(window);
		window.draw(this->cSprite);
		effectOverlay.render(window);
		projectile.render(window);
		if (!disableEffectMHover)
			hpBar.DetectMouse(ActiveBuffs, window);

		for (size_t i = 0; i < floatingTexts.size(); i++)
		{
			floatingTexts[i]->render(window);
		}

		projectile.update(window);
	}
}

Weapon CharacterGroup::Character::EquippedWeapon()
{
	return weaponCtrl.equippedWeapon;
}

const WeaponEffects CharacterGroup::Character::WeaponStats()
{
	return weaponCtrl.equippedWeapon.weaponEffects;
}

const bool CharacterGroup::Character::HasWeapon()
{
	if (EquippedWeapon().type != Enums::WeaponTypes::None)
		return true;

	return false;
}

void CharacterGroup::Character::WpnSecondaryOverride()
{

	switch (EquippedWeapon().weaponEffects.SpecialEffect) {
	case Enums::SpecWpnEfct::SecondaryMassHeal:
		secondaryMove = Moves::Get().massHealSecondary;
		break;
	}

	if (secondaryMove.type == Enums::SecondaryMove::ForestStaffSecondary &&
		EquippedWeapon().weaponEffects.SpecialEffect != Enums::SpecWpnEfct::SecondaryMassHeal) {
		secondaryMove = originalSecondary;
	}

}

Character::~Character()
{
}

const bool CharacterGroup::Character::IsRanged() {
	return ranged;
}

void CharacterGroup::Character::IsRanged(bool condition)
{
	ranged = condition;
}

const bool CharacterGroup::Character::HasHealPrevention()
{
	bool blockHeal = false;

	for (size_t i = 0; i < unsigned(ActiveBuffs.size()); i++)
	{
		if (ActiveBuffs[i].first.action == Enums::Effects::BlockHeal && ActiveBuffs[i].second > 0) {
			blockHeal = true;
		}
	}

	return blockHeal;
}

const bool CharacterGroup::Character::HasSecondary()
{
	if (secondaryMove.passiveEffect != Enums::PassiveEffects::None)
		return false;

	if (secondaryMove.type != Enums::SecondaryMove::None && SecondaryCooldown == 0) {
		return true;
	}
	return false;
}

void CharacterGroup::Character::ApplySecondaryCooldown()
{
	SecondaryCooldown = secondaryMove.cooldown;
}


//Based on the move provided, a PRIMARY MOVE effect is applied to this character
void Character::ApplyEffect(PrimaryMove move, int healModifier)
{
	SoundBank::Get().Play(move.effect.sound);

	if (ActiveBuffs.size() >= MaxEffects) {
		return;
	}

	if (HitPointsCurrent <= 0)
		return;

	if (move.effect.action == Enums::Effects::None)
		return;


	if (move.effect.action == Enums::Effects::Stun) {
		if (CheckHasStun())
					return;

		if (Affinity == 'e' && HitPointsMax() >= 200)
			if (Utils::RandRange(4) != 2)
				return;
	}
		


	if (move.effect.action == Enums::Effects::ReduceStamina) {
		hpBar.FlashStamBar();
		float val = (100 - ReduceStaminaAmount) * 0.01;
		StaPointsCurrent *= val;
		return;
	}

	if (move.effect.action == Enums::Effects::RemoveBeneficial) {
		RemoveBuff();
		return;
	}

	effectOverlay.RunEffect(move.effect.action);
	ActiveBuffs.push_back(make_pair(move.effect, move.effect.duration));
	ApplyActiveBuffs(false);
}

//Based on the move provided, a SECONDARY MOVE effect is applied to this character
void Character::ApplyEffect(SecondaryMove move, int healModifier)
{

	SoundBank::Get().Play(move.effect.sound);

	if (ActiveBuffs.size() >= MaxEffects) {
		return;
	}

	if (HitPointsCurrent <= 0)
		return;

	if (move.effect.action == Enums::Effects::None)
		return;

	if (move.effect.action == Enums::Effects::Stun)
		if (CheckHasStun())
			return;


	if (move.type == Enums::SecondaryMove::MaskedOrcSecondary || move.type == Enums::SecondaryMove::OrcSecondary) {
		StaPointsCurrent = StaPointsMax;
	}

	if (move.effect.action == Enums::Effects::NextTurnHeal) {
		effectOverlay.RunEffect(Enums::Effects::NextTurnHeal);
		if (healModifier == 0) {
			HealFor(30);
		}
		else {
			float am = ((healModifier * 0.01f) + 1) * 30;
			int rounded = round(am);
			HealFor(rounded);
		}

	}

	effectOverlay.RunEffect(move.effect.action);
	ActiveBuffs.push_back(make_pair(move.effect, move.effect.duration));
	ApplyActiveBuffs(false);
}

void CharacterGroup::Character::ApplyEffect(MoveEffect effect, int duration)
{
	SoundBank::Get().Play(effect.sound);

	if (ActiveBuffs.size() >= MaxEffects) {
		return;
	}

	if (effect.action == Enums::Effects::Stun)
		if (CheckHasStun())
			return;

	effectOverlay.RunEffect(effect.action);
	AddToActiveEffects(effect, duration);
	ApplyActiveBuffs(false);
}

void CharacterGroup::Character::ApplyEffect(MoveEffect effect)
{
	SoundBank::Get().Play(effect.sound);

	if (ActiveBuffs.size() >= MaxEffects) {
		return;
	}

	if (effect.action == Enums::Effects::Stun)
		if (CheckHasStun())
			return;

	effectOverlay.RunEffect(effect.action);
	AddToActiveEffects(effect);
	ApplyActiveBuffs(false);
}

bool CharacterGroup::Character::CheckHasStun()
{
	for (auto i = 0; i < ActiveBuffs.size(); i++)
	{
		if (ActiveBuffs[i].first.action == Enums::Effects::Stun)
			return true;

		return false;
	}
}

void CharacterGroup::Character::ApplyEffectTo(Character* target, PrimaryMove move)
{
	if (Utils::Chance(move.effectChance))
		target->ApplyEffect(move);

	ApplyRandomEffectTo(target);
}

void CharacterGroup::Character::ApplyEffectTo(Character* target, SecondaryMove move)
{
	
	SoundBank::Get().Play(move.soundName);

	if (WeaponStats().SpecialEffect == Enums::SpecWpnEfct::BonusHeal) {
		target->ApplyEffect(move, WeaponStats().SpecialEffectVal);
	}
	else {
		target->ApplyEffect(move);
	}
	ApplyRandomEffectTo(target);
}

void CharacterGroup::Character::ApplyEffectTo(Character* target, MoveEffect effect)
{
	target->ApplyEffect(effect);
	ApplyRandomEffectTo(target);
}

void CharacterGroup::Character::RemoveAllDebuffs()
{
	disableEffectMHover = true;
	for (size_t i = 0; i < ActiveBuffs.size(); i++)
	{
		if (ActiveBuffs[i].first.type == 'h') {
			ActiveBuffs[i].second = 0;
		}
	}
	hpBar.reloadEffects(ActiveBuffs);
	disableEffectMHover = false;
}

void CharacterGroup::Character::RemoveBuff()
{
	//Checks to see if there are any beneficial buffs on this character
	int activeBeneficials = 0;
	for (size_t i = 0; i < ActiveBuffs.size(); i++)
	{
		if (ActiveBuffs[i].first.type == 'b')
			activeBeneficials++;
	}
	if (activeBeneficials == 0)
		return;

	//choses a random beneficial and removes it
	disableEffectMHover = true;
	bool found = false;
	do {
		int rand = Utils::RandRange(ActiveBuffs.size());
		if (ActiveBuffs[rand - 1].first.type == 'b') {
			ActiveBuffs[rand - 1].second = 0;
			found = true;
		}
	} while (found == false);

	hpBar.reloadEffects(ActiveBuffs);
	disableEffectMHover = false;
}

void CharacterGroup::Character::RemoveAllBuffs()
{
	disableEffectMHover = true;
	for (size_t i = 0; i < ActiveBuffs.size(); i++)
	{
		if (ActiveBuffs[i].first.type == 'b') {
			ActiveBuffs[i].second = 0;
		}
	}
	hpBar.reloadEffects(ActiveBuffs);
	disableEffectMHover = false;
}

void CharacterGroup::Character::AddToActiveEffects(MoveEffect effect)
{
	ActiveBuffs.push_back(make_pair(effect, effect.duration));
}

void CharacterGroup::Character::AddToActiveEffects(MoveEffect effect, int duration)
{
	ActiveBuffs.push_back(make_pair(effect, duration));
}

void CharacterGroup::Character::ApplyRandomEffectTo(CharacterGroup::Character* target)
{
	if (target == this) {
		return;
	}

	//casting a bonus effect to an ally if possible
	if (EquippedWeapon().weaponEffects.SpecialEffect == Enums::SpecWpnEfct::ApplyRandomBuff && target->Affinity == this->Affinity
		&& Utils::PercentChance(WeaponStats().SpecialEffectVal)) {
		target->applyRandomEffect('b');
	}

	//casting a bonus effect to an enemy if possible
	if (EquippedWeapon().weaponEffects.SpecialEffect == Enums::SpecWpnEfct::ApplyRandomDebuff && target->Affinity != this->Affinity
		&& Utils::PercentChance(WeaponStats().SpecialEffectVal)) {
		target->applyRandomEffect('h');
	}
}

bool CharacterGroup::Character::ApplySecondaryEffect(vector<Character*> allies, vector<Character*> enemies)
{
	int delay = 50;
	int counter = 0;

	//Checks if the character can cast their secondary move, and if the move is in the list
	if (HasSecondary()) {


		if (secondaryMove.type == Enums::SecondaryMove::OrcBossSecondary) {

			vector<MoveEffect> stolenEffects;

			for (size_t i = 0; i < allies.size(); i++)
			{
				if (allies[i] == this)
					continue;

				for (size_t j = 0; j < allies[i]->ActiveBuffs.size(); j++)
				{
					if (allies[i]->ActiveBuffs[j].first.type == 'b')
						stolenEffects.push_back(allies[i]->ActiveBuffs[j].first);
				}
			}

			for (size_t i = 0; i < enemies.size(); i++)
			{

				for (size_t j = 0; j < enemies[i]->ActiveBuffs.size(); j++)
				{
					if (enemies[i]->ActiveBuffs[j].first.type == 'b')
						stolenEffects.push_back(enemies[i]->ActiveBuffs[j].first);
				}
			}

			if (stolenEffects.size() == 0)
				return false;

			for (size_t i = 0; i < stolenEffects.size(); i++)
			{
				ApplyEffect(stolenEffects[i]);
			}

			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i]->RemoveAllActiveBuffs();
			}

			hpBar.reloadEffects(ActiveBuffs);
			ApplySecondaryCooldown();
			return true;
		}

		else if (secondaryMove.type == Enums::SecondaryMove::ForestStaffSecondary) {
			int count = 0;

			if (Affinity == 'e') {
				for (size_t i = 0; i < allies.size(); i++)
				{
					if (allies[i]->HitPointsCurrent > allies[i]->HitPointsMax() * 0.75) {
						count++;
					}
				}

				if (count == allies.size())
					return false;
			}


			for (size_t i = 0; i < allies.size(); i++)
			{
				allies[i]->RemoveAllDebuffs();
				allies[i]->HealFor(EquippedWeapon().weaponEffects.SpecialEffectVal);
				allies[i]->effectOverlay.RunEffect(Enums::Effects::NextTurnHeal);
			}
			ApplySecondaryCooldown();
			return true;
		}

		else if (secondaryMove.type == Enums::SecondaryMove::LeafLordSecondary) {
			for (size_t i = 0; i < unsigned(allies.size()); i++)
			{
				Character* current = allies[i];
				current->effectOverlay.RunEffect(secondaryMove);
				float val = current->HitPointsMax() * 0.25;
				current->HealFor(val);
				current->AddToActiveEffects(MoveEffects::Get().AddShield);
				current->ReloadBuffs();
			}
			ApplySecondaryCooldown();
			return true;
		}

		else if (secondaryMove.type == Enums::SecondaryMove::ElfRangedSecondary) {
			int inactives = 0;
			int givenHits = 7;
			do {
				int targ = rand() % enemies.size();
				if (enemies[targ]->active) {
					applyDamageTo(enemies[targ], 5);
					ApplyRandomEffectTo(enemies[targ]);
					givenHits--;
					counter = 0;
				}
				else {
					inactives++;
				}
				if (inactives == enemies.size()) {
					givenHits = 0;
				}
			} while (givenHits != 0);
			ApplySecondaryCooldown();
			return true;
		}

		else if (secondaryMove.type == Enums::SecondaryMove::CentaurSecondary) {
		
			for (size_t i = 0; i < allies.size(); i++)
			{
				allies[i]->ApplyEffect(MoveEffects::Get().AddSpeed, 1);
				allies[i]->ApplyEffect(MoveEffects::Get().AddAttack, 1);
			}

		ApplySecondaryCooldown();
		return true;
		}


		else if (secondaryMove.type == Enums::SecondaryMove::ShamanOrcSecondary) {
			float hpPool = 0;
			int highHpAllies = 0;

			//Checks to see if there is only one ally (themselves) and cancels the move, as it would be useless
			if (allies.size() == 1) {
				return false;
			}

			//Checks to see if any ally is below 25% health, making the effect worthwile
			for (size_t i = 0; i < unsigned(allies.size()); i++) {
				if (allies[i]->HitPointsCurrent > allies[i]->HitPointsMax() * 0.75)
					highHpAllies++;

				if (highHpAllies == allies.size()) {
					return false;
				}
			}

			for (size_t i = 0; i < unsigned(allies.size()); i++)
			{
				hpPool += allies[i]->HitPointsCurrent;
				allies[i]->HitPointsCurrent = 0;
			}

			do {
				for (size_t i = 0; i < unsigned(allies.size()); i++)
				{
					if (allies[i]->HitPointsCurrent == allies[i]->HitPointsMax())
						continue;

					allies[i]->HitPointsCurrent++;
					hpPool--;
				}
			} while (hpPool > 0);
			ApplySecondaryCooldown();
			return true;
		}

		else {
			return false;
		}
	}


	else {
		return false;
	}
}

bool CharacterGroup::Character::ApplyPrimaryEffect(vector<Character*> allies, vector<Character*> enemies, Character* mainTarget)
{
	if (primaryMove.type == Enums::PrimaryMove::CentaurPrimary) {
		
		//if there is only this character

		if (allies.size() <= 0 || mainTarget == nullptr)
			return false;

		vector<Character*> able;

		for (size_t i = 0; i < allies.size(); i++)
		{
			if (!allies[i]->targetSet)
			able.push_back(allies[i]);
		}

		if (able.size() <= 1)
			return false;
		
		bool found = false;

		do {
			int rand = Utils::RandRange(0, able.size() - 1);
			if (able[rand] != this && able[rand]->active && able[rand]->targetSet == false) {
				targetSet = true;
				able[rand]->targetSet = true;
				able[rand]->Attack(mainTarget, 1, allies, enemies);
				found = true;
			}
		} while (!found);

		return false;

	}

	if (primaryMove.type == Enums::PrimaryMove::ShamanOrcPrimary) {
		Character* lowestHpAlly = allies[0];
		Character* highestHpEnemy = enemies[0];

		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->HitPointsCurrent < highestHpEnemy->HitPointsCurrent)
				highestHpEnemy = enemies[i];
		}

		for (size_t i = 0; i < allies.size(); i++)
		{
			if (allies[i]->HitPointsMax() - allies[i]->HitPointsCurrent > lowestHpAlly->HitPointsMax() - lowestHpAlly->HitPointsCurrent)
				lowestHpAlly = allies[i];
		}

		SoundBank::Get().Play("shamanTarget");
	
		highestHpEnemy->effectOverlay.RunEffect(primaryMove, 'e');
		float val = applyDamageTo(highestHpEnemy);
		lowestHpAlly->effectOverlay.RunEffect(primaryMove, 'a');
		lowestHpAlly->HealFor(val);
		UnsetTarget();

		return true;
	}
	return false;
}


void CharacterGroup::Character::ClearBuffs()
{
	ActiveBuffs.clear();
	hpBar.ClearBuffs();
}

void Character::ApplyActiveBuffs(bool reduceDurations) {
	/*reduce durations is called "false" when a buff stat-modifying effect is called and applied but the
	buff duration is uneffected, or when the effect is just applied.*/

	/*next turn effects like DOT or Next turn heal are exempt from this condition, as their effects
	would activate as the effect itself is being applied*/

	//resets modifiers to be re-applied from an active effect
	ShieldPortion = 1;
	DamageModifier = 1;
	SpeedModifier = 1;

	if (reduceDurations)
		for (size_t i = 0; i < unsigned(ActiveBuffs.size()); i++)
		{
			if (ActiveBuffs[i].second <= 0)
				continue;

			switch (ActiveBuffs[i].first.action) {
			case Enums::Effects::Shield:
				ShieldPortion *= PosModVal;
				break;

			case Enums::Effects::BreakShield:
				ShieldPortion *= NegModVal;
				break;

			case Enums::Effects::Speed:
				SpeedModifier *= NegModVal;
				break;

			case Enums::Effects::ReduceSpeed:
				SpeedModifier *= PosModVal;
				break;

			case Enums::Effects::Attack:
				DamageModifier *= NegModVal;
				break;

			case Enums::Effects::BreakAttack:
				DamageModifier *= PosModVal;
				break;

			case Enums::Effects::NextTurnHeal:
				HealFor(15);
				effectOverlay.RunEffect(Enums::Effects::NextTurnHeal);
				break;

			case Enums::Effects::Stun:
				StaPointsCurrent = 0;
				break;

				//deals 5% of the target's max HP (ignores armour)
			case Enums::Effects::Dot:
				//TODO
				IntakeDamage(HitPointsMax() * 0.05);
				break;
			}

			if (reduceDurations)
				ActiveBuffs[i].second--;

			if (ActiveBuffs[i].second <= 0) {
				ActiveBuffs.erase(ActiveBuffs.begin() + i);
			}
		}

	if (!reduceDurations)
		for (size_t i = 0; i < unsigned(ActiveBuffs.size()); i++)
		{
			switch (ActiveBuffs[i].first.action) {
			case Enums::Effects::Shield:
				ShieldPortion *= PosModVal;
				break;

			case Enums::Effects::BreakShield:
				ShieldPortion *= NegModVal;
				break;

			case Enums::Effects::Speed:
				SpeedModifier *= NegModVal;
				break;

			case Enums::Effects::ReduceSpeed:
				SpeedModifier *= PosModVal;
				break;

			case Enums::Effects::Attack:
				DamageModifier *= NegModVal;
				break;

			case Enums::Effects::BreakAttack:
				DamageModifier *= PosModVal;
				break;
			}
		}


	vector<pair<MoveEffect, int>> tempVec;

	for (size_t i = 0, y = 0; i < unsigned(ActiveBuffs.size()); i++)
	{
		if (ActiveBuffs[i].second >= 1)
			tempVec.push_back(make_pair(ActiveBuffs[i].first, ActiveBuffs[i].second)); //1
		y++;
	}

	ActiveBuffs.clear();
	hpBar.ClearBuffs();

	ActiveBuffs = tempVec;

	hpBar.reloadEffects(ActiveBuffs);

}

int CharacterGroup::Character::IntakeDamage(float value, bool ignoreArmour)
{
	float intake = 0;
	if (!ignoreArmour) {
		intake = (value * ShieldPortion);
	}
	else {
		intake = value;
	}

	if (hitVariations > 0) {
		string name = hitNameGroup + to_string(Utils::RandRange(1, hitVariations));
		SoundBank::Get().Play(name);
	}

	HitPointsCurrent -= intake;
	displayFloatText(to_string((int)intake), 'd');
	cout << "intook: " << intake << endl;
	hit = true;
	return intake;
}

float CharacterGroup::Character::ResultingHitpoints(float value)
{
	return HitPointsCurrent -= value * ShieldPortion;
}

void CharacterGroup::Character::ChangePosition(int newIndex, Vector2f newPosition)
{
	IndexPosition = newIndex;
	BasePos = newPosition;
	ResetEffectOverlayPos();
}

void CharacterGroup::Character::GiveWeapon(Weapon newWeapon)
{
	weaponCtrl.equippedWeapon = newWeapon;
}

const float CharacterGroup::Character::HitPointsMax()
{
	return hitPointsMax + (WeaponStats().Health);
}

const bool Character::AtBasePosition()
{
	Vector2f targetDiff = position - BasePos;
	float difference = Utils::Length(targetDiff);
	if (difference == 0) {
		return true;
	}
	else {
		return false;
	}
}

const bool CharacterGroup::Character::DeathCycleActive()
{
	return deathCycleActive;
}

void CharacterGroup::Character::ApplyPassiveEffect(Character* target)
{
	switch (secondaryMove.passiveEffect) {
	case Enums::PassiveEffects::TurnOnKill:
		cout << "Dino got another turn" << endl;
		//displayFloatText(secondaryMove.name, 'm');
		HealFor(target->HitPointsMax() * 0.20f); //Dino heal amount
		StaPointsCurrent = StaPointsMax;
		break;
	}
}

void Character::Reset()
{
	deathCycleActive = false;
	ResetOpacity();
	ClearBuffs();
	active = true;
	hpBar.visible = true;
	SetState(Enums::cState::Idle);
	weaponCtrl.ResetAnimLoop();
	targetSet = false;
	justKilled = false;
	disableEffectMHover = false;
	cSprite.setColor(Color::White);
	position = BasePos;
	HitPointsCurrent = HitPointsMax();
	StaPointsCurrent = 0;
	DamageModifier = 1;
	ShieldPortion = 1;
	SecondaryCooldown = 0;
	floatingTexts.clear();
	ResetEffectOverlayPos();
	hpBar.BalanceDisplayBars(HitPointsCurrent, StaPointsCurrent);
	ResetRectPosition();
	SetMoveSpeed(baseMoveSpeed);
}

//Moves to a target location, wether that be another character or a base position
void Character::moveTo(Vector2f targetPos, float stopDistance)
{
	
	Vector2f targetDiff = (position - targetPos);

	float difference = Utils::Length(targetDiff);

	//Creates an offset according to the attacker's size as to prevent overlap on contact
	int offset = 0;
	if (targetSet && rectSourceSprite.height > 16)
		offset = target->rectSourceSprite.height - 16;

	stopDistance += offset * 5;

	if (difference >= stopDistance) {
		position -= (Utils::SetLength(targetDiff, moveSpeed)); //5.5f //SPEED
	}

	if (difference <= stopDistance && targetPos == BasePos)
	{
		position = BasePos;
	}

	if (targetPos != BasePos && difference <= stopDistance) {
		//Target Reached

		if (attackVariations > 0)
			SoundBank::Get().Play(attackNameGroup + to_string(Utils::RandRange(1, attackVariations)));

		applyDamageTo(target);

		//Check and apply debuff to target

		if (selectedMove == 1) {
			ApplyEffectTo(target, primaryMove);
		}

		if (selectedMove == 2) {
			ApplyEffectTo(target, secondaryMove);
		}

		if (target->HitPointsCurrent <= 0) {
			ApplyPassiveEffect(target);
		}
		UnsetTarget();
	}
}

const Vector2f& CharacterGroup::Character::WidthOffset()
{
	return widthOffset;
}

void CharacterGroup::Character::SetWidthOffset() 
{
	widthOffset = Vector2f(0, 0);
	widthOffset = Vector2f((((rectSourceSprite.width - 16) * 5) / 2), 0);
	ResetRectPosition();
}

void CharacterGroup::Character::ResetRectPosition()
{
	rectSourceSprite.top = 0;
	rectSourceSprite.left = -rectSourceSprite.width;
}

void CharacterGroup::Character::HealFor(float val)
{
	if (HasHealPrevention())
		return;

	SoundBank::Get().Play("heal");

	float am = ((WeaponStats().Healing * 0.01f) + 1) * val;

	int rounded = round(am);

	cout << "healed for " << rounded << endl;

	displayFloatText(to_string(rounded), 'h');

	if (HitPointsCurrent + rounded > HitPointsMax()) {
		HitPointsCurrent = HitPointsMax();
	}
	else {
		HitPointsCurrent += rounded;
	}

}

void CharacterGroup::Character::IncreaseStaminaBar()
{
	float x = (Speed * SpeedModifier) + WeaponStats().Speed;

	if (StaPointsCurrent + x <= 100) {
		StaPointsCurrent += x;
	}
	if (StaPointsCurrent + x > 100) {
		StaPointsCurrent = 100;
	}
}

//Player controlled attack
void Character::Attack(Character* character, int move, vector<Character*> allies, vector<Character*> targets)
{
	selectedMove = move;

	target = character;

	if (selectedMove == 1) 
		ApplyPrimaryEffect(allies, targets, character);

	if (!IsRanged()) {
		SetState(Enums::cState::Move);
		targetSet = true;
	}

	if (IsRanged()) {
		targetSet = true;
		if (selectedMove == 1) {
			projectile.SetTarget(*this, *target);
		}

		if (selectedMove == 2) {
			weaponCtrl.StartAnimation();
			//uses a global effect, if applicable and ends there, if possible
			if (!ApplySecondaryEffect(allies, targets)) {
				ApplyEffectTo(target, secondaryMove);
			}
			SoundBank::Get().Play(secondaryMove.soundName);
			ApplySecondaryCooldown();
			UnsetTarget();
		}
	}
}

//Non player controlled attack
void Character::AutoMove(vector<Character*> attackableTargets, vector<Character*> allTargets, vector<Character*> allies, GlobalMoveAnimator& globalEffect) {

	targetSet = true;

	if (Affinity == 'e' && Utils::RandRange(1, 1000) == 40) {
		targetSet = false;
		return;
	}

	float lowestHp = 1000;

	int lowestHpIndex = 0;


	for (size_t i = 0; i < attackableTargets.size(); i++)
	{

		//Checks if the character can eliminate any of the targets in the array and uses their primary to do so 
		if (attackableTargets[i]->HitPointsCurrent - Damage <= 0) {
			selectedMove = 1;
			target = attackableTargets[i];
			if (!IsRanged()) {
				SetState(Enums::cState::Move);
				targetSet = true;
			}
			else {
				projectile.SetTarget(*this, *target);
			}
		}

		if (ApplySecondaryEffect(allies, allTargets)) {
			SoundBank::Get().Play(secondaryMove.soundName);
			weaponCtrl.StartAnimation();
			globalEffect.Animate(secondaryMove);
			UnsetTarget();
			break;
		}

		if (HasSecondary() && !secondaryMove.globalEffect) {
			//Uses secondary move if able
			if (!secondaryMove.selfCastOnly) {
				weaponCtrl.StartAnimation();
				bool chosen = false;
				for (size_t i = 0; i < unsigned(allies.size()); i++)
				{
					if ((allies[i]->HitPointsMax() - allies[i]->HitPointsCurrent) > (allies[lowestHpIndex]->HitPointsMax() - allies[lowestHpIndex]->HitPointsCurrent)) {
						if (allies[lowestHpIndex]->IndexPosition == 0)
							for (size_t i = 0; i < unsigned(allies.size()); i++)
							{
								if (allies[i]->IndexPosition == 2 && allies[i]->active == true) {
									continue;
								}
							}

						if (allies[lowestHpIndex]->IndexPosition == 1)
							for (size_t i = 0; i < unsigned(allies.size()); i++)
							{
								if (allies[i]->IndexPosition == 3 && allies[i]->active == true) {
									continue;
								}
							}
						lowestHpIndex = i;
						lowestHp = allies[i]->HitPointsCurrent;
					}
				}

				ApplyEffectTo(allies[lowestHpIndex], secondaryMove);
				ApplySecondaryCooldown();
				UnsetTarget();
				break;
			}

			else if (secondaryMove.selfCastOnly) {
				weaponCtrl.StartAnimation();
				ApplyEffectTo(this, secondaryMove);
				ApplySecondaryCooldown();
				UnsetTarget();
				break;
			}

		}

		//resort to primary
		else {
			for (size_t i = 0; i < unsigned(attackableTargets.size()); i++)
			{
				if (attackableTargets[i]->HitPointsCurrent < lowestHp) {
					lowestHpIndex = i;
					lowestHp = attackableTargets[i]->HitPointsCurrent;
				}

			}
			selectedMove = 1;
			target = attackableTargets[lowestHpIndex];

			if (ApplyPrimaryEffect(allies, allTargets, attackableTargets[lowestHpIndex]))
				break;

			if (!IsRanged()) {
				SetState(Enums::cState::Move);
				targetSet = true;
			}
			else {
				projectile.SetTarget(*this, *target);
			}
			break;
		}
	}
}

void Character::CheckProjHit()
{
	if (projectile.AtTargetPosition()) {

		if (target->ResultingHitpoints(Damage) <= 0) {
			ApplyPassiveEffect(target);
		}

		applyDamageTo(target);
		ApplyEffectTo(target, primaryMove);
		UnsetTarget();
		StaPointsCurrent = 0;
		projectile.ClearTarget();
	}
}

void Character::hitTarget()
{
	target->recieveHit();
}


void Character::recieveHit()
{
	cSprite.setColor(Color(218, 78, 56));
	hitCounter++;
	if (hitCounter >= 10) {
		cSprite.setColor(Color::White);
		hitCounter = 0;
		hit = false;
	}
}

void CharacterGroup::Character::ReloadBuffs()
{
	ApplyActiveBuffs(false);
	hpBar.reloadEffects(ActiveBuffs);
}

void CharacterGroup::Character::SetState(Enums::cState newState)
{
	state = newState;
	weaponCtrl.SetState(newState);
	weaponCtrl.ResetAnimLoop();
}

void CharacterGroup::Character::SetMoveSpeed(float val)
{
	moveSpeed = val;
}

void Character::IdleAnimation()
{
	rectSourceSprite.top = 0;
	if (clock.getElapsedTime().asSeconds() > animationSpeed) {
		if (rectSourceSprite.left == rectSourceSprite.width * 3) {
			rectSourceSprite.left = -rectSourceSprite.width;
			weaponCtrl.ResetAnimLoop();
		}

		rectSourceSprite.left += rectSourceSprite.width;
		weaponCtrl.NextFrame();

		cSprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void Character::MoveAnimation()
{
	rectSourceSprite.top = rectSourceSprite.height;
	if (clock.getElapsedTime().asSeconds() > animationSpeed) {
		if (rectSourceSprite.left == rectSourceSprite.width * 3) {
			rectSourceSprite.left = 0;
			weaponCtrl.ResetAnimLoop();
		}
		else {
			rectSourceSprite.left += rectSourceSprite.width;
			weaponCtrl.NextFrame();
		}


		cSprite.setTextureRect(rectSourceSprite);
		clock.restart();
	}
}

void CharacterGroup::Character::ApplyColorEffect()
{
	cSprite.setColor(Color::Black);
}

void CharacterGroup::Character::RemoveAllActiveBuffs()
{
	for (size_t i = 0; i < unsigned(ActiveBuffs.size()); i++)
	{
		ActiveBuffs.erase(ActiveBuffs.begin() + i);
	}
	ApplyActiveBuffs(false);
}
