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
	if (x==0)
	{
		player->showTip("key.png");
		return false;
	}
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

ObjAttr LockedDoor::getAttr()
{
	ObjAttr attr;
	attr.setAStarCost( UDWhenPlay::inst().getValue(udi_t::udi_key)!=0 ? ObjAttr::AStarMin : ObjAttr::AStarMax );
	return attr;
}
