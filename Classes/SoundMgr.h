#pragma once

void playEffect( const char* name );
void setEffectsVolume(int volume);
int getEffectsVolume();
void setBackgroundMusicVolume(int volume);
int getBackgroundMusicVolume();
static const char* PickupHeart = "sound/pickup_heart.wav";
static const char* PickupShield = "sound/pickup_shield.wav";
static const char* PickupKey = "sound/pickup_key.wav";
static const char* PickupArrow = "sound/pickup_arrow.wav";
static const char* PickupHoe = "sound/pickup_hoe.wav";
static const char* PickupBomb = "sound/pickup_bomb.wav";
static const char* PickupMap = "sound/pickup_map.wav";
static const char* PickupGold0 = "sound/pickup_many_gold5.wav";
static const char* PickupGold1 = "sound/pickup_many_gold9.wav";

static const char* SoilBroken = "sound/soil_broken.wav";
static const char* SettingFlag = "sound/setting_flag.wav";
static const char* RemoveFlag = "sound/removing_flag.wav";
static const char* MonsterDeath = "sound/monster_death.wav";

static const char* TrapBurn = "sound/trap_fire.wav";
static const char* TrapExp = "sound/trap_bomb.wav";

static const char* UseHoe = "sound/use_hoe.wav";
static const char* UseBomb = "sound/use_bomb.wav";
static const char* UseMap = "sound/use_map.wav";

static const char* Confused = "sound/confused.wav";

static const char* PlayBack = "sound/play_back.mp3";
static const char* PlayerWin = "sound/player_win.wav";
static const char* PlayerLose = "sound/player_lose.wav";
static const char* LevelWin = "sound/level_win.wav";
static const char* LevelLose = "sound/level_lose.wav";
static const char* PlayerSteps = "sound/hero_steps.wav";

static const char* ClickButton = "sound/click_button.wav";
static const char* ClickError = "sound/click_error.wav";
