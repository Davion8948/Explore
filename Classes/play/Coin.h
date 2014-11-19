#pragma once
#include "mapobj.h"

class Coin :
	public MapObj, public DynamicCreation
{
public:
	Coin(void);
	virtual ~Coin(void);

	DeclareDynamicCreation(Coin);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player);
	virtual bool onPlayerSteping(Player* player);
	virtual bool onPlayerFinished(Player* player);

private:
	int m_coin;
};

