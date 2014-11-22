#include "Monster.h"
#include "GameMap.h"
#include "UDWhenPlay.h"
#include "LevelData.h"

ImplementDynamicCreation(Monster);

Monster::Monster(void)
{
}


Monster::~Monster(void)
{
}

void Monster::config( const cocos2d::ValueMap& cfg )
{
	MapObj::config(cfg);
}

bool Monster::willPlayerEnter( Player* player )
{
	int x = UDWhenPlay::inst().getValue(udi_t::udi_arrow);
	Return_False_If(x==0);

	return true;
}

bool Monster::onPlayerSteping( Player* player )
{
	return true;
}

bool Monster::onPlayerFinished( Player* player )
{
	int x = UDWhenPlay::inst().getValue(udi_t::udi_arrow);
	Return_True_If(x==0);
	UDWhenPlay::inst().setValue(udi_t::udi_arrow, x-1);
	LevelData::inst().addKilledMonster(1);
	return false;
}

bool Monster::canAStar()
{
	return UDWhenPlay::inst().getValue(udi_t::udi_arrow)!=0;
}
