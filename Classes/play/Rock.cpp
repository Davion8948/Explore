#include "Rock.h"

ImplementDynamicCreation(Rock);

Rock::Rock(void)
{
}


Rock::~Rock(void)
{
}

void Rock::config( const cocos2d::ValueMap& cfg )
{
	initWithFile("rock.png");
	MapObj::config(cfg);
}

bool Rock::willPlayerEnter( Player* player )
{
	return false;
}

bool Rock::onPlayerSteping( Player* player )
{
	return false;
}

bool Rock::onPlayerFinished( Player* player )
{
	return true;
}

bool Rock::canUseBomb()
{
	return true;
}
