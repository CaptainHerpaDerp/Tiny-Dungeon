#include "Level.h"

Level::Level()
{
	Color BoneWhite(253, 247, 237);
	Color InkyBrown(72, 59, 58);

	if (!font.loadFromFile("Assets/Fonts/pixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	if (!typeFont.loadFromFile("Assets/Fonts/typePixelFont.ttf")) {
		cout << "Font not found" << endl;
	}

	cooldownTime.setFont(font);
	cooldownTime.setFillColor(BoneWhite);
	cooldownTime.setString(to_string(turnsRemaining));
	cooldownTime.setCharacterSize(75);
	cooldownTime.setPosition(760 - (cooldownTime.getLocalBounds().width) / 2, 1085 - (cooldownTime.getLocalBounds().height));

	moveInfoName.setFont(typeFont);

	moveInfoName.setCharacterSize(22);

	moveInfoText.setCharacterSize(16);

	moveInfoText.setFont(typeFont);
	moveInfoText.setPosition(760 - (moveInfoText.getLocalBounds().width) / 2, 1086);

	currentLevelDisplay.setFont(font);
	currentLevelDisplay.setFillColor(InkyBrown);
	currentLevelDisplay.setCharacterSize(75);
	currentLevelDisplay.setString("0");

	AddGameObject(autoPlayButton);
	AddGameObject(toggleAudioButton);
	AddGameObject(homeButton);
	AddGameObject(continueButton);

	//Allies
	charPositions.insert(pair<int, CharPositionData>(1, CharPositionData{ Vector2f(540, 800) , Vector2f(545, 981) , Vector2f(580, 951) }));
	charPositions.insert(pair<int, CharPositionData>(2, CharPositionData{ Vector2f(780, 800) , Vector2f(785, 981) , Vector2f(820, 951) }));
	charPositions.insert(pair<int, CharPositionData>(3, CharPositionData{ Vector2f(540, 640) , Vector2f(545, 821) , Vector2f(580, 791) }));
	charPositions.insert(pair<int, CharPositionData>(4, CharPositionData{ Vector2f(780, 640) , Vector2f(785, 821) , Vector2f(820, 791) }));

	//Enemies
	charPositions.insert(pair<int, CharPositionData>(-1, CharPositionData{ Vector2f(540, 240) , Vector2f(545, 341) , Vector2f(580, 311) }));
	charPositions.insert(pair<int, CharPositionData>(-2, CharPositionData{ Vector2f(780, 240) , Vector2f(785, 341) , Vector2f(820, 311) }));
	charPositions.insert(pair<int, CharPositionData>(-3, CharPositionData{ Vector2f(540, 400) , Vector2f(545, 501) , Vector2f(580, 471) }));
	charPositions.insert(pair<int, CharPositionData>(-4, CharPositionData{ Vector2f(780, 400) , Vector2f(785, 501) , Vector2f(820, 471) }));

	//Boss
	charPositions.insert(pair<int, CharPositionData>(-5, CharPositionData{ Vector2f(668, 368) , Vector2f(665, 471), Vector2f(700, 441) }));

	autoPlayButton.SetType(Enums::ButtonTypes::AutoPlay);
	buttons.push_back(&autoPlayButton);

	toggleAudioButton.SetType(Enums::ButtonTypes::Audio);
	buttons.push_back(&toggleAudioButton);

	homeButton.SetType(Enums::ButtonTypes::Menu);
	buttons.push_back(&homeButton);

	continueButton.SetType(Enums::ButtonTypes::NextLevel);
	buttons.push_back(&continueButton);
	continueButton.visible = false;

	decor.Randomize();

	menuOverlay.IsReturnMenu(true);
	menuOverlay.CloseMenu();

}

Level::~Level()
{

}

//Runs on the very first frame
void Level::Start(RenderWindow& window)
{
	auto it = charPositions.find(1);

	DetectSave();

	RewardChar->SetPosition(rewardCharPosition);
	menuOverlay.SetPosition(505, 320);
	homeButton.SetPosition(30, 1075);
	continueButton.SetPosition(703 - (float)(continueButton.rectSourceSprite.width * 5) / 2, 256);
	toggleAudioButton.SetPosition(115, 1075);
	uiMovePassiveBorder->SetPosition(760 + (77 * 5), 1101);
	moveDetailsFrame->SetPosition(700, 911);
	moveInfoName.setPosition(698 - (moveInfoName.getLocalBounds().width) / 2, 828.5f);
	moveInfoText.setPosition((moveDetailsFrame->position - Vector2f(155.0f, 40.0f)));
	currentLevelCard->SetPosition(1105, 1105);
	currentLevelCardExtended->SetPosition(1130, 1105);	autoPlayButton.SetPosition(200, 1075);

	rewardWeapon.SetPosition(rewardWeaponPosition);

	UpdateLevelDisplay();

	StartRoutine = true;

}

void Level::DetectSave()
{
	if (SaveFileReader::Get().HasSave()) {
		SaveFileReader::Get().LoadGame(currentLevel, Allies, Enemies, RewardCharacter, pdMode);
		ReloadAllyPositions();

		if (currentLevel % 5 == 0) {
			decor.SetBossFountain(true);

			if (SoundBank::Get().IsMuted())
				return;
			SoundBank::Get().bossSong.setLoop(true);
			SoundBank::Get().bossSong.play();
		}

		if (((int)RewardCharacter) >= 0) {
			SetRewardChar(RewardCharacter);
		}
	}
	else {
		LoadLevel(1);
	}
}

void Level::SetStartRoutine(bool condition)
{
	StartRoutine = condition;
}

void Level::UpdateLevelDisplay()
{
	if (pdMode) {
		currentLevelDisplay.setFillColor(Color(88, 13, 13));
	}
	else {
		currentLevelDisplay.setFillColor(WindowEffects::Get().DirtyInk);
	}

	currentLevelDisplay.setString(to_string(currentLevel));


	if (currentLevel < 10) {
		currentLevelDisplay.setPosition(currentLevelCard->position.x - (currentLevelDisplay.getLocalBounds().width) / 2,
			currentLevelCard->position.y - (currentLevelDisplay.getLocalBounds().height) - 15);
		currentLevelCardExtended->visible = false;
		currentLevelCard->visible = true;
	}
	else {
		currentLevelDisplay.setPosition(currentLevelCardExtended->position.x - (currentLevelDisplay.getLocalBounds().width) / 2,
			currentLevelCardExtended->position.y - (currentLevelDisplay.getLocalBounds().height) - 15);
		currentLevelCardExtended->visible = true;
		currentLevelCard->visible = false;
	}
}

void Level::update(RenderWindow& window)
{
	if (!StartRoutine) {
		Start(window);
	}

	//continues the restart sequence
	if (restartingLevel) {
		restart();
	}

	if (homeButton.IsToggled()) {
		menuOverlay.OpenMenu();
	}

	//Checks for pressed exit button and saves game
	if (menuOverlay.exit) {

		SaveExit(window);
	}

	if (menuOverlay.toClose == true) {
		homeButton.IsToggled(false);
		menuOverlay.toClose = false;
	}

	if (!homeButton.IsToggled())
	{
		menuOverlay.CloseMenu();

		//Checks if player has toggled autoplay
		if (autoPlayButton.IsToggled() && turn != -1 && Characters[turn]->Affinity == 'a' && Characters[turn]->state == Enums::cState::Idle && Characters[turn]->StaPointsCurrent >= 100 && Characters[turn]->active && NoEffectsRunning()) {
			AutoAssignMove('a');
		}

		if (toggleAudioButton.IsToggled()) {
			SoundBank::Get().Mute();
		}
		else {
			SoundBank::Get().Unmute();
		}

		//Checks if Enemies' turn
		if (turn != -1 && Characters[turn]->Affinity == 'e' && Characters[turn]->state == Enums::cState::Idle && Characters[turn]->StaPointsCurrent >= 100 && Characters[turn]->active && NoEffectsRunning()) {
			AutoAssignMove('e');
		}
	}

	//Check if Character with turn has returned from attacking and sets the turn back to neutral
	if (turn != -1) {

		if (Characters[turn]->active == false)
			turn = -1;

		if (turn != -1 && Characters[turn]->StaPointsCurrent == 0 && Characters[turn]->AtBasePosition() && !Characters[turn]->targetSet && NoEffectsRunning() && LevelStatus() == 0) {
			turn = -1;
		}
	}

	//Advance all characters' attack bar if none are currently at the maximum (their turn)
	if (!globalEffectAnim.IsAnimating())
		if (turn == -1 || Characters[turn]->active == false) {
			showTurnCircle = false;
			tickStamBar();
		}

	//Moves the move border's "selected" indicator based on the move clicked upon
	if (selectedMove == 2) {
		uiMoveSelectedBorder->SetPosition(760, 1101);
	}
	if (selectedMove == 1) {
		uiMoveSelectedBorder->SetPosition(640, 1101);
	}

	//Updating turn circle's position to that of the ally's turn
	if (showTurnCircle)
		UpdateAllyTurnCircle();

	if (turn != -1) {
		//Hides the ALLY and Enemy cast indicator by default, then enables it again if the conditions are met
		UpdateCastIndicators(window);
	}

	if (WindowEffects::Get().IsFaded())
		WindowEffects::Get().FadeClear();


	//Updates all objects added from main
	for (size_t i = 0; i < GameObjects.size(); i++)
	{
		GameObjects[i]->update();
	}


	//Checks if ally has been killed, stores them in a vector
	for (size_t i = 0; i < Characters.size(); i++)
	{
		Characters[i]->update();
		if (Characters[i]->active && Characters[i]->DeathCycleActive()) {
			if (find(charactersKilled.begin(), charactersKilled.end(), Characters[i]) != charactersKilled.end()) {
			}
			else {
				charactersKilled.push_back(Characters[i]);
			}
		}
	}

	for (size_t i = 0; i < buttons.size(); i++)
	{

		if (Utils::MouseBoundsOf(*buttons[i], window)) {
			buttons[i]->EnterHover();
		}
		else {
			buttons[i]->ExitHover();
		}
	}

	uiMovePassiveBorder->Animate(7, 22, 22, 0.08f);
	RewardChar->update();
	rewardWeapon.update();
	uiMoveCardPrimary->update();
	uiMoveCardSecondary->update();
	menuOverlay.update(window);
	globalEffectAnim.update();
	weaponDetails.update();
	decor.update();

	if (menuOverlay.restartButton.IsToggled()) {
		restart();
	}

	//menu button
	if (menuOverlay.mainMenuButton.IsToggled()) {
		//save to menu

		menuOverlay.LockAll();

		WindowEffects::Get().FadeBlack();
		if (!WindowEffects::Get().IsFaded())
			return;

		WindowEffects::Get().FadeClear();
		for (size_t i = 0; i < charactersKilled.size(); i++)
		{
			charactersKilled[i]->Reset();
			charactersKilled[i]->hpBar.visible = false;
		}
		charactersKilled.clear();

		SaveFileReader::Get().SaveGame(currentLevel, Allies, Enemies, RewardChar, toRewardChar, toRewardWeapon, pdMode);

		exitToMenu = true;
		menuOverlay.mainMenuButton.IsToggled(false);
	}

	if (isArrangingCharacters) {
		RearrangeAllies(window);
	}

	if (isClaimingWeapon) {

		rewardWeaponFinishPos = Vector2f(((float)window.getSize().x / 2) - (16 * 5) / 2, ((float)window.getSize().y / 2) - (32 * 5) + 6);

		if (wepGivenCharacter == nullptr && weaponMoved == false && Utils::DistanceTo(rewardWeapon.position, rewardWeaponFinishPos) > 5) {
			rewardWeapon.MoveTo(rewardWeaponFinishPos);
		}
		else {
			weaponMoved = true;
			GiveRewardWeapon(window);
		}
	}

	if (isRearrangingCharWeapons && !isArrangingCharacters) {
		RearrangeCharacterWeapon(window);
	}

	if (isRearrangingCharWeapons || isArrangingCharacters || isClaimingWeapon && weaponMoved) {
		continueButton.visible = true;
		if (Utils::MouseBoundsOf(continueButton, window) && MBLPress) {
			ToggleArrangeInd(false);
			isArrangingCharacters = false;
			isRearrangingCharWeapons = false;
			isClaimingWeapon = false;
		}
	}
	else {
		continueButton.visible = false;
	}

	//locks play button function and turn circle visibility and displays an open door
	if (InTransition()) {
		showMoves = false;
		autoPlayButton.Lock();
		showTurnCircle = false;
		ToglHpbarVis(false);
	}

	//Displays information about the hovered move
	if (Utils::MouseBoundsOf(*uiMoveCardPrimary, window) && turn >= 0) {

		if (moveSelectionCounter >= MouseHoverTime)
		{
			DisplayMoveInfo(1);
		}
		else {
			moveSelectionCounter++;
		}
	}
	else if (Utils::MouseBoundsOf(*uiMoveCardSecondary, window) && turn >= 0) {

		if (moveSelectionCounter >= MouseHoverTime) {
			DisplayMoveInfo(2);
		}
		else {
			moveSelectionCounter++;
		}
	}
	else {
		ResetInfoText();
	}

	//Sets mouse pressed condition to false as it is made true earlier in the same frame by HandleEvents()
	MBLPress = false;
	MBLRelease = false;
}

void Level::MoveAlliesDoor()
{
	showTurnCircle = false;
	ToggleArrangeInd(false);

	for (size_t i = 0; i < activeAllies().size(); i++)
	{
		activeAllies()[i]->SetMoveSpeed(6.5f);
		activeAllies()[i]->BasePos = door->position - Vector2f(10, 100);
		activeAllies()[i]->SetState(Enums::cState::Move);
	}
}

void Level::UpdateCastIndicators(sf::RenderWindow& window)
{
	allyCastIndicator->visible = false;
	if (!InTransition() && Characters[turn]->secondaryMove.targetMode == 'a' && selectedMove == 2 || Characters[turn]->primaryMove.targetMode == 'a' && selectedMove == 1)
	{
		for (size_t i = 0; i < Characters.size(); i++)
		{
			Character* cur = Characters[i];

			if (cur->Affinity == 'a' && Utils::MouseBoundsOf(*cur, window) && cur->active) {
				allyCastIndicator->visible = true;

				auto pos = charPositions.find(cur->IndexPosition);
				allyCastIndicator->SetPosition(pos->second.castPos);
			}
		}
	}

	enemyCastIndicator->visible = false;

	if (turn != -1 && !InTransition() && Characters[turn]->secondaryMove.targetMode == 'e' && selectedMove == 2 || Characters[turn]->primaryMove.targetMode == 'e' && selectedMove == 1)
	{
		for (size_t i = 0; i < Characters.size(); i++)
		{
			Character* cur = Characters[i];
			if (cur->active && cur->Affinity == 'e' && IsAttackable(cur) && Utils::MouseBoundsOf(*cur, window) && cur->state == Enums::cState::Idle) {
				enemyCastIndicator->visible = true;

				auto pos = charPositions.find(cur->IndexPosition);
				enemyCastIndicator->SetPosition(pos->second.castPos);
			}
		}
	}
}

void Level::UpdateAllyTurnCircle()
{
	if (Characters[turn]->Affinity == 'a') {
		auto pos = charPositions.find(Characters[turn]->IndexPosition);
		uiAllyCircle->SetPosition(pos->second.castPos);
	}
}

void Level::SaveExit(sf::RenderWindow& window)
{
	for (size_t i = 0; i < charactersKilled.size(); i++)
	{
		charactersKilled[i]->Reset();
		charactersKilled[i]->hpBar.visible = false;
	}
	charactersKilled.clear();

	SaveFileReader::Get().SaveGame(currentLevel, Allies, Enemies, RewardChar, toRewardChar, toRewardWeapon, pdMode);
	window.close();
}

void Level::SaveToMenu(sf::RenderWindow& window)
{
	vector<Ally> allies;

	for (size_t i = 0; i < charactersKilled.size(); i++)
	{
		charactersKilled[i]->Reset();
		charactersKilled[i]->hpBar.visible = false;
	}
	charactersKilled.clear();

	SaveFileReader::Get().SaveGame(currentLevel, Allies, Enemies, RewardChar, toRewardChar, toRewardWeapon, pdMode);
	window.close();
}

void Level::render(RenderWindow& window)
{
	map.DrawMap(window);
	decor.render(window);

	allyCastIndicator->render(window);
	enemyCastIndicator->render(window);

	if (showTurnCircle && turn != -1 && Characters[turn]->AtBasePosition()) {
		uiAllyCircle->render(window);
	}

	else {
		uiAllyCircle->SetPosition(-100, -100);
	}

	for (size_t i = 0; i < GameObjects.size(); i++)
	{
		GameObjects[i]->render(window);
	}

	for (size_t i = 0; i < Characters.size(); i++)
	{
		Characters[i]->render(window);
		/*if (Utils::MouseBoundsOf(*Characters[i], window)) {	
			cout << Characters[i]->EquippedWeapon().id << endl;
		}*/
	}

	moveDetailsFrame->render(window);
	window.draw(moveInfoName);
	window.draw(moveInfoText);
	window.draw(currentLevelDisplay);

	if (showMoves) {
		uiMoveCardPrimary->render(window);
		uiMoveCardSecondary->render(window);
		uiMovePassiveBorder->render(window);
		uiMoveSelectedBorder->render(window);
	}
	globalEffectAnim.render(window);

	if (showCooldownUi) {
		uiCooldownRect->render(window);
		window.draw(cooldownTime);
	}

	if (toRewardChar)
		RewardChar->render(window);

	if (isClaimingWeapon || toRewardWeapon)
		rewardWeapon.render(window);

	DisplayWeaponInfo(window);

	menuOverlay.render(window);
	weaponDetails.render(window);
}

void Level::AddGameObject(GameObject& obj)
{
	GameObjects.push_back(&obj);
}

void Level::AddCharacter(Enemy& obj, int index)
{
	Enemies.push_back(&obj);
	InitializeCharacter(obj, index);
}

void Level::AddCharacter(Ally& obj, int index, bool active)
{
	Allies.push_back(&obj);
	obj.active = active;
	InitializeCharacter(obj, index);
}

/// <summary>
/// Sets visibility of all character's HpBars to provided condition
/// </summary>
/// <param name="cond"></param>
void Level::ToglHpbarVis(bool cond)
{
	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (Characters[i]->hpBar.visible != cond)
			Characters[i]->hpBar.visible = cond;
	}
}

