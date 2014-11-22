#include "SoilBlock.h"
#include "Player.h"

ImplementDynamicCreation(SoilBlock);

SoilBlock::SoilBlock(void)
{
}

SoilBlock::~SoilBlock(void)
{
}

void SoilBlock::config( const cocos2d::ValueMap& cfg )
{
	MapObj::config(cfg);
}

bool SoilBlock::willPlayerEnter(Player* player)
{
	Animation* amn = Animation::create();
	for(int i=1; i<7; ++i)
	{
		const char* fname = cstr("soilboom_%03d.png", i);
		amn->addSpriteFrameWithFile(fname);
	}
	amn->setDelayPerUnit(0.6f/6);
	runAction(Animate::create(amn));
	return true;
}

bool SoilBlock::onPlayerSteping(Player* player)
{
	return true;
}

bool SoilBlock::onPlayerFinished(Player* player)
{
	return false;
}

bool SoilBlock::onPlayerSurround(Player* player)
{
	Animation* amn = Animation::create();
	for(int i=1; i<7; ++i)
	{
		const char* fname = cstr("soilboom_%03d.png", i);
		amn->addSpriteFrameWithFile(fname);
	}
	amn->setDelayPerUnit(0.6f/6);

	Sprite* sp = Sprite::create();
	sp->setPosition(getPosition());

	auto auto_remove = [=](){ sp->removeFromParent(); };

	sp->runAction(Sequence::create(Animate::create(amn), CallFunc::create(auto_remove), nullptr));
	getParent()->addChild(sp);
	
	return false;
}

bool SoilBlock::canUseHoe()
{
	return true;
}

bool SoilBlock::canUseBomb()
{
	return true;
}

bool SoilBlock::canUseMap()
{
	return true;
}

bool SoilBlock::canUseFlag()
{
	return true;
}

bool SoilBlock::canAStar()
{
	return true;
}
