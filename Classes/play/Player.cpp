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
	initWithSpriteFrameName(name+"_00.png");
	CCAnimationCache::getInstance()->addAnimationsWithFile(name+".action");
 	setAnchorPoint(Point(0.5f,0.2f));
}

void Player::stepTo(const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish )
{
	Point cur = this->getPosition();
	int dir = getDirection(cur, dst);

	bool can = cell->checkPlayerEnter(this);

	if (!can)
	{
		setSpriteFrame( sstr("%s_%d0.png", m_player.c_str(), dir) );
		whenFinish(msCanotMove);
	}
	else
	{
		auto callMid = bind( &Player::stepMid, this, dst, cell, whenFinish);
		this->runAction( Sequence::create( MoveBy::create(0.1f, (dst-cur)/2), CallFunc::create(callMid), nullptr ) );

		this->runAction( Animate::create( AnimationCache::getInstance()->getAnimation( sstr("walk%d",dir))) );

		playEffect(PlayerSteps);
	}
}

void Player::stepMid( const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish )
{
	Point cur = this->getPosition();
	int dir = getDirection(cur, dst);

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
	}
}

Player::Direction Player::getDirection( const Point& start, const Point& end )
{
	Point diff = end - start;
	if (diff.x == 0)
	{
		CCAssert(diff.y != 0, "");
		return (diff.y>0 ? d_up : d_down);
	}
	else if (diff.x > 0)
	{
		if (diff.y > 0)
		{
			return d_ur;
		}
		else if (diff.y == 0)
		{
			return d_right;
		}
		else
		{
			return d_rd;
		}
	}
	else
	{
		if (diff.y > 0)
		{
			return d_lt;
		}
		else if (diff.y == 0)
		{
			return d_left;
		}
		else
		{
			return d_dl;
		}
	}
}

void Player::showTip( const string& tip_name )
{
	removeAllChildren();
	Sprite* need = Sprite::create("need.png");
	need->setPosition( this->getContentSize() );
	Sprite* tip = Sprite::create(tip_name);
	tip->setPosition( need->getContentSize()/2+Size(0,5) );
	tip->setScale(0.5f);
	need->addChild(tip);

	need->setScale(0);
	need->runAction( Sequence::create(ScaleTo::create(0.1f, 1.4f),ScaleTo::create(0.0f, 1.0f),nullptr) );
	addChild(need);

	playEffect(Confused);
}

void Player::hideTip()
{
	removeAllChildren();
}

void Player::onStateChanged( GameState gs )
{
	if (gs == gs_win)
	{
		getParent()->stopAllActions();
		stopAllActions();
		runAction(JumpBy::create(3, Point(0,0), 64, 3));
		Animation* ani = Animation::create();
		for (int i=3; i<6; ++i)
		{
			string name = sstr("%s_%d0.png", m_player.c_str(), i);
			ani->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName(name));
		}
		ani->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName(m_player + "_40.png"));
		ani->setDelayPerUnit(0.1f);
		this->runAction( Repeat::create( Animate::create(ani), 9) );
	}
}

