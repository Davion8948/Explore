#include "Monster.h"
#include "GameMap.h"
#include "UserData.h"

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
	int x = UserData::inst().getValue(UserData::udi_arrow);
	Return_False_If(x==0);

	return true;
}

bool Monster::onPlayerSteping( Player* player )
{
	return true;
}

bool Monster::onPlayerFinished( Player* player )
{
	int x = UserData::inst().getValue(UserData::udi_arrow);
	Return_True_If(x==0);
	UserData::inst().setValue(UserData::udi_arrow, x-1);
	return false;
}
