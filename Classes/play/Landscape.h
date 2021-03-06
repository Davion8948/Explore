#pragma once

#include "MapObj.h"

class Landscape
	: public MapObj
	, public DynamicCreation
{
public:
	Landscape(void);
	virtual ~Landscape(void);

	DeclareDynamicCreation(Landscape);

	virtual void config(const cocos2d::ValueMap& cfg) override;

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;
	virtual bool onPlayerSurround(Player* player) override;
};

