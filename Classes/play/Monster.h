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

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;

	virtual ObjAttr getAttr() override;
private:
};

