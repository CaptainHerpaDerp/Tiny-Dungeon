#pragma once
#include <SFML/Graphics.hpp> 
#include <iostream>
#include "Map.h"
#include "Ally.h"
#include "Enemy.h"
#include "Utils.h"
#include "Scene.h"
#include "Button.h"
#include "MenuOverlay.h"
#include "WindowEffects.h"
#include "Character.h"
#include <stdlib.h>
#include <time.h>
#include "GameEndOverlay.h"
#include "SaveFileReader.h"
#include "GlobalMoveAnimator.h"
#include "WeaponDetails.h"
#include "SoundBank.h"
#include "LevelDecor.h"
#include <memory>

using namespace std;
using namespace sf;
using namespace CharacterGroup;

class Level : public Scene
{

private:
	bool StartRoutine = false;
	void Start(RenderWindow& window);

	void UpdateLevelDisplay();

	Font font;
	Font typeFont;
	Text cooldownTime;
	RichText moveInfoName;
	RichText moveInfoText;
	Text currentLevelDisplay;

	bool exitToMenu = false;
	bool restartingLevel = false;
	bool showCooldownUi = false;
	char doorStatus = 'c';
	int turnsRemaining = 0;
	int inclusions = 0;
	int positions[4];

	int moveSelectionCounter = 0;

	void IncludeE(Enums::EnemyTypes type);
	void IncludeBoss(Enums::EnemyTypes type);
	void IncludeRandomEFrom(Enums::EnemyTypes enemyGroup[]);
	void IncludeRandChar();
	void IncludeRandWeapon();
	void IncludeWeapon(Weapon weapon);
	void IncludeWeaponFrom(Weapon* group[], int size);
	void IncludeEnemyWeaponFrom(Weapon* group[], int size);
	void IncludeRandEnemyWeapon();
	void IncludeEnemyWeapon(Weapon weapon);
	void GiveWeaponToEnemy(Enums::EnemyTypes enemy, Weapon weapon);
	void SetRewardChar(Enums::AllyTypes type);

	bool MBLPress = false;
	bool MBLRelease = false;
	bool MBLHold = false;
	bool toRewardChar = false;
	bool toRewardWeapon = false;
	bool toArrange = false;
	bool menuOpen;
	bool pdMode = false;
	bool weaponMoved = false;
	bool isRearrangingCharWeapons = false;

	bool isArrangingCharacters = false;
	bool isClaimingWeapon = false;

	void SetArrange(bool condition);
	void ToggleArrangeInd(bool condition, char group = 'a');
	void LoadLevel(int number);
	void ReloadAllyPositions();
	void ToggleAllyInv();
	void SelectPrimary();
	void SelectSecondary();
	void restart();

	const bool NoEffectsRunning();
	const bool weaponSecondaryTexture();
	const vector<Enemy*> activeEnemies();
	const vector<Ally*> activeAllies();
	const vector<Character*> activeCharacters(char affinityOf = 't');

	Vector2f rewardCharPosition = Vector2f(660, 121);
	Vector2f rewardWeaponPosition = Vector2f(660, 150);
	Vector2f rewardWeaponFinishPos = Vector2f(630, 350);

	Enums::EnemyTypes MediumOrcGroup[3]{ Enums::EnemyTypes::MediumOrc,
	Enums::EnemyTypes::MediumMaskedOrc ,
	Enums::EnemyTypes::MediumShamanOrc };

	Button autoPlayButton;
	Button toggleAudioButton;
	Button homeButton;
	Button continueButton;

	MenuOverlay menuOverlay;	
	WeaponDetails weaponDetails;
	WeaponController rewardWeapon;
	Character* wepGivenCharacter;

	LevelDecor decor;

	GlobalMoveAnimator globalEffectAnim;

	vector<Character*> charactersKilled;

public:
	Level();
	~Level();


	//Using raw pointers, as the lifetime of these object match the level's lifetime 
	Ally* RewardChar;	
	Ally* AllyMoverSelect;

	vector<Ally*> Allies;
	vector<GameObject*> GameObjects;
	vector<Character*> Characters;
	vector<Enemy*> Enemies;	
	vector<Vector2f> hpBarPositions;
	vector<Button*> buttons;

	auto_ptr<GameObject> fman;

	GameObject* door;
	GameObject* allyCastIndicator;
	GameObject* enemyCastIndicator;
	GameObject* uiFrame;
	GameObject* uiAllyCircle;
	GameObject* uiMoveCardPrimary;
	GameObject* uiMoveCardSecondary;
	GameObject* uiMovePassiveBorder;
	GameObject* uiMoveSelectedBorder;
	GameObject* uiCooldownRect;
	GameObject* moveDetailsFrame;
	GameObject* currentLevelCard;
	GameObject* currentLevelCardExtended;

	Enums::AllyTypes RewardCharacter;

	Ally* allyTurn;

	bool showTurnCircle = false;
	bool showMoves = false;
	bool hideTurnUi = true;
	bool delay;

	int selectedMove = 1;
	int turn = -1;
	int currentLevel = 0;

	void DetectSave();
	void SetStartRoutine(bool condition);

	void AddGameObject(GameObject& obj);
	void InitializeCharacter(Character& obj, int intlPos);
	void AddCharacter(Enemy& obj, int index);
	void AddCharacter(Ally& obj, int index, bool active = true);
	void ToglHpbarVis(bool cond);

	bool CharArranging() const;
	bool WeaponClaim() const;
	bool WeaponArrange() const;
	bool IsAttackable(Character* character) const;
	bool InTransition() const;
	bool GetPdMode() const;
	
	void render(RenderWindow& window) override;
	void update(RenderWindow& window) override;
	void MoveAlliesDoor();
	void UpdateCastIndicators(RenderWindow& window);
	void UpdateAllyTurnCircle();
	void SaveToMenu(RenderWindow& window);
	void SaveExit(RenderWindow& window);

	bool RequestReturnMenu() const;

	void AutoAssignMove(char turnCharAffinity);
	void HandleEvents(Event& ev, RenderWindow& window);
	void SetPdMode(bool condition);
	void DisplayMoveInfo(int selected);
	void DisplayWeaponInfo(RenderWindow& window);

	void ResetInfoText(bool resetTimer = true);

	void SetLevel(int number);

	void Attack(Character& turnChar, Character* target);
	
	void ApplyRewards();
	void NextLevel();
	void CloseDoor();
	void OpenDoor();
	int LevelStatus();
	void KillEnemies();
	void KillAllies();
	void ResetAll();
	void ClearCharWeapons();
	void ResetAllies();
	void ResetCharacters();
	void RearrangeAllies(RenderWindow& window);
	void GiveRewardWeapon(RenderWindow& window);
	void RearrangeCharacterWeapon(RenderWindow& window);
	void ResetAllLocks();
	void tickStamBar();
};

