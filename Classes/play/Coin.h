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

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
	virtual bool onPlayerFinished(Player* player) override;

private:
	int m_coin;
};

