#pragma once
#include "mapobj.h"

class Monster :
	public MapObj, public DynamicCreation
{
public:
	Monster(void);
	virtual ~Monster(void);

	DeclareDynamicCreation(Monster);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player);
	virtual bool onPlayerSteping(Player* player);
	virtual bool onPlayerFinished(Player* player);

private:
};

