#include "Coin.h"
#include "GameMap.h"
#include "UDWhenPlay.h"
#include "LevelData.h"

ImplementDynamicCreation(Coin);

Coin::Coin(void)
	:m_coin(0)
{
}


Coin::~Coin(void)
{
}

void Coin::config( const cocos2d::ValueMap& cfg )
{
	int coin = cfg.at("coin").asInt();
	m_coin = coin;
	if (coin == 10)
	{
		initWithFile("coin1.png");
	}
	else if (coin == 100)
	{
		initWithFile("coin2.png");
	}
	MapObj::config(cfg);
}

bool Coin::willPlayerEnter( Player* player )
{
	return true;
}

bool Coin::onPlayerSteping( Player* player )
{
	Label* text = Label::createWithTTF( sstr("+%d",m_coin), "fonts/Marker Felt.ttf", 32);
	text->setPosition(getPosition());
	text->runAction( Sequence::create(MoveBy::create(2, Vec2(0, 64)), CCCallFunc::create(std::bind(&CCNode::removeFromParent, text)), 0) );
	getParent()->addChild(text);
	return true;
}

bool Coin::onPlayerFinished( Player* player )
{
	UDWhenPlay::inst().addValue(udi_t::udi_coin, m_coin);
	LevelData::inst().addCollectedCoin(m_coin);
	return false;
}

bool Coin::canAStar()
{
	return true;
}