//Sets up the character's ui and base position
void Level::InitializeCharacter(Character& obj, int intlPos)
{
	auto pos = charPositions.find(intlPos);
	obj.IndexPosition = pos->first;
	obj.BasePos = pos->second.charPos;
	obj.hpBar.position = pos->second.hpBarPos;
	obj.position = obj.BasePos;
	Characters.push_back(&obj);
}

//Returns true if the turn character is able to attack the character provided in the constructor
bool Level::IsAttackable(Character* character) const
{
	Character* turnChar = Characters[turn];

	if (character->active == false) {
		return false;
	}

	if (turnChar->Affinity == 'a' && turnChar->secondaryMove.globalEffect && turnChar->secondaryMove.targetMode == 'e' && selectedMove == 2)
		return true;

	if (turnChar->Affinity == character->Affinity)
		if (turnChar->secondaryMove.targetMode == 'a' && selectedMove == 2 || turnChar->primaryMove.targetMode == 'a' && selectedMove == 1)
			return true;


	if (turnChar->Affinity != character->Affinity)
		if (turnChar->secondaryMove.targetMode == 'a' && selectedMove == 2 || turnChar->primaryMove.targetMode == 'a' && selectedMove == 1)
			return false;

	if (character->IndexPosition == 3 || character->IndexPosition == 4 || character->IndexPosition == -3 || character->IndexPosition == -4 || character->IndexPosition == -5)
		return true;


	switch ((character->IndexPosition)) {
	case 1:
		for (size_t i = 0; i < Characters.size(); i++)
		{
			if (Characters[i]->IndexPosition == 3 && Characters[i]->active)
			{
				return false;
			}
		}
		return true;
		break;

	case 2:
		for (size_t i = 0; i < Characters.size(); i++)
		{
			if (Characters[i]->IndexPosition == 4 && Characters[i]->active)
			{
				return false;
			}
		}
		return true;
		break;

	case -1:
		for (size_t i = 0; i < Characters.size(); i++)
		{
			if (Characters[i]->IndexPosition == -3 && Characters[i]->active)
			{
				return false;
			}
		}
		return true;
		break;

	case -2:
		for (size_t i = 0; i < Characters.size(); i++)
		{
			if (Characters[i]->IndexPosition == -4 && Characters[i]->active)
			{
				return false;
			}
		}
		return true;
		break;
	}

	return false;
}

