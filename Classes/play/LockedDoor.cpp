#include "LockedDoor.h"
#include "GameMap.h"
#include "UDWhenPlay.h"
#include "LevelData.h"

ImplementDynamicCreation(LockedDoor);

LockedDoor::LockedDoor(void)
{
}


LockedDoor::~LockedDoor(void)
{
}

void LockedDoor::config( const cocos2d::ValueMap& cfg )
{
	initWithFile("locked.png");
	MapObj::config(cfg);
}

bool LockedDoor::willPlayerEnter( Player* player )
{
	int x = UDWhenPlay::inst().getValue(udi_t::udi_key);	
	Return_False_If(x==0);
	return true;
}

bool LockedDoor::onPlayerSteping( Player* player )
{
	return true;
}

bool LockedDoor::onPlayerFinished( Player* player )
{
	int x = UDWhenPlay::inst().getValue(udi_t::udi_key);
	Return_True_If(x==0);
	UDWhenPlay::inst().setValue(udi_t::udi_key, x-1);
	LevelData::inst().addOpenedDoor(1);
	return false;
}

bool LockedDoor::canAStar()
{
	return UDWhenPlay::inst().getValue(udi_t::udi_key)!=0;
}
