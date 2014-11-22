#include "Trap.h"
#include "UDWhenPlay.h"
#include "LevelData.h"
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

	x = UDWhenPlay::inst().getValue(udi_t::udi_shield);
	if (x > 0)
	{
		UDWhenPlay::inst().addValue(udi_t::udi_shield, -1);
	}
	else
	{
		x = UDWhenPlay::inst().getValue(udi_t::udi_heart);
		UDWhenPlay::inst().addValue(udi_t::udi_heart, -1);
		if (x == 1)
		{
			GameStateMgr::inst().change(gs_dead);
		}
	}
	return true;
}

bool Trap::canUseFlag()
{
	return true;
}