//Automatically moves the turn character, ally or enemy
void Level::AutoAssignMove(char turnCharAffinity)
{
	char enemyAffinity;

	if (turnCharAffinity == 'a') {
		enemyAffinity = 'e';
	}
	else {
		enemyAffinity = 'a';
	}

	vector<Character*> attackables;
	vector<Character*> enemies;
	vector<Character*> allies;

	showTurnCircle = false;

	Character* turnChar = Characters[turn];

	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (Characters[i]->active && Characters[i]->Affinity == enemyAffinity) {
			enemies.push_back(Characters[i]);
		}

		if (IsAttackable(Characters[i]) && Characters[i]->Affinity == enemyAffinity) {
			attackables.push_back(Characters[i]);
		}

		if (Characters[i]->active && Characters[i]->Affinity == turnCharAffinity) {
			allies.push_back(Characters[i]);
		}
	}

	if (enemies.size() == 0) {
		return;
	}

	turnChar->StaPointsCurrent = 0;
	turnChar->AutoMove(attackables, enemies, allies, globalEffectAnim);

}

//Manages all inputs
void Level::HandleEvents(Event& event, RenderWindow& window)
{
	if (GameEndOverlay::Get().Locked())
		return;

	menuOverlay.HandleEvents(event, window);

	switch (event.type)
	{
	case Event::Closed:
		window.close();
		break;

	case Event::KeyPressed:

		if (event.key.code == Keyboard::S) {
		}

		if (event.key.code == Keyboard::K) {
			KillAllies();
		}

		if (event.key.code == Keyboard::R) {
			decor.Randomize();

			bool unique = false;
			do
			{
				RewardCharacter = static_cast<Enums::AllyTypes>(rand() % 10);

				unique = true;

				for (size_t i = 0; i < Allies.size(); i++)
				{
					if (Allies[i]->type == RewardCharacter)
						unique = false;
				}

			} while (!unique);
			RewardChar->Transmog(RewardCharacter);

		}

		if (event.key.code == Keyboard::Num3) {
			Allies[0]->GiveWeapon(rewardWeapon.LifeStaff);
		}

		if (event.key.code == Keyboard::Num4) {
			Allies[0]->weaponCtrl.ClearWeapon();
		}

		if (event.key.code == Keyboard::L) {
			Allies[0]->HitPointsCurrent = 0;
		}

		if (event.key.code == Keyboard::N)
			KillEnemies();

		if (event.key.code == Keyboard::Escape) {
			homeButton.Activate();
		}

#pragma region  mover

		if (event.key.code == Keyboard::K) {
			KillAllies();
		}

		if (event.key.code == Keyboard::N)
			KillEnemies();

		if (event.key.code == Keyboard::Num1) {
			SelectPrimary();
		}

		if (event.key.code == Keyboard::Num2) {
			SelectSecondary();
		}

		if (event.key.code == Keyboard::Num6) {
			SetLevel(10);
		}


		break;
#pragma endregion

	case Event::MouseButtonReleased:
		MBLHold = false;
		MBLRelease = true;

		if (!InTransition() && !homeButton.IsToggled() && event.mouseButton.button == Mouse::Left && turn != -1 && Characters[turn]->Affinity == 'a' && NoEffectsRunning())
		{
			for (size_t i = 0; i < Characters.size(); i++)
			{
				Character* target = Characters[i];
				Character* turnChar = Characters[turn];

				if (turn != -1 && turnChar->StaPointsCurrent >= 100 && turnChar->AtBasePosition() && target->active && !turnChar->targetSet && Utils::MouseBoundsOf(*target, window)) {
					if (target->Affinity == 'e' && IsAttackable(target)) {
						Attack(*turnChar, target);
					}

					if (target->Affinity == 'a') {
						if (turnChar->SecondaryCooldown == 0 && selectedMove == 2 && turnChar->secondaryMove.targetMode == 'a') {
							target->hpBar.added = false;
							// bug zone 
							turnChar->weaponCtrl.StartAnimation();
							if (!turnChar->ApplySecondaryEffect(activeCharacters('a'), activeCharacters('e'))) {
								turnChar->ApplyEffectTo(target, turnChar->secondaryMove);
							}
							SoundBank::Get().Play(turnChar->secondaryMove.soundName);
							turnChar->ApplySecondaryCooldown();
							turnChar->StaPointsCurrent = 0;
						}
					}
				}
			}
		}

		//Detects mouse overlap with buttons and activates them accordingly
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (Utils::MouseBoundsOf(*buttons[i], window)) {
				buttons[i]->Activate();
			}
		}

		//Detect mouse overlap with move cards and changes the selected move accordingly
		if (turn >= 0 && !InTransition()) {

			if (Utils::MouseBoundsOf(*uiMoveCardPrimary, window)) {
				SelectPrimary();
			}

			if (Utils::MouseBoundsOf(*uiMoveCardSecondary, window)) {
				SelectSecondary();
			}
		}
		break;

	case Event::MouseButtonPressed:
		MBLHold = true;
		MBLPress = true;
		break;
	}
}

