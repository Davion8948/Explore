#pragma once
#include "MapObj.h"

class SoilBlock :
	public MapObj, public DynamicCreation
{
public:
	SoilBlock(void);
	virtual ~SoilBlock(void);

	DeclareDynamicCreation(SoilBlock);

	virtual void config(const cocos2d::ValueMap& cfg) override;

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;
	virtual bool onPlayerSurround(Player* player) override;

	virtual bool canUseHoe() override;
	virtual bool canUseBomb() override;
	virtual bool canUseMap() override;
	virtual bool canUseFlag() override;

	virtual bool canAStar() override;
};

