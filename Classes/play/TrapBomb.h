#pragma once
#include "Trap.h"

class TrapBomb :
	public Trap, public DynamicCreation
{
public:
	TrapBomb(void);
	virtual ~TrapBomb(void);

	DeclareDynamicCreation(TrapBomb);

	virtual void config(const cocos2d::ValueMap& cfg) override;

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;

private:
};

