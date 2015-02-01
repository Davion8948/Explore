#include "Landscape.h"
#include "Player.h"

ImplementDynamicCreation(Landscape);

Landscape::Landscape(void)
{
}

Landscape::~Landscape(void)
{
}

void Landscape::config( const cocos2d::ValueMap& cfg )
{
	MapObj::config(cfg);
// 	string animation;
// 	safe_assign(animation, cfg, "animation");
// 	if (!animation.empty())
// 	{
// 		Animation* ani = AnimationCache::getInstance()->getAnimation(animation);
// 		runAction( RepeatForever::create(Animate::create(ani)) );
// 	}
}

bool Landscape::willPlayerEnter(Player* player)
{
	player->showTip("unknown.png");
	return false;
}

bool Landscape::onPlayerSteping(Player* player)
{
	return false;
}

bool Landscape::onPlayerFinished(Player* player)
{
	return true;
}

bool Landscape::onPlayerSurround(Player* player)
{
	return true;
}
