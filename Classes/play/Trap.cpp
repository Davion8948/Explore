#include "Trap.h"
#include "UserData.h"
#include "GameState.h"

Trap::Trap(void)
{
}


Trap::~Trap(void)
{
}

bool Trap::onPlayerFinished( Player* player )
{
	int x = 0;

	x = UserData::inst().getValue(UserData::udi_shield);
	if (x > 0)
	{
		UserData::inst().addValue(UserData::udi_shield, -1);
	}
	else
	{
		x = UserData::inst().getValue(UserData::udi_heart);
		UserData::inst().addValue(UserData::udi_heart, -1);
		if (x == 1)
		{
			GameStateMgr::inst().change(gs_dead);
		}
	}
	return true;
}
