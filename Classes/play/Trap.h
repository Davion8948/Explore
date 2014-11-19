#pragma once
#include "mapobj.h"

class Trap :
	public MapObj
{
public:
	Trap(void);
	virtual ~Trap(void) = 0;

	virtual bool onPlayerFinished(Player* player) override;
};

