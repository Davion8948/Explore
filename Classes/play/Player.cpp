#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

bool Player::init()
{	
	initWithPlayerName("mpl");
//	setScale(0.5f);
	return true;
}

void Player::initWithPlayerName( const string& name )
{
	m_player = name;
	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile(name+".plist");
	assert(initWithSpriteFrameName(name+"00.png"));
	CCAnimationCache::getInstance()->addAnimationsWithFile(name+".action");
 	setAnchorPoint(Point(0.5f,0.2f));
}

void Player::stepTo(const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish )
{
	Point cur = this->getPosition();
	int dir = cur.x==dst.x ? (cur.y<dst.y?0:2) : (cur.x<dst.x?1:3);

	bool can = cell->checkPlayerEnter(this);

	if (!can)
	{
		setSpriteFrame( sstr("%s%d0.png", m_player.c_str(), dir) );
		whenFinish(msCanotMove);
	}
	else
	{
		auto callMid = bind( &Player::stepMid, this, dst, cell, whenFinish);
		this->runAction( Sequence::create( MoveBy::create(0.1f, (dst-cur)/2), CallFunc::create(callMid), nullptr ) );

		this->runAction( Animate::create( AnimationCache::getInstance()->getAnimation( sstr("walk%d",dir))) );
		setSpriteFrame( sstr("%s%d0.png", m_player.c_str(), dir) );
	}
}

void Player::stepMid( const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish )
{
	Point cur = this->getPosition();
	int dir = cur.x==dst.x ? (cur.y<dst.y?0:2) : (cur.x<dst.x?1:3);

	bool can = cell->checkPlayerSteping(this);

	if (!can)
	{
		this->setPosition( this->getPosition() + cur-dst );
		whenFinish(msMoveThenBack);
	}
	else
	{
		auto moveFinish = std::bind(whenFinish, msFullyFinish);
		this->runAction( Sequence::create( MoveBy::create(0.1f, dst-cur), CallFunc::create(moveFinish), nullptr ) );
		this->runAction( Animate::create( AnimationCache::getInstance()->getAnimation( sstr("walk%d",dir))) );
		setSpriteFrame( sstr("%s%d0.png", m_player.c_str(), dir) );
	}
}