void Level::SetPdMode(bool condition)
{
	pdMode = condition;
}

//Displays relevant information about the allied character's moves
void Level::DisplayMoveInfo(int selected)
{

	Character* turnChar = Characters[turn];

	ResetInfoText(false);

	moveDetailsFrame->visible = true;

	if (selected == 1) {
		moveInfoName << WindowEffects::Get().BoneWhite << turnChar->primaryMove.name;
		moveInfoName.setPosition(698 - (moveInfoName.getLocalBounds().width) / 2, 835);

		switch (turnChar->primaryMove.type) {
		case Enums::PrimaryMove::DinoPrimary:
			//moveInfoText << WindowEffects::Get().BoneWhite << "Attacks an enemy and has\na " << to_string((int)(100 / turnChar->primaryMove.effectChance)) << "% chance of removing\none of their beneficial\neffects";
			moveInfoText << WindowEffects::Get().BoneWhite << "Attacks an enemy to deal\n" << turnChar->TotalDamageWeaponIncl() << " and has a\n" << to_string((int)(100 / turnChar->primaryMove.effectChance)) << "% chance of removing\none of their beneficial\neffects";
			break;

		case Enums::PrimaryMove::KnightPrimary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Attacks an enemy to deal\n" << turnChar->TotalDamageWeaponIncl() << " and has\na " << to_string((int)(100 / turnChar->primaryMove.effectChance)) << "% chance of stunning\nthem for " << to_string(turnChar->primaryMove.effect.duration) << " turns";
			break;

		case Enums::PrimaryMove::BlueMagePrimary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Casts a bolt at an enemy\ndealing " << turnChar->TotalDamageWeaponIncl() << "\nand reduces their attack\nbar by " << to_string(ReduceStaminaAmount) << "% ";
			break;

		case Enums::PrimaryMove::ElfRangedPrimary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Shoots target enemy and\ndeals " << turnChar->TotalDamageWeaponIncl() << "\nwith a " << to_string((int)(100 / turnChar->primaryMove.effectChance)) << "% chance of\nbreaking their defence\nfor " << to_string(turnChar->primaryMove.effect.duration) << " turns";
			break;

		case Enums::PrimaryMove::CentaurPrimary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Attacks target enemy and\ndeals " << turnChar->TotalDamageWeaponIncl() << "\nwhile a random ally\nattacks simultaneously";
			break;
		}
	}



	if (selected == 2) {
		moveInfoName << WindowEffects::Get().BoneWhite << turnChar->secondaryMove.name;
		moveInfoName.setPosition(698 - (moveInfoName.getLocalBounds().width) / 2, 835);

		string healBonus = "";
		int totalHeal = 0;

		switch (turnChar->secondaryMove.type) {
		case Enums::SecondaryMove::DinoSecondary:
			if (turnChar->WeaponStats().Healing == 0)
				healBonus = "20%";
			if (turnChar->WeaponStats().Healing != 0) {
				totalHeal = ((turnChar->WeaponStats().Healing * 0.01f) + 1) * 20;
				healBonus = to_string(totalHeal) + "(" + Utils::PosOrNeg(turnChar->WeaponStats().Healing) + to_string(turnChar->WeaponStats().Healing) + "%)";
			}

			moveInfoText << WindowEffects::Get().BoneWhite << "Defeating an enemy with\nthis character grants\nanother turn and heals\nfor " << healBonus << " of the\nenemy's maximum hp";
			//moveInfoText.setString(Utils::AutoBreak("Grants another turn whenan enemy is defeated   and heals 20 percent ofthe enemies max hp", 23));
			break;

		case Enums::SecondaryMove::KnightSecondary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Grants target ally a\nshield that blocks " << to_string((int)(PosModVal * 100)) << "%\nof incoming damage for\n" << to_string(turnChar->secondaryMove.effect.duration) << " turns";
			break;

		case Enums::SecondaryMove::BlueMageSecondary:

			if (turnChar->WeaponStats().SpecialEffect == Enums::SpecWpnEfct::BonusHeal) {
				totalHeal = ((turnChar->WeaponStats().SpecialEffectVal * 0.01f) + 1) * 30;
				healBonus = "(" + Utils::PosOrNeg(turnChar->WeaponStats().SpecialEffectVal) + to_string(turnChar->WeaponStats().SpecialEffectVal) + "%)";
			}
			else {
				totalHeal = 30;
			}

			moveInfoText << WindowEffects::Get().BoneWhite << "Heals a target ally for\n" << to_string(totalHeal) << healBonus << " points, and\ngrants them a buff to\nheal again on their\nnext turn";
			break;

		case Enums::SecondaryMove::ElfRangedSecondary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Fires 7 projectiles\nwhich randomly hit\nenemies, each dealing\n" << turnChar->TotalDamageWeaponIncl();
			break;

		case Enums::SecondaryMove::CentaurSecondary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Grants all allies attack\nand speed buffs for\n1 turn";
			break;

		case Enums::SecondaryMove::ForestStaffSecondary:
			moveInfoText << WindowEffects::Get().BoneWhite << "Heals all allies for\n" << to_string(turnChar->WeaponStats().SpecialEffectVal) << " points and removes\nall harmful effects\nthey may have";
			break;

		}
	}
}

