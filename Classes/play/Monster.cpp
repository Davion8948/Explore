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
	if (x == 0)
	{
		player->showTip("arrow.png");
		return false;
	}
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

	playEffect(MonsterDeath);
	UDWhenPlay::inst().setValue(udi_t::udi_arrow, x-1);
	LevelData::inst().addKilledMonster(1);
	return false;
}

ObjAttr Monster::getAttr()
{
	ObjAttr attr;
	attr.setAStarCost( UDWhenPlay::inst().getValue(udi_t::udi_arrow)!=0 ? ObjAttr::AStarMin : ObjAttr::AStarMax );
	return attr;
}
