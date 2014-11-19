#pragma once
#include "mapobj.h"

class LockedDoor :
	public MapObj, public DynamicCreation
{
public:
	LockedDoor(void);
	virtual ~LockedDoor(void);

	DeclareDynamicCreation(LockedDoor);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player);
	virtual bool onPlayerSteping(Player* player);
	virtual bool onPlayerFinished(Player* player);

private:
};

