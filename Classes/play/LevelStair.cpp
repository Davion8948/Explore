#include "LevelStair.h"
#include "Player.h"
#include "GameState.h"
#include "MainLayer.h"
ImplementDynamicCreation(LevelStair);


LevelStair::LevelStair(void)
{
}

LevelStair::~LevelStair(void)
{
}

void LevelStair::config( const cocos2d::ValueMap& cfg )
{
	initWithFile("level_stair.png");
	MapObj::config(cfg);
}

bool LevelStair::willPlayerEnter(Player* player)
{
	return true;
}

bool LevelStair::onPlayerSteping(Player* player)
{
	return true;
}

bool LevelStair::onPlayerFinished(Player* player)
{
	if (GameStateMgr::inst().curState() != gs_win)
	{
		GameStateMgr::inst().change(GameState::gs_win);
	}
	return true;
}

bool LevelStair::onPlayerSurround(Player* player)
{	
	return true;
}
