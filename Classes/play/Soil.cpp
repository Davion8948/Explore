#include "Soil.h"
#include "Player.h"

ImplementDynamicCreation(Soil);

Soil::Soil(void)
{
}

Soil::~Soil(void)
{
}

void Soil::config( const cocos2d::ValueMap& cfg )
{
	CCAssert(cfg.find("texture")!=cfg.end(), "");
	MapObj::config(cfg);
// 	setAnchorPoint(Point(0,1));
}

bool Soil::willPlayerEnter(Player* player)
{
	Animation* amn = Animation::create();
	for(int i=1; i<7; ++i)
	{
		const char* fname = cstr("soilboom_%03d.png", i);
		amn->addSpriteFrameWithFile(fname);
	}
	amn->setDelayPerUnit(0.6f/6);
	runAction(Animate::create(amn));
// 	Sprite* sp = Sprite::create();
// 	sp->runAction(Animate::create(amn));
// 	sp->setAnchorPoint(Point(0,1));
// 	//sp->setPosition( getContentSize()/2 );
// 	addChild(sp);

	playEffect(SoilBroken);
	return true;
}

bool Soil::onPlayerSteping(Player* player)
{
	return true;
}

bool Soil::onPlayerFinished(Player* player)
{
	return false;
}

bool Soil::onPlayerSurround(Player* player)
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

	sp->runAction( autoRemoveAction(sp, Animate::create(amn)) );
	getParent()->addChild(sp);
	
	playEffect(SoilBroken);
	return false;
}

ObjAttr Soil::getAttr()
{
	ObjAttr attr;
	attr.setUseHoe(true);
	attr.setUseBomb(true);
	attr.setUseMap(true);
	attr.setUseFlag(true);
	return attr;
}
