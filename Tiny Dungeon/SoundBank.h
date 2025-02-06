#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <unordered_map>
using namespace std;
using namespace sf;

//the maximum amount of sounds that may be played at once
constexpr auto MaxSounds = 10;

class SoundBank
{
private:
	bool mute = false;
	SoundBank();

public:
	static SoundBank& Get();

	void Mute();
	void Unmute();
	bool IsMuted() const;
	void Play(const string& sound);
	void StopSongs();

	vector<Sound*> activeSounds;

	Music* songs[3];

	unordered_map<string, SoundBuffer> sounds;

	Music menuMusic;
	Music deathMusic;
	Music bossSong;

	SoundBuffer openMenu;
	SoundBuffer exitMenu;
	SoundBuffer selectSound;
	SoundBuffer selectMove;
	SoundBuffer hover;
	SoundBuffer selectCharacter;
	SoundBuffer startGame;

	SoundBuffer removeWeapon;
	SoundBuffer equipWeapon;
	SoundBuffer recieveReward;

	int humanHits = 3;
	SoundBuffer humanHit1;
	SoundBuffer humanHit2;
	SoundBuffer humanHit3;

	int centaurHits = 1;
	SoundBuffer centaurHit;

	int centaurAttacks = 1;
	SoundBuffer centaurAttack;

	SoundBuffer centaurSecondary;

	int dashes = 2;
	SoundBuffer dash[2];

	int foresterHits = 2;
	SoundBuffer foresterHit1;
	SoundBuffer foresterHit2;

	int foresterBossHits = 2;
	SoundBuffer foresterBossHit1;
	SoundBuffer foresterBossHit2;

	int foresterBossAttacks = 2;
	SoundBuffer foresterBossAttack1;
	SoundBuffer foresterBossAttack2;

	SoundBuffer foresterBossSecondary;

	int orcHits = 3;
	SoundBuffer orcHit1;
	SoundBuffer orcHit2;
	SoundBuffer orcHit3;

	int orcAttacks = 2;
	SoundBuffer orcAttack1;
	SoundBuffer orcAttack2;

	int orcBossAttacks = 2;
	int orcBossHits = 2;

	SoundBuffer orcBossSecondary;
	SoundBuffer orcBossAttack1;
	SoundBuffer orcBossAttack2;
	SoundBuffer orcBossHit1;
	SoundBuffer orcBossHit2;

	SoundBuffer orcBattleCry;
	SoundBuffer shamanCircle;
	SoundBuffer shamanPrimaryTarget;

	SoundBuffer arrowFire;
	SoundBuffer arrowVolley;

	SoundBuffer blueMageHealMove;
	SoundBuffer blueMageCast;
	SoundBuffer blueMageHit;

	SoundBuffer foresterCast;
	SoundBuffer foresterCastHit;

	SoundBuffer forestStaffMove;

	SoundBuffer heal;
	SoundBuffer revival;

	SoundBuffer genericMove;

	SoundBuffer doorOpen;
	SoundBuffer doorClose;

	//Buffs
	SoundBuffer stun;
	SoundBuffer shield;
	SoundBuffer breakShield;
	SoundBuffer attack;
	SoundBuffer breakAttack;
	SoundBuffer poison;
	SoundBuffer preventHeal;
	SoundBuffer speed;
	SoundBuffer slow;
	SoundBuffer reuduceStam;
	SoundBuffer removeBeneficial;

	//Sound
	SoundBuffer bell;
};