void Level::DisplayWeaponInfo(RenderWindow& rw)
{
	for (size_t i = 0; i < Allies.size(); i++)
	{
		if (Allies[i]->active && Allies[i]->state == Enums::cState::Idle)
			weaponDetails.Display(&Allies[i]->weaponCtrl, rw);
	}
}

//Resets the info displayed when hovering over a move as well as the time required to trigger the display of info to zero
void Level::ResetInfoText(bool resetTimer)
{
	if (resetTimer)
		moveSelectionCounter = 0;

	moveDetailsFrame->visible = false;
	moveInfoText.clear();
	moveInfoName.clear();
}

//Reduces all allies' health to zero (debug)
void Level::KillAllies() {

	cout << "Kill All Allies" << endl;

	for (size_t i = 0; i < Allies.size(); i++)
	{
		Allies[i]->HitPointsCurrent = 0;
	}
}

//Reduces all enemies' health to zero (debug)
void Level::KillEnemies() {

	cout << "Kill All Enemies" << endl;

	for (size_t i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->HitPointsCurrent = 0;

	}
}

//Resets active allies and linked ui elements
void Level::ResetAllies()
{
	for (size_t i = 0; i < Allies.size(); i++)
	{
		Ally* ally = Allies[i];

		if (ally->active) {
			auto pos = charPositions.find(ally->IndexPosition);
			ally->hpBar.position = pos->second.hpBarPos;
			ally->Reset();
		}
	}
}

//Resets ally positions, states and adaptive stats
void Level::ApplyRewards()
{
	if (toRewardChar) {
		SoundBank::Get().Play("recieveReward");
		for (size_t i = 0; i < Allies.size(); i++)
		{
			if (!Allies[i]->active) {
				Allies[i]->Reset();
				Allies[i]->Transmog(RewardCharacter);
				Allies[i]->position = rewardCharPosition;
				Allies[i]->active = true;
				break;
			}
		}
		isArrangingCharacters = true;
		RewardChar->visible = false;
		toRewardChar = false;
	}

	if (toRewardWeapon) {
		SoundBank::Get().Play("recieveReward");
		isClaimingWeapon = true;
		toRewardWeapon = false;
	}
}

//Resets all characters and their linked ui elements
void Level::ResetCharacters() {
	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (Characters[i]->active)
			Characters[i]->Reset();
	}
}

//Resets the level and all characters
void Level::ResetAll() {
	toRewardChar = false;
	toRewardWeapon = false;
	isClaimingWeapon = false;
	restartingLevel = false;
	exitToMenu = false;
	weaponMoved = false;
	inclusions = 0;
	charactersKilled.clear();
	menuOverlay.toClose = true;
	ResetAllLocks();
	ResetCharacters();
	ReloadAllyPositions();
	SetArrange(false);
	UpdateLevelDisplay();
	door->SetTexture(TextureBank::Get().Door);
}

void Level::ClearCharWeapons()
{
	for (size_t i = 0; i < Characters.size(); i++)
	{
		Characters[i]->weaponCtrl.ClearWeapon();
	}
}

//Increases all characters' stamina bars by their speed each frame until one is full
void Level::tickStamBar()
{
	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (Characters[i]->StaPointsCurrent == 100.0f && turn == -1 && Characters[i]->active) {

			turn = i;
			Character* turnChar = Characters[turn];

			turnChar->cSprite.setColor(WindowEffects::Get().BoneWhite);

			//Checks if equipped weapon will replace the character's secondary
			turnChar->WpnSecondaryOverride();

			if (turnChar->secondaryMove.passiveEffect != Enums::PassiveEffects::None) {
				uiMovePassiveBorder->visible = true;
			}
			else {
				uiMovePassiveBorder->visible = false;
			}

			selectedMove = 1;

			//Applies buff at the beginning of the character's turn
			turnChar->ApplyActiveBuffs();

			//Recuces secondary move's cooldown time
			if (turnChar->SecondaryCooldown > 0) {
				turnChar->SecondaryCooldown--;
				showCooldownUi = true;
				cooldownTime.setString(to_string(turnChar->SecondaryCooldown));
			}

			if (turnChar->SecondaryCooldown == 0)
				showCooldownUi = false;

			uiMoveCardPrimary->SetTexture(turnChar->primaryMove.cardTexture);
			if (!weaponSecondaryTexture())
				uiMoveCardSecondary->SetTexture(turnChar->secondaryMove.cardTexture);

			showMoves = true;
			showTurnCircle = true;

			if (turnChar->Affinity == 'e') {
				if (hideTurnUi) {
					showMoves = false;
					showTurnCircle = false;
					showCooldownUi = false;
				}
			}
		}

		if (Characters[i]->StaPointsCurrent < Characters[i]->StaPointsMax && Characters[i]->active && turn == -1) {
			Character* turnChar = Characters[i];
			turnChar->IncreaseStaminaBar();
		}
	}
}

//Allows the player to rearrange allies
void Level::RearrangeAllies(RenderWindow& rw)
{
	Vector2f mpos = (Vector2f)Mouse::getPosition(rw);

	for (size_t i = 0; i < Allies.size(); i++)
	{
		ToggleArrangeInd(true, 'v');

		if (Allies[i]->active == true && AllyMoverSelect == nullptr) {

			if (Utils::MouseBoundsOf(*Allies[i], rw) && MBLPress) {
				AllyMoverSelect = Allies[i];
			}
		}

		//To switch selected character with another

		if (AllyMoverSelect != nullptr && AllyMoverSelect->active) {
			ToggleArrangeInd(true, 'a');
			for (size_t i = 0; i < Allies.size(); i++)
			{
				if (Allies[i] != AllyMoverSelect) {
					if (Utils::MouseBoundsOf(*Allies[i], rw) && MBLRelease) {

						int SelIndexCopy = AllyMoverSelect->IndexPosition;
						int SwitchIndexPosCopy = Allies[i]->IndexPosition;

						Vector2f SelBasePosCopy = AllyMoverSelect->BasePos;
						Vector2f SwitchBasePosCopy = Allies[i]->BasePos;

						AllyMoverSelect->ChangePosition(SwitchIndexPosCopy, SwitchBasePosCopy);

						Allies[i]->ChangePosition(SelIndexCopy, SelBasePosCopy);

						AllyMoverSelect = nullptr;
					}
				}
			}
		}

		if (AllyMoverSelect != nullptr) {
			AllyMoverSelect->ArrangeIndicator.ToggleSelected(true);
		}

		if (AllyMoverSelect == nullptr) {
			ToggleArrangeInd(true, 'v');
			for (size_t i = 0; i < Allies.size(); i++)
			{
				Allies[i]->ArrangeIndicator.ToggleSelected(false);
			}
		}
	}
}

