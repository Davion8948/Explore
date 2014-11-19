#include "LockedDoor.h"
#include "GameMap.h"
#include "UserData.h"

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
	int x = UserData::inst().getValue(UserData::udi_key);	
	Return_False_If(x==0);
	return true;
}

bool LockedDoor::onPlayerSteping( Player* player )
{
	return true;
}

bool LockedDoor::onPlayerFinished( Player* player )
{
	int x = UserData::inst().getValue(UserData::udi_key);
	Return_True_If(x==0);
	UserData::inst().setValue(UserData::udi_key, x-1);
	return false;
}
