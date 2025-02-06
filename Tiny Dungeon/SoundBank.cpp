#include "SoundBank.h"

SoundBank& SoundBank::Get()
{
	static SoundBank sb;
	return sb;
}

void SoundBank::Mute()
{
	if (mute)
		return;
	mute = true;

	for (size_t i = 0; i < MaxSounds; i++)
	{
		if (activeSounds[i]->getStatus() == Sound::Status::Playing) {
			activeSounds[i]->setVolume(0);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		songs[i]->setVolume(0);
	}

}

void SoundBank::Unmute()
{
	if (!mute)
		return;
	mute = false;
	for (size_t i = 0; i < MaxSounds; i++)
	{
		activeSounds[i]->setVolume(100);	
	}

	for (int i = 0; i < 3; i++)
	{
		songs[i]->setVolume(100);
	}
}

bool SoundBank::IsMuted() const
{
	return mute;
}

void SoundBank::Play(const string& sound)
{
	if (mute) {
		return;
	}

	for (size_t i = 0; i < MaxSounds; i++)
	{
		if (activeSounds[i]->getStatus() == Sound::Status::Stopped) {
			auto pos = sounds.find(sound);
			if (pos != sounds.end())
			{
				activeSounds[i]->setBuffer(pos->second);
				activeSounds[i]->play();
			}
			return;
		}
	}
}

void SoundBank::StopSongs()
{
	for (int i = 0; i < 3; i++)
	{
		songs[i]->stop();
	}
}

SoundBank::SoundBank()
{
	activeSounds.reserve(MaxSounds);
	for (int i = 0; i < MaxSounds; ++i)
		activeSounds.push_back(new Sound());

	openMenu.loadFromFile("Assets/Sounds/UiSounds/MenuOpen.wav");
	exitMenu.loadFromFile("Assets/Sounds/UiSounds/ExitMenu.wav");
	selectSound.loadFromFile("Assets/Sounds/UiSounds/Bump2.wav");
	selectMove.loadFromFile("Assets/Sounds/UiSounds/SelectMove.wav");
	hover.loadFromFile("Assets/Sounds/UiSounds/hover.wav");
	selectCharacter.loadFromFile("Assets/Sounds/UiSounds/select.wav");
	sounds.emplace("openMenu", openMenu);
	sounds.emplace("closeMenu", exitMenu);
	sounds.emplace("hover", hover);
	sounds.emplace("selectCharacter", selectCharacter);
	sounds.emplace("selectMove", selectMove);
	sounds.emplace("selectSound", selectSound);

	equipWeapon.loadFromFile("Assets/Sounds/Misc/equipWeapon.wav");
	recieveReward.loadFromFile("Assets/Sounds/Misc/recieveReward.wav");
	removeWeapon.loadFromFile("Assets/Sounds/Misc/removeWeapon.wav");
	sounds.emplace("equipWeapon", equipWeapon);
	sounds.emplace("recieveReward", recieveReward);
	sounds.emplace("removeWeapon", removeWeapon);

	menuMusic.openFromFile("Assets/Sounds/songs/menuMusic.wav");
	deathMusic.openFromFile("Assets/Sounds/songs/deathSong.wav");	
	bossSong.openFromFile("Assets/Sounds/songs/bossSong.wav");

	songs[0] = &menuMusic;
	songs[1] = &deathMusic;
	songs[2] = &bossSong;

	bell.loadFromFile("Assets/Sounds/bell.wav");
	sounds.emplace("bellRing", bell);

	humanHit1.loadFromFile("Assets/Sounds/Human/humanHit1.wav");
	humanHit2.loadFromFile("Assets/Sounds/Human/humanHit2.wav");
	humanHit3.loadFromFile("Assets/Sounds/Human/humanHit3.wav");
	sounds.emplace("humanHit1", humanHit1);
	sounds.emplace("humanHit2", humanHit2);
	sounds.emplace("humanHit3", humanHit3);

	centaurHit.loadFromFile("Assets/Sounds/Centaur/CentaurHit.wav");
	sounds.emplace("centaurHit1", centaurHit);

	centaurSecondary.loadFromFile("Assets/Sounds/Centaur/Secondary.wav");
	sounds.emplace("centaurSecondary", centaurSecondary);

	centaurAttack.loadFromFile("Assets/Sounds/Centaur/CentaurAttack.wav");
	sounds.emplace("centaurAttack1", centaurAttack);

	orcHit1.loadFromFile("Assets/Sounds/Orc/orcHit1.wav");
	orcHit2.loadFromFile("Assets/Sounds/Orc/orcHit2.wav");
	orcHit3.loadFromFile("Assets/Sounds/Orc/orcHit2.wav");
	sounds.emplace("orcHit1", orcHit1);
	sounds.emplace("orcHit2", orcHit2);
	sounds.emplace("orcHit3", orcHit3);

	orcAttack1.loadFromFile("Assets/Sounds/Orc/orcAttack1.wav");
	orcAttack2.loadFromFile("Assets/Sounds/Orc/orcAttack2.wav");
	sounds.emplace("orcAttack1", orcAttack1);
	sounds.emplace("orcAttack2", orcAttack2);

	orcBattleCry.loadFromFile("Assets/Sounds/Orc/orcCry.wav");
	shamanCircle.loadFromFile("Assets/Sounds/Orc/shamanCircle.wav");
	shamanPrimaryTarget.loadFromFile("Assets/Sounds/Orc/ShamanTargetEnemy.wav");
	sounds.emplace("shamanTarget", shamanPrimaryTarget);
	sounds.emplace("shamanCircle", shamanCircle);
	sounds.emplace("orcBattleCry", orcBattleCry);

	orcBossAttack1.loadFromFile("Assets/Sounds/Orc/orcBossAttack1.wav");
	orcBossAttack2.loadFromFile("Assets/Sounds/Orc/orcBossAttack2.wav");
	sounds.emplace("orcBossAttack1", orcBossAttack1);
	sounds.emplace("orcBossAttack2", orcBossAttack2);

	orcBossHit1.loadFromFile("Assets/Sounds/Orc/orcBossHit1.wav");
	orcBossHit2.loadFromFile("Assets/Sounds/Orc/orcBossHit2.wav");
	sounds.emplace("orcBossHit1", orcBossHit1);
	sounds.emplace("orcBossHit2", orcBossHit2);

	orcBossSecondary.loadFromFile("Assets/Sounds/Orc/OrcBossSecondary.wav");
	sounds.emplace("orcBossSecondary", orcBossSecondary);

	foresterHit1.loadFromFile("Assets/Sounds/Hit/Forester/03_Small_Humanoid_Damage_1.wav");
	foresterHit2.loadFromFile("Assets/Sounds/Hit/Forester/04_Small_Humanoid_Damage_2.wav");
	sounds.emplace("foresterHit1", foresterHit1);
	sounds.emplace("foresterHit2", foresterHit2);

	foresterBossHit1.loadFromFile("Assets/Sounds/ForesterBoss/Hit1.wav");
	foresterBossHit2.loadFromFile("Assets/Sounds/ForesterBoss/Hit2.wav");
	sounds.emplace("foresterBossHit1", foresterBossHit1);
	sounds.emplace("foresterBossHit2", foresterBossHit2);

	foresterBossAttack1.loadFromFile("Assets/Sounds/ForesterBoss/Attack1.wav");
	foresterBossAttack2.loadFromFile("Assets/Sounds/ForesterBoss/Attack2.wav");
	sounds.emplace("foresterBossAttack1", foresterBossAttack1);
	sounds.emplace("foresterBossAttack2", foresterBossAttack2);

	heal.loadFromFile("Assets/Sounds/Buffs/Heal.wav");
	sounds.emplace("heal", heal);

	arrowFire.loadFromFile("Assets/Sounds/Elf/Bow_Release.wav");
	sounds.emplace("arrowFire", arrowFire);

	arrowVolley.loadFromFile("Assets/Sounds/Elf/Volley.wav");
	sounds.emplace("arrowVolley", arrowVolley);

	blueMageHealMove.loadFromFile("Assets/Sounds/magic/bluemage/BlueMageHeal.wav");
	blueMageCast.loadFromFile("Assets/Sounds/magic/bluemage/cast.wav");
	blueMageHit.loadFromFile("Assets/Sounds/magic/bluemage/hit.wav");
	sounds.emplace("blueMageHealMove", blueMageHealMove);
	sounds.emplace("blueMageCast", blueMageCast);
	sounds.emplace("blueMageHit", blueMageHit);

	foresterCast.loadFromFile("Assets/Sounds/magic/forester/cast.wav");
	foresterCastHit.loadFromFile("Assets/Sounds/magic/forester/hit.wav");
	sounds.emplace("foresterCast", foresterCast);
	sounds.emplace("foresterCastHit", foresterCastHit);

	forestStaffMove.loadFromFile("Assets/Sounds/moves/ForestStaff.wav");
	sounds.emplace("forestStaffMove", forestStaffMove);


	genericMove.loadFromFile("Assets/Sounds/moves/GenericMove.wav");
	sounds.emplace("genericMove", genericMove);


	foresterBossSecondary.loadFromFile("Assets/Sounds/ForesterBoss/ForesterBossSecond.wav");
	sounds.emplace("foresterBossSecondary", foresterBossSecondary);

	revival.loadFromFile("Assets/Sounds/revival.wav");
	sounds.emplace("revival", revival);

	doorOpen.loadFromFile("Assets/Sounds/Misc/doorOpen.wav");
	sounds.emplace("doorOpen", doorOpen);

	doorClose.loadFromFile("Assets/Sounds/Misc/doorClose.wav");
	sounds.emplace("doorClose", doorClose);

	//buffs
	shield.loadFromFile("Assets/Sounds/Buffs/shield.wav");
	breakShield.loadFromFile("Assets/Sounds/Buffs/BreakShield.wav");
	attack.loadFromFile("Assets/Sounds/Buffs/Attack.wav");
	breakAttack.loadFromFile("Assets/Sounds/Buffs/BreakAttack.wav");
	poison.loadFromFile("Assets/Sounds/Buffs/Poison.wav");
	preventHeal.loadFromFile("Assets/Sounds/Buffs/PreventHeal.wav");
	speed.loadFromFile("Assets/Sounds/Buffs/Speed.wav");
	slow.loadFromFile("Assets/Sounds/Buffs/Slow.wav");
	stun.loadFromFile("Assets/Sounds/Buffs/Stun.wav");
	reuduceStam.loadFromFile("Assets/Sounds/Buffs/ReduceStam.wav");
	removeBeneficial.loadFromFile("Assets/Sounds/Buffs/RemoveBeneficial.wav");

	sounds.emplace("shield", shield);
	sounds.emplace("breakShield", breakShield);
	sounds.emplace("attack", attack);
	sounds.emplace("breakAttack", breakAttack);
	sounds.emplace("poison", poison);
	sounds.emplace("preventHeal", preventHeal);
	sounds.emplace("speed", speed);
	sounds.emplace("slow", slow);
	sounds.emplace("stun", stun);
	sounds.emplace("reuduceStam", reuduceStam);
	sounds.emplace("removeBeneficial", removeBeneficial);


	cout << "loaded sounds" << endl;

}