/// <summary>
/// Allows the player to give one of their characters the level's reward weapon,
/// if a selected character already has a weapon, trades the reward weapon for the character's weapon
/// and waits for the leftover weapon to be given. Automatically switches to RearrangeCharWeapons() when
/// there no longer is a weapon to be given
/// </summary>
/// <param name="rw"></param>
void Level::GiveRewardWeapon(RenderWindow& rw)
{
	Vector2f mpos = (Vector2f)Mouse::getPosition(rw);

	for (size_t i = 0; i < Allies.size(); i++)
	{
		ToggleArrangeInd(true, 'v');

		if (!Allies[i]->active)
			continue;

		if (Utils::MouseBoundsOf(*Allies[i], rw) && MBLPress) {
			if (wepGivenCharacter != nullptr) {
				wepGivenCharacter->weaponCtrl.ClearWeapon();
				rewardWeapon.SetPosition(wepGivenCharacter->BasePos);
				wepGivenCharacter = Allies[i];
				rewardWeapon.visible = true;
			}

			wepGivenCharacter = Allies[i];
			rewardWeapon.MoveTo(wepGivenCharacter->BasePos);
		}

		if (wepGivenCharacter != nullptr)
			if (Utils::DistanceTo(wepGivenCharacter->BasePos, rewardWeapon.position) < 5) {
				SoundBank::Get().Play("equipWeapon");
				//If character already has a wapon
				if (wepGivenCharacter->EquippedWeapon().type != Enums::WeaponTypes::None) {
					SoundBank::Get().Play("removeWeapon");
					Weapon copy = rewardWeapon.equippedWeapon;
					rewardWeapon.Set(wepGivenCharacter->EquippedWeapon());
					wepGivenCharacter->GiveWeapon(copy);
					rewardWeapon.MoveTo(rewardWeaponFinishPos);
					wepGivenCharacter = nullptr;
				}
				//If character doest have a weapon
				else {
					wepGivenCharacter->GiveWeapon(rewardWeapon.equippedWeapon);
					rewardWeapon.visible = false;
					isClaimingWeapon = false;

					//checks if there are multiple allies with weapons, enabling rearrange weapon mode
					int count = 0;
					for (size_t i = 0; i < activeAllies().size(); i++)
					{
						if (activeAllies()[i]->HasWeapon())
							count++;
					}

					if (count >= 2) {
						isRearrangingCharWeapons = true;
					}
					return;
				}
				weaponMoved = false;
			}
			else {
				weaponMoved = false;
			}
	}

	weaponDetails.Display(&rewardWeapon, rw, true);
}

void Level::RearrangeCharacterWeapon(RenderWindow& rw)
{
	Vector2f mpos = (Vector2f)Mouse::getPosition(rw);

	for (size_t i = 0; i < Allies.size(); i++)
	{
		ToggleArrangeInd(true, 'w');
		if (Allies[i]->active == true && AllyMoverSelect == nullptr) {

			if (Utils::MouseBoundsOf(*Allies[i], rw) && MBLPress) {
				AllyMoverSelect = Allies[i];
			}
		}

		//To switch selected character with another

		if (AllyMoverSelect != nullptr && AllyMoverSelect->active) {
			ToggleArrangeInd(true, 'v');
			for (size_t i = 0; i < Allies.size(); i++)
			{
				if (Allies[i] != AllyMoverSelect) {
					if (Utils::MouseBoundsOf(*Allies[i], rw) && MBLRelease) {

						SoundBank::Get().Play("equipWeapon");

						int SelIndexCopy = AllyMoverSelect->IndexPosition;
						int SwitchIndexPosCopy = Allies[i]->IndexPosition;

						Weapon SelWeaponCopy = AllyMoverSelect->EquippedWeapon();
						Weapon SwitchWeaponCopy = Allies[i]->EquippedWeapon();

						AllyMoverSelect->GiveWeapon(SwitchWeaponCopy);
						Allies[i]->GiveWeapon(SelWeaponCopy);

						AllyMoverSelect = nullptr;
					}
				}
			}
		}

		if (AllyMoverSelect != nullptr) {
			AllyMoverSelect->ArrangeIndicator.ToggleSelected(true);
		}

		if (AllyMoverSelect == nullptr) {
			ToggleArrangeInd(true, 'v');
			for (size_t i = 0; i < Allies.size(); i++)
			{
				Allies[i]->ArrangeIndicator.ToggleSelected(false);
			}
		}
	}
}

//Resets all button locks
void Level::ResetAllLocks()
{
	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->GetType() == Enums::ButtonTypes::Audio) {
			buttons[i]->isLocked = false;
		}
		else
		buttons[i]->Unlock();
	}
}

//Retrns the level status (if the level is won or lost) based on the amount of living enemies or allies
int Level::LevelStatus()
{
	if (currentLevel == 0)
		return 0;

	if (turn != -1 && Characters[turn]->targetSet)
		return 0;

	if (globalEffectAnim.IsAnimating())
		return 0;

	int eliminatedA = 0;
	int totalA = 0;

	int totalE = 0;
	int eliminatedE = 0;

	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (Characters[i]->Affinity == 'e')
			totalE++;

		if (Characters[i]->Affinity == 'a')
			totalA++;

		if (Characters[i]->Affinity == 'e' && Characters[i]->active == false)
			eliminatedE++;

		if (Characters[i]->Affinity == 'a' && Characters[i]->active == false)
			eliminatedA++;
	}

	if (totalE == eliminatedE) {
		ToggleAllyInv();
		return 1;
	}

	if (totalA == eliminatedA) {
		ClearCharWeapons();
		return 2;
	}


	return 0;
}

