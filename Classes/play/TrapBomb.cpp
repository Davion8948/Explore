#include "TrapBomb.h"
#include "GameMap.h"

ImplementDynamicCreation(TrapBomb);

TrapBomb::TrapBomb(void)
{
}


TrapBomb::~TrapBomb(void)
{
}

void TrapBomb::config( const cocos2d::ValueMap& cfg )
{
	initWithFile("eb_00.png");
	Trap::config(cfg);
}

bool TrapBomb::willPlayerEnter( Player* player )
{
	return true;
}

bool TrapBomb::onPlayerSteping( Player* player )
{
	Animation* ani = Animation::create();
	for (int i=1; i<10; ++i)
	{
		string name = sstr("eb_%02d.png", i);
		ani->addSpriteFrameWithFile( name );
	}
	ani->setDelayPerUnit(0.1f);
	auto reset = [=](){
		this->initWithFile("eb_00.png");
	};
	this->runAction( Sequence::create(Animate::create(ani),CallFunc::create(reset),nullptr) );

	playEffect(TrapExp);
	return false;
}
