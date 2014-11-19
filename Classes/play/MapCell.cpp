#include "MapCell.h"
#include "Trap.h"
#include "Block.h"
#include "Player.h"

MapCell::MapCell( void )
	:m_pDisplayNumber(nullptr)
	,m_type(tNone)
{

}

MapCell::~MapCell( void )
{

}

bool MapCell::init()
{
	Return_False_If(!Sprite::init());
	//setContentSize(Size(64,64));
	return true;
}

void MapCell::addBy( const cocos2d::ValueMap& data )
{
	const string& type = data.at("type").asString();
	MapObj* obj = MapObj::create(type);
	obj->config(data);

	if (dynamic_cast<Trap*>(obj) != nullptr)
	{
		m_type |= tTrap;
	}
	if (dynamic_cast<Block*>(obj) != nullptr)
	{
		m_type |= tBlock;
	}

	m_objs.push_back(obj);
	addChild(obj);
}

bool MapCell::checkPlayerEnter( Player* player )
{
	bool can = true;
	for (MapObj* obj : m_objs)
	{
		if (!obj->willPlayerEnter(player))
		{
			can = false;
			break;
		}
	}
	return can;
}

bool MapCell::checkPlayerSteping( Player* player )
{
	bool can = true;
	for (MapObj* obj : m_objs)
	{
		if (!obj->onPlayerSteping(player))
		{
			can = false;
		}
	}
	return can;
}

void MapCell::checkPlayerFinished( Player* player )
{
	for (auto& obj : m_objs)
	{
		Continue_If(nullptr==obj);
		if (!obj->onPlayerFinished(player))
		{
			this->removeChild(obj, true);
			obj = nullptr;
		}
	}

	m_objs.remove_if( [](MapObj* obj)->bool{ return obj==nullptr;} );
	m_type &= ~tBlock;
	refreshDisplay();
}

void MapCell::onPlayerSurround(Player* player)
{
	Return_If( Is_Trap(m_type) && Is_Block(m_type) );

	for (auto& obj : m_objs)
	{
		if (!obj->onPlayerSurround(player))
		{
			removeChild(obj, true);
			obj = nullptr;
		}
	}
	m_objs.remove_if( [](MapObj* obj)->bool{ return obj==nullptr;} );

	m_type &= ~tBlock;
	refreshDisplay();
}

// void MapCell::push_top( MapObj* obj )
// {
// 	m_objs.push_back(obj);
// 	addChild(obj);
// }
// 
// void MapCell::remove( MapObj* obj_to_del )
// {
// 	for (auto& obj : m_objs)
// 	{
// 		if (obj==obj_to_del)
// 		{
// 			this->removeChild(obj, true);
// 		}
// 	}
// 	m_objs.remove(obj_to_del);
// }

int MapCell::getSurroundMineCount() const
{
	return m_surroundMineCount;
}

void MapCell::setSurroundMineCount( int num )
{
	m_surroundMineCount = num;

	refreshDisplay();
}

CellState MapCell::getState() const
{
	return (CellState)m_type;
}

void MapCell::refreshDisplay()
{
	if (0==m_surroundMineCount || !m_objs.empty())
	{
		removeChild(m_pDisplayNumber, true);
		m_pDisplayNumber = nullptr;
	}
	else
	{
		if (nullptr==m_pDisplayNumber)
		{
			m_pDisplayNumber = Label::createWithTTF(to_string(m_surroundMineCount), "fonts/Marker Felt.ttf", 32);
			m_pDisplayNumber->setPosition(0,0);
			addChild(m_pDisplayNumber);
		}
		else
		{
			m_pDisplayNumber->setString(to_string(m_surroundMineCount));
		}
	}
}

void MapCell::onEffectHoe( bool start_or_end, bool bUse )
{
	Return_If(m_objs.empty());
	static const int tag = rand();
	if (start_or_end)
	{
		Sprite* sp = Sprite::create();
		sp->setTag(tag);
		Animation* amn = Animation::create();
		for (int i=1; i<18; ++i)
		{
			amn->addSpriteFrameWithFile( cstr("pickaxe_%03d.png", i) );
		}
		amn->setDelayPerUnit(0.1f);
		sp->runAction(RepeatForever::create(Animate::create(amn)));
		sp->setPosition( Point(8, 8) );
		addChild(sp);
	}
	else
	{
		if (bUse && getChildByTag(tag)!=nullptr)
		{
			removeChild(m_objs.back(), true);
			m_objs.pop_back();
		}
		removeChildByTag(tag);
	}
}

void MapCell::onEffectBomb( bool start_or_end, bool bUse )
{
	Return_If(m_objs.empty());
	static const int tag = rand();
	if (start_or_end)
	{
		Sprite* sp = Sprite::create();
		sp->setTag(tag);
		Animation* amn = Animation::create();
		for (int i=1; i<12; ++i)
		{
			amn->addSpriteFrameWithFile( cstr("dinamit_%03d.png", i) );
		}
		amn->setDelayPerUnit(0.1f);
		sp->runAction(RepeatForever::create(Animate::create(amn)));
		sp->setPosition( Point(8, 8) );
		addChild(sp);
	}
	else
	{
		if (bUse && getChildByTag(tag)!=nullptr)
		{
			removeChild(m_objs.back(), true);
			m_objs.pop_back();
		}
		removeChildByTag(tag);
	}
}

void MapCell::onEffectMap(bool start_or_end)
{
	Return_If(m_objs.empty());
	static const int tag = rand();
	if (start_or_end)
	{
		Sequence* seq = Sequence::createWithTwoActions( FadeTo::create(1,0), FadeTo::create(1,255) );
		RepeatForever* rep = RepeatForever::create(seq);
		rep->setTag(tag);
		m_objs.back()->runAction( rep );
	}
	else
	{
		m_objs.back()->setOpacity(255);
		m_objs.back()->stopActionByTag(tag);
	}
}