//Loads a level of the given parameter
void Level::LoadLevel(int number)
{
	currentLevel = number;

	if (number % 5 == 0) {
		decor.SetBossFountain(true);

		if (SoundBank::Get().IsMuted())
			return;
		SoundBank::Get().bossSong.setLoop(true);
		SoundBank::Get().bossSong.play();
	}
	else {
		SoundBank::Get().bossSong.stop();
	}
		

	decor.Randomize();

	for (size_t i = 0; i < 5; i++)
	{
		Enemies[i]->Reset();
		Enemies[i]->active = false;
	}

	currentLevelDisplay.setString(to_string(number));

	UpdateLevelDisplay();

	if (currentLevel == 100) {
		KillAllies();
	}

	//Radomizes the possible positions for the enemies
	Utils::FillRandUnique(positions, 4, 0, 4);

	cout << "loaded level ";

	if (number != 0) {
		if (number % 4 == 0) {
			IncludeRandChar();
		}
	}

	//Level Settings
	switch (number) {
	case 1:
		cout << "1" << endl;
		//Boss needs to be loaded but not included in the first level
		Enemies[4]->Transmog(Enums::EnemyTypes::LeafLord);
		IncludeE(Enums::EnemyTypes::MiniForester);

		break;

	case 2:
		IncludeE(Enums::EnemyTypes::Forester);
		IncludeE(Enums::EnemyTypes::MiniForester);
		IncludeRandChar();

		break;

	case 3:
		IncludeE(Enums::EnemyTypes::Forester);
		IncludeE(Enums::EnemyTypes::MiniForester);
		IncludeE(Enums::EnemyTypes::MiniForester);
		GiveWeaponToEnemy(Enums::EnemyTypes::MiniForester, WeaponController().WoodClub);

		IncludeWeaponFrom(WeaponController().firstPhaseGroup, FirstPhaseGroupSize);
		break;

	case 4:
		IncludeE(Enums::EnemyTypes::MiniForester);
		IncludeE(Enums::EnemyTypes::Forester);
		IncludeE(Enums::EnemyTypes::MiniForester);
		IncludeE(Enums::EnemyTypes::Forester);
		GiveWeaponToEnemy(Enums::EnemyTypes::Forester, WeaponController().WoodStaff);
		GiveWeaponToEnemy(Enums::EnemyTypes::MiniForester, WeaponController().WoodClub);
		break;

	case 5:
		IncludeE(Enums::EnemyTypes::MiniForester);
		IncludeE(Enums::EnemyTypes::MiniForester);
		IncludeBoss(Enums::EnemyTypes::LeafLord);
		IncludeE(Enums::EnemyTypes::Forester);
		IncludeE(Enums::EnemyTypes::Forester);
		GiveWeaponToEnemy(Enums::EnemyTypes::Forester, WeaponController().WoodStaff);
		GiveWeaponToEnemy(Enums::EnemyTypes::Forester, WeaponController().WoodStaff);
		GiveWeaponToEnemy(Enums::EnemyTypes::MiniForester, WeaponController().WoodClub);

		IncludeWeaponFrom(WeaponController().firstPhaseGroup, FirstPhaseGroupSize);
		break;

	case 6:
		IncludeE(Enums::EnemyTypes::MiniOrc);
		IncludeE(Enums::EnemyTypes::MiniOrc);
		IncludeE(Enums::EnemyTypes::MediumOrc);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		break;

	case 7:
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeE(Enums::EnemyTypes::MediumOrc);
		IncludeE(Enums::EnemyTypes::MiniOrc);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeWeaponFrom(WeaponController().secondPhaseGroup, SecondPhaseGroupSize);
		break;

	case 8:
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		break;

	case 9:
		IncludeE(Enums::EnemyTypes::MediumOrc);
		IncludeE(Enums::EnemyTypes::MediumShamanOrc);
		IncludeE(Enums::EnemyTypes::MediumMaskedOrc);
		IncludeE(Enums::EnemyTypes::MediumMaskedOrc);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		GiveWeaponToEnemy(Enums::EnemyTypes::MediumShamanOrc, WeaponController().DamageStaff);
		break;

	case 10:
		IncludeBoss(Enums::EnemyTypes::OrcBoss);
		IncludeE(Enums::EnemyTypes::MediumShamanOrc);
		IncludeE(Enums::EnemyTypes::MediumShamanOrc);
		IncludeE(Enums::EnemyTypes::MediumMaskedOrc);
		IncludeE(Enums::EnemyTypes::MediumOrc);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		GiveWeaponToEnemy(Enums::EnemyTypes::OrcBoss, WeaponController().SkullMace);

		IncludeWeaponFrom(WeaponController().secondPhaseGroup, SecondPhaseGroupSize);
		break;
	}

	if (number > 10) {
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeRandomEFrom(MediumOrcGroup);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
		IncludeEnemyWeaponFrom(rewardWeapon.orcWeaponGroup, OrcWeaponGroupSize);
	}

	//Instantly sets characters' display hp and stamina to their true values, 
	//to avoid gradual increase at the beginning of level

	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (!Characters[i]->active)
			continue;

		Characters[i]->hpBar.BalanceDisplayBars(Characters[i]->HitPointsCurrent, Characters[i]->StaPointsCurrent);

	}
}

void Level::ReloadAllyPositions()
{
	for (size_t i = 0; i < Allies.size(); i++)
	{
		Ally* current;
		current = Allies[i];
		switch (current->IndexPosition) {

		case 3:
			//Ally Front Left
			current->BasePos = Vector2f(540, 640);
			current->hpBar.position = (Vector2f(545, 981 - 80 * 2));
			break;

		case 4:
			//Ally Front Right
			current->BasePos = Vector2f(780, 640);
			current->hpBar.position = (Vector2f(785, 981 - 80 * 2));
			break;

		case 1:
			//Ally Back Left
			current->BasePos = Vector2f(540, 800);
			current->hpBar.position = (Vector2f(545, 981));
			break;

		case 2:
			//Ally Back Right
			current->BasePos = Vector2f(780, 800);
			current->hpBar.position = Vector2f(785, 981);
			break;
		}

		current->SetPosition(current->BasePos);

		current->ResetEffectOverlayPos();
	}
}

void Level::ToggleAllyInv()
{
	for (size_t i = 0; i < Allies.size(); i++)
	{
		Allies[i]->hpBar.visible = false;
		Allies[i]->HitPointsCurrent = 1000;
	}
}

void Level::SelectPrimary()
{
	if (turn >= 0 && !InTransition()) {
		if (selectedMove == 2)
			SoundBank::Get().Play("selectMove");
		selectedMove = 1;
	}


}

void Level::SelectSecondary()
{
	if (turn >= 0 && !InTransition() && Characters[turn]->secondaryMove.passiveEffect == Enums::PassiveEffects::None && Characters[turn]->SecondaryCooldown == 0) {
		if (selectedMove == 1)
			SoundBank::Get().Play("selectMove");
		selectedMove = 2;
	}
}

void Level::restart()
{
	restartingLevel = true;


	WindowEffects::Get().FadeBlack();
	if (!WindowEffects::Get().IsFaded())
		return;

	decor.Randomize();
	menuOverlay.restartButton.IsToggled(false);

	for (size_t i = 0; i < Allies.size(); i++)
	{
		if (Allies[i]->IndexPosition == 3) {
			Allies[i]->active = true;
			Allies[i]->Transmog(Enums::AllyTypes::KnightM);
		}
		else
			Allies[i]->active = false;
	}
	ResetAll();
	LoadLevel(1);
}

const bool Level::NoEffectsRunning()
{
	for (size_t i = 0; i < Characters.size(); i++)
	{
		Character* current;
		current = Characters[i];
		if (!current->active)
			continue;

		if (current->effectOverlay.FinishedAnim()) {
			return false;
		}

		if (current->DeathCycleActive()) {
			return false;
		}

	}

	if (globalEffectAnim.IsAnimating())
		return false;

	return true;

}

const bool Level::weaponSecondaryTexture()
{
	if (Characters[turn]->secondaryMove.type == Enums::SecondaryMove::ForestStaffSecondary) {
		uiMoveCardSecondary->SetTexture(TextureBank::Get().ForestStaffSecondary);
		return true;
	}
	return false;

}

const vector<Enemy*> Level::activeEnemies()
{
	vector<Enemy*> actives;

	for (size_t i = 0; i < Enemies.size(); i++)
	{
		if (Enemies[i]->active)
			actives.push_back(Enemies[i]);
	}
	return actives;
}

const vector<Ally*> Level::activeAllies()
{
	vector<Ally*> actives;

	for (size_t i = 0; i < Allies.size(); i++)
	{
		if (Allies[i]->active)
			actives.push_back(Allies[i]);
	}
	return actives;
}

const vector<Character*> Level::activeCharacters(char affinityOf)
{
	vector<Character*> actives;

	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (affinityOf == 't') {
			if (Characters[i]->active)
				actives.push_back(Characters[i]);
		}

		else if (affinityOf == 'a') {
			if (Characters[i]->active && Characters[i]->Affinity == 'a')
				actives.push_back(Characters[i]);
		}

		else if (affinityOf == 'e') {
			if (Characters[i]->active && Characters[i]->Affinity == 'e')
				actives.push_back(Characters[i]);
		}

	}
	return actives;
}

