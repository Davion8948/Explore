#pragma once
#include "Trap.h"

class TrapFire :
	public Trap, public DynamicCreation
{
public:
	TrapFire(void);
	virtual ~TrapFire(void);

	DeclareDynamicCreation(TrapFire);

	virtual void config(const cocos2d::ValueMap& cfg);

	virtual bool willPlayerEnter(Player* player) override;
	virtual bool onPlayerSteping(Player* player) override;
// 	virtual bool onPlayerFinished(Player* player) override;
// 	virtual void onPlayerSurround() override;
private:
	Animation* fireAnimation(int end_pos);

};

