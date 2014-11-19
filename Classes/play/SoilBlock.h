#pragma once
#include "Block.h"

class SoilBlock :
	public Block, public DynamicCreation
{
public:
	SoilBlock(void);
	virtual ~SoilBlock(void);

	DeclareDynamicCreation(SoilBlock);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;
	virtual bool onPlayerSurround(Player* player) override;
};