//Ensures a unique character is granted
void Level::IncludeRandChar()
{
	//checks if all 4 allies are active, in which case skips.
	if (activeAllies().size() == 4) {
		return;
	}

	bool unique = false;
	RewardChar->position = rewardCharPosition;
	RewardChar->BasePos = rewardCharPosition;
	do
	{
		RewardCharacter = static_cast<Enums::AllyTypes>(rand() % 10);

		unique = true;

		for (size_t i = 0; i < Allies.size(); i++)
		{
			if (Allies[i]->type == RewardCharacter)
				unique = false;
		}

	} while (!unique);
	RewardChar->Transmog(RewardCharacter);
	toRewardChar = true;
}

void Level::IncludeRandWeapon()
{
	rewardWeapon.Set(*rewardWeapon.weapons[Utils::RandRange(0, 7)], true);

	toRewardWeapon = true;
}

void Level::IncludeWeapon(Weapon weapon)
{
	rewardWeapon.Set(weapon, true);
	toRewardWeapon = true;
}

void Level::IncludeWeaponFrom(Weapon* group[], int size)
{
	int sel = Utils::RandRange(0, size - 1);
	rewardWeapon.Set(*group[sel], true);
	toRewardWeapon = true;
}

void Level::IncludeEnemyWeaponFrom(Weapon* group[], int size)
{
	bool appliedWeapon = false;
	int sel = Utils::RandRange(0, size - 1);
	do {
		int targ = rand() % Enemies.size();
		if (Enemies[targ]->IndexPosition != -5 && Enemies[targ]->active && !Enemies[targ]->HasWeapon()) {
			Enemies[targ]->GiveWeapon(*group[sel]);
			appliedWeapon = true;
		}
	} while (appliedWeapon == false);
}

void Level::IncludeRandEnemyWeapon()
{
	bool appliedWeapon = false;

	do {
		int targ = rand() % Enemies.size();
		if (Enemies[targ]->active && !Enemies[targ]->HasWeapon()) {
			Enemies[targ]->weaponCtrl.RandomizeWeapon();
			appliedWeapon = true;
		}
	} while (appliedWeapon == false);
}

void Level::IncludeEnemyWeapon(Weapon weapon)
{
	bool appliedWeapon = false;

	do {
		int targ = rand() % Enemies.size();
		if (Enemies[targ]->active && !Enemies[targ]->HasWeapon()) {
			Enemies[targ]->GiveWeapon(weapon);
			appliedWeapon = true;
		}
	} while (appliedWeapon == false);
}

void Level::GiveWeaponToEnemy(Enums::EnemyTypes enemyType, Weapon weapon)
{
	for (size_t i = 0; i < Enemies.size(); i++)
	{
		Enemy* cur = Enemies[i];
		if (!cur->active)
			continue;

		if (cur->HasWeapon())
			continue;

		if (cur->type == enemyType) {
			cur->GiveWeapon(weapon);
			return;
		}
	}
}

void Level::SetRewardChar(Enums::AllyTypes type)
{
	RewardChar->position = rewardCharPosition;
	RewardChar->BasePos = rewardCharPosition;
	toRewardChar = true;
	RewardChar->Transmog(type);
}

//Includes an enemy of a given type to the level with a random position
void Level::IncludeE(Enums::EnemyTypes type)
{
	Enemies[positions[inclusions]]->active = true;
	Enemies[positions[inclusions]]->Transmog(type);
	inclusions++;
}

void Level::IncludeRandomEFrom(Enums::EnemyTypes enemyGroup[])
{
	Enemies[positions[inclusions]]->active = true;
	Enemies[positions[inclusions]]->Transmog(enemyGroup[rand() % 3]);
	inclusions++;
}

//Includes a boss at the center of the level
void Level::IncludeBoss(Enums::EnemyTypes type)
{
	auto pos = charPositions.find(-5);
	Enemies[4]->position = pos->second.charPos;
	Enemies[4]->active = true;
	Enemies[4]->Transmog(type);
}

void Level::NextLevel()
{

	//revives all killed allies
	if (!pdMode && charactersKilled.size() > 0) {
		for (size_t i = 0; i < charactersKilled.size(); i++)
		{
			if (charactersKilled[i]->Affinity != 'a')
				continue;

			charactersKilled[i]->Reset();
			charactersKilled[i]->hpBar.visible = false;
			SoundBank::Get().Play("revival");
		}
		charactersKilled.clear();
	}

	ApplyRewards();
	OpenDoor();

	if (InTransition()) {
		return;
	}

	//move all characters to door
	MoveAlliesDoor();

	WindowEffects::Get().FadeBlack();
	if (!WindowEffects::Get().IsFaded())
		return;

	toRewardWeapon = false;
	isClaimingWeapon = false;
	weaponMoved = false;
	toRewardChar = false;
	ToggleArrangeInd(false);
	inclusions = 0;
	AllyMoverSelect = nullptr;
	wepGivenCharacter = nullptr;
	autoPlayButton.Unlock();
	currentLevel++;
	LoadLevel(currentLevel);
	ReloadAllyPositions();
	ResetCharacters();
	weaponDetails.Reset();
	rewardWeapon.position = rewardWeaponPosition;
	CloseDoor();
}

void Level::CloseDoor()
{
	if (doorStatus == 'c')
		return;

	doorStatus = 'c';

	door->SetTexture(TextureBank::Get().Door);
	SoundBank::Get().Play("doorClose");
}

void Level::OpenDoor()
{
	if (doorStatus == 'o')
		return;

	doorStatus = 'o';

	door->SetTexture(TextureBank::Get().DoorOpen);
	SoundBank::Get().Play("doorOpen");
}

void Level::SetLevel(int level)
{
	ApplyRewards();

	if (InTransition()) {
		return;
	}

	ToggleArrangeInd(false);
	inclusions = 0;
	currentLevel = level;
	LoadLevel(level);
	ResetAllies();
}

//Manual player attack
void Level::Attack(Character& turnChar, Character* target)
{
	showTurnCircle = false;

	vector<Character*> allies;
	vector<Character*> enemies;

	for (size_t i = 0; i < Characters.size(); i++)
	{
		if (!Characters[i]->active)
			continue;

		if (Characters[i]->Affinity == 'e')
			enemies.push_back(Characters[i]);

		if (Characters[i]->Affinity == 'a')
			allies.push_back(Characters[i]);

	}

	if (turnChar.secondaryMove.globalEffect && selectedMove == 2)
	{
		turnChar.StaPointsCurrent = 0;
		globalEffectAnim.Animate(turnChar.secondaryMove);
		turnChar.Attack(target, selectedMove, allies, enemies);
		return;
	}

	turnChar.StaPointsCurrent = 0;
	turnChar.Attack(target, selectedMove, allies, enemies);
}

bool Level::InTransition() const
{
	if (WeaponClaim() || CharArranging() || WeaponArrange()) {
		return true;
	}
	return false;
}

bool Level::GetPdMode() const
{
	return pdMode;
}

bool Level::CharArranging() const
{
	return isArrangingCharacters;
}

bool Level::WeaponClaim() const
{
	return isClaimingWeapon;
}

bool Level::WeaponArrange()const
{
	return isRearrangingCharWeapons;
}

void Level::SetArrange(bool condition)
{
	isArrangingCharacters = condition;
}

bool Level::RequestReturnMenu() const
{
	return exitToMenu;
}

void Level::ToggleArrangeInd(bool condition, char group)
{
	for (size_t i = 0; i < Allies.size(); i++)
	{
		Allies[i]->ArrangeIndicator.visible = false;

		if (group == 'a')
			Allies[i]->ArrangeIndicator.visible = condition;

		if (group == 'v' && Allies[i]->visible)
			Allies[i]->ArrangeIndicator.visible = condition;

		if (group == 'w' && Allies[i]->visible && Allies[i]->HasWeapon())
			Allies[i]->ArrangeIndicator.visible = condition;
	}
}
