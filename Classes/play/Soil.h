#pragma once
#include "MapObj.h"

class Soil :
	public MapObj,
	public DynamicCreation
{
public:
	Soil(void);
	virtual ~Soil(void);

	DeclareDynamicCreation(Soil);

	virtual void config(const cocos2d::ValueMap& cfg) override;

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;
	virtual bool onPlayerSurround(Player* player) override;

	virtual ObjAttr getAttr() override;
};

