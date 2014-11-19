#include "TrapFire.h"
#include "GameMap.h"

ImplementDynamicCreation(TrapFire);

TrapFire::TrapFire(void)
{
}


TrapFire::~TrapFire(void)
{
}

void TrapFire::config( const cocos2d::ValueMap& cfg )
{
	MapObj::config(cfg);
	initWithFile("fire_000.png");
 	runAction( RepeatForever::create( Animate::create(fireAnimation(2)) ) );
}

bool TrapFire::willPlayerEnter( Player* player )
{
	stopAllActions();
	runAction( Sequence::create(Animate::create(fireAnimation(9)), CallFunc::create([=](){
		this->runAction( RepeatForever::create(Animate::create(this->fireAnimation(2))) );
	}), nullptr) );

	return true;
}

bool TrapFire::onPlayerSteping( Player* player )
{
	return false;
}

// bool TrapFire::onPlayerFinished( Player* player )
// {
// 	UserData::inst().addValue(UserData::udi_heart, -1);
// 
// 	return true;
// }

Animation* TrapFire::fireAnimation( int end_pos )
{
	Animation* animation = Animation::create();
	animation->setDelayPerUnit( end_pos==2 ? 1/10.0f : 1/20.0f );
	for (int i=0; i<end_pos; ++i)
	{
		animation->addSpriteFrameWithFile( sstr("fire_%03d.png", i) );
	}
	animation->addSpriteFrameWithFile( "fire_000.png" );
	return animation;
}
