#pragma once
#include "Block.h"

class Rock :
	public Block, public DynamicCreation
{
public:
	Rock(void);
	virtual ~Rock(void);

	DeclareDynamicCreation(Rock);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player);
	virtual bool onPlayerSteping(Player* player);
	virtual bool onPlayerFinished(Player* player);
};

