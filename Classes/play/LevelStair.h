#pragma once
#include "MapObj.h"

class LevelStair :
	public MapObj, public DynamicCreation
{
public:
	LevelStair(void);
	virtual ~LevelStair(void);

	DeclareDynamicCreation(LevelStair);

	virtual void config(const cocos2d::ValueMap& cfg) override;

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;
	virtual bool onPlayerSurround(Player* player) override;
};

