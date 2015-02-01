#pragma once
#include "MapObj.h"

class Rock :
	public MapObj,
	public DynamicCreation
{
public:
	Rock(void);
	virtual ~Rock(void);

	DeclareDynamicCreation(Rock);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;

	virtual ObjAttr getAttr() override;
};

