#include "Rock.h"
#include "Player.h"

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
// 	const Size size = getContentSize();
// 	setAnchorPoint(Point(0,1));
}

bool Rock::willPlayerEnter( Player* player )
{
	player->showTip("bomb.png");
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

ObjAttr Rock::getAttr()
{
	ObjAttr attr;
	attr.setUseBomb(true);
	attr.setUseMap(true);
	attr.setAStarCost(ObjAttr::AStarMax);
	return attr;
}
