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

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;

	virtual ObjAttr getAttr() override;
private:
};

