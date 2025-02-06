#include "SaveFileReader.h"

SaveFileReader& SaveFileReader::Get() {
	return SaveFileReader_Instance;
}

SaveFileReader::SaveFileReader()
{
	
}

void SaveFileReader::ClearSave()
{
	ofstream ifs("Config/Continue.cmgt");

	if (ifs.is_open()) {
		for (size_t i = 0; i < 20; i++)
		{
			ifs << "";
		}
	}
}

const bool SaveFileReader::HasSave()
{
	ifstream ifs("Config/Continue.cmgt");

	string next;
	int temp = 0;

	if (ifs.is_open()) {
		ifs >> next >> temp;
	}

	if (temp >= 1) {
		return true;
	}
	else
		return false;
}

void SaveFileReader::SaveGame(int currentLevel, vector<Ally*> Allies, vector<Enemy*> Enemies, Ally* rewardChar, bool toRewardChar, bool toRewardWeapon, int difficulty)
{
	ofstream ifs("Config/Continue.cmgt");

	if (ifs.is_open()) {
		ifs << __DATE__ << endl;

		ifs << "CurrentLevel= " << currentLevel << endl;

		ifs << "Difficulty= " << difficulty << endl;

		ifs << "[active|type]" << endl;

		ifs << "[Allies]" << endl;
		for (size_t i = 0; i < Allies.size(); i++)
		{
			ifs << Allies[i]->active << " " << (int)Allies[i]->type << " " << (int)Allies[i]->IndexPosition << " " 
				<< (int)Allies[i]->EquippedWeapon().id << " " << (int)Allies[i]->WeaponStats().Attack << " " << (int)Allies[i]->WeaponStats().Health << " "
				<< (int)Allies[i]->WeaponStats().Speed << " " << (int)Allies[i]->WeaponStats().Healing << " " << (int)Allies[i]->WeaponStats().SpecialEffect << " "
				<< (int)Allies[i]->WeaponStats().SpecialEffectVal << " " << (int)Allies[i]->EquippedWeapon().weaponQuality << " " << "\n";

			if (Allies[i]->active)
				cout << i << " " << Allies[i]->IndexPosition << endl;
		}

		ifs << "[Enemies]" << endl;
		for (size_t i = 0; i < Enemies.size(); i++)
		{
			ifs << Enemies[i]->active << " " << (int)Enemies[i]->type << " " << (int)Enemies[i]->EquippedWeapon().id << "\n";
		}

		if (toRewardChar) {
			ifs << "[RewardCharacter]" << endl;
			ifs << (int)rewardChar->type << endl;
		}

		if (toRewardWeapon) {
			ifs << "[RewardWeapon]" << endl;
			ifs << 1 << endl;
		}
	}
}

void SaveFileReader::LoadGame(int& currentLevel, vector<Ally*>& Allies, vector<Enemy*>& Enemies, Enums::AllyTypes& rewardChar, bool& difficulty)
{
	ifstream ifs("Config/Continue.cmgt");

	if (ifs.fail()) {
		cout << "failed to open windowPrefs";
	}

	string next = "";
	int tempType = 0;
	int tempEffect = 0;
	WeaponController tempWeapon;

	if (ifs.is_open()) {
		ifs >> next >> next >> next;
		ifs >> next >> currentLevel;
		ifs >> next >> difficulty >> next >> next;

	/*	(int)Allies[i]->EquippedWeapon().id << " " << (int)Allies[i]->WeaponStats().Attack << " " << (int)Allies[i]->WeaponStats().Health << " "
			<< (int)Allies[i]->WeaponStats().Speed << " " << (int)Allies[i]->WeaponStats().Healing << " " << (int)Allies[i]->WeaponStats().SpecialEffect << " "
			<< (int)Allies[i]->WeaponStats().SpecialEffectVal << " " << (int)Allies[i]->EquippedWeapon().weaponQuality << " " << "\n";*/

		for (size_t i = 0; i < Allies.size(); i++)
		{
			ifs >> Allies[i]->active >> tempType >> Allies[i]->IndexPosition >> tempWeapon.equippedWeapon.id >> tempWeapon.stats().Attack >> tempWeapon.stats().Health
				>> tempWeapon.stats().Speed >> tempWeapon.stats().Healing >> tempEffect >> tempWeapon.stats().SpecialEffectVal >> tempWeapon.equippedWeapon.weaponQuality;

			Allies[i]->Transmog(static_cast<Enums::AllyTypes>(tempType));

			if (tempWeapon.equippedWeapon.id != 0) {
				tempWeapon.stats().SpecialEffect = static_cast<Enums::SpecWpnEfct>(tempEffect);
				Allies[i]->GiveWeapon(*tempWeapon.weapons[tempWeapon.equippedWeapon.id - 1]);
				Allies[i]->weaponCtrl.stats() = tempWeapon.stats();
				Allies[i]->weaponCtrl.equippedWeapon.weaponQuality = tempWeapon.equippedWeapon.weaponQuality;
			}

		}
		ifs >> next;
		for (size_t i = 0; i < Enemies.size(); i++)
		{
			ifs >> Enemies[i]->active >> tempType >> tempWeapon.equippedWeapon.id;
			Enemies[i]->Transmog(static_cast<Enums::EnemyTypes>(tempType));
			if (tempWeapon.equippedWeapon.id != 0)
				Enemies[i]->GiveWeapon(*tempWeapon.weapons[tempWeapon.equippedWeapon.id - 1]);
		}
		ifs >> next;

		//Checks to see if a reward character is present
		if (next != "[RewardCharacter]") {
			rewardChar = static_cast<Enums::AllyTypes>(-1);
			return;
		}
			
		ifs >> tempType;

		rewardChar = static_cast<Enums::AllyTypes>(tempType);

	}
}

string SaveFileReader::GetSaveDate()
{
	ifstream ifs("Config/Continue.cmgt");

	if (ifs.fail()) {
		cout << "failed to open windowPrefs";
	}

	string next;
	string m;
	string d;
	string y;

	if (ifs.is_open()) {
		ifs >> m >> d >> y;
	}
	
	return m + "/" + d + "/" + y;
}

string SaveFileReader::GetSaveLevel()
{
	ifstream ifs("Config/Continue.cmgt");

	if (ifs.fail()) {
		cout << "failed to open windowPrefs";
	}

	string next;
	string r;

	if (ifs.is_open()) {
		ifs >> next >> next >> next >> next >> r;
	}

	return "Level " + r;
}

int SaveFileReader::GetSaveDifficulty()
{
	ifstream ifs("Config/Continue.cmgt");

	if (ifs.fail()) {
		cout << "failed to open windowPrefs";
	}

	string next;
	int d = 0;

	if (ifs.is_open()) {
		ifs >> next >> next >> next >> next >> next >> next >> d;
	}

	return d;
}

SaveFileReader SaveFileReader::SaveFileReader_Instance;
