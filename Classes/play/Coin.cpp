#include "Coin.h"
#include "GameMap.h"
#include "UDWhenPlay.h"
#include "LevelData.h"
#include "SoundMgr.h"

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
	initWithFile( cstr("coin%d.png", coin) );
	MapObj::config(cfg);
}

bool Coin::willPlayerEnter( Player* player )
{
// 	switch (m_coin)
// 	{
// 	case 10:
// 		playEffect(PickupGold0);
// 		break;
// 	case 50:
// 	case 100:
// 		playEffect(PickupGold1);//¨¬?¡ä¨¬?¨²
// 		break;
// 	}
	playEffect(PickupGold0);
	return true;
}

bool Coin::onPlayerSteping( Player* player )
{
	Label* text = Label::createWithTTF( sstr("+%d",m_coin), "fonts/Marker Felt.ttf", 32);
	text->setColor(Color3B(255,215,64));
	text->setPosition(getPosition());
	text->runAction( Sequence::create(MoveBy::create(2, Vec2(0, 64)), CCCallFunc::create(std::bind(&CCNode::removeFromParent, text)), 0) );
	text->setLocalZOrder(player->getLocalZOrder());
	getParentCell()->playTopEffect(text);
	return true;
}

bool Coin::onPlayerFinished( Player* player )
{
	UDWhenPlay::inst().addValue(udi_t::udi_coin, m_coin);
	LevelData::inst().addCollectedCoin(m_coin);
	return false;
}

