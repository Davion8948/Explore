#include "MapCell.h"
#include "Player.h"
#include "Trap.h"
#include "LevelData.h"

static const int tag_effect_map = 0x03;
static const int tag_effect_bomb = 0x02;
static const int tag_effect_hoe = 0x01;

MapCell::MapCell( void )
	:m_pDisplayNumber(nullptr)
	,m_isMine(false)
	,m_isFlagged(false)
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

void MapCell::pushObjBy( const cocos2d::ValueMap& data )
{
	const string& type = data.at("type").asString();
	MapObj* obj = MapObj::create(type, data);
	obj->setParentCell(this);
	obj->config(data);

	m_objs.push_front(obj);
	addChild(obj);

	if (!m_isMine)
	{
		m_isMine = (dynamic_cast<Trap*>(obj)!=nullptr);
	}
}

bool MapCell::empty()
{
	return m_objs.empty();
}

bool MapCell::isMine()
{
	return m_isMine;
}

void MapCell::setSurroundMineCount( int num )
{
	m_surroundMineCount = num;

	refreshDisplay();
}

void MapCell::onFlagged()
{
	Return_If(m_objs.empty());
	ObjAttr attr = m_objs.front()->getAttr();
	Return_If(!attr.canUseFlag());
	m_isFlagged = !m_isFlagged;
	static const int tag = 0x04;
	if (m_isFlagged)
	{
		Sprite* flag = Sprite::create("flag.png");
		flag->setScale(3);
		flag->runAction(ScaleTo::create(0.2f,1));
		flag->setPosition(tw/2, -th/2);
		addChild(flag, 0, tag);
		playEffect(SettingFlag);
	}
	else
	{
		removeChildByTag(tag);
		playEffect(RemoveFlag);
	}
}

bool MapCell::checkPlayerEnter( Player* player )
{
	Return_False_If(m_isFlagged);

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
	Return_If(m_isFlagged);

	for (auto& obj : m_objs)
	{
		CCAssert(nullptr!=obj, "");
		if (!obj->onPlayerFinished(player))
		{
			this->removeChild(obj, true);
			obj = nullptr;
		}
	}

	m_objs.remove_if( [](MapObj* obj)->bool{ return obj==nullptr;} );
	refreshDisplay();
}

void MapCell::checkDig(Player* player)
{
	Return_If( m_objs.empty() );
	Return_If( m_surroundMineCount!=0 );
	Return_If( isMine() );
	Return_If( m_isFlagged );

	for (auto& obj : m_objs)
	{
		if (!obj->onPlayerSurround(player))
		{
			removeChild(obj, true);
			obj = nullptr;
		}
	}
	m_objs.remove_if( [](MapObj* obj)->bool{ return obj==nullptr;} );

	refreshDisplay();
}

void MapCell::playTopEffect( Node* node )
{
	CCAssert(nullptr!=node, "");
	node->setPosition( node->getPosition()+getPosition() );
	getParent()->addChild(node);
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
			m_pDisplayNumber->setPosition(tw/2,-th/2);
			addChild(m_pDisplayNumber);
		}
		else
		{
			m_pDisplayNumber->setString(to_string(m_surroundMineCount));
		}
	}
}

bool MapCell::onEffectHoe( bool start_or_end, bool bUse )
{
	Return_False_If(m_objs.empty());
	Return_False_If(!m_objs.front()->getAttr().canUseHoe());
	Return_False_If( m_isFlagged );

	if (start_or_end)
	{
		Sprite* sp = Sprite::create();
		sp->setTag(tag_effect_hoe);
		Animation* amn = Animation::create();
		for (int i=1; i<18; ++i)
		{
			amn->addSpriteFrameWithFile( cstr("pickaxe_%03d.png", i) );
		}
		amn->setDelayPerUnit(0.1f);
		sp->runAction(RepeatForever::create(Animate::create(amn)));
		sp->setPosition( Point(tw/2, -th/2) );
		addChild(sp);
	}
	else
	{
		if (bUse)
		{
			removeChild(m_objs.front(), true);
			m_objs.pop_front();
			playEffect(UseHoe);
		}
		removeChildByTag(tag_effect_hoe);
	}
	return true;
}

bool MapCell::onEffectBomb( bool start_or_end, bool bUse )
{
	Return_False_If(m_objs.empty());
	Return_False_If(!m_objs.front()->getAttr().canUseBomb());
	Return_False_If( m_isFlagged );

	if (start_or_end)
	{
		Sprite* sp = Sprite::create();
		sp->setTag(tag_effect_bomb);
		Animation* amn = Animation::create();
		for (int i=1; i<12; ++i)
		{
			amn->addSpriteFrameWithFile( cstr("dinamit_%03d.png", i) );
		}
		amn->setDelayPerUnit(0.1f);
		sp->runAction(RepeatForever::create(Animate::create(amn)));
		sp->setPosition( Point(tw/2, -th/2) );
		addChild(sp);
	}
	else
	{
		if (bUse)
		{
			for (auto x : m_objs)
				removeChild(x, true);
			m_objs.clear();
			playEffect(UseBomb);
		}
		removeChildByTag(tag_effect_bomb);

		if (isMine())
		{
			LevelData::inst().addDestroyedTrap(1);
		}
	}
	return true;
}

bool MapCell::onEffectMap(bool start_or_end)
{
	Return_False_If(m_objs.empty());
	Return_False_If(!m_objs.front()->getAttr().canUseMap());
	Return_False_If( m_isFlagged );

	static const int tag_effect_map = 0x03;
	if (start_or_end)
	{
		Sequence* seq = Sequence::createWithTwoActions( FadeTo::create(1,0), FadeTo::create(1,255) );
		RepeatForever* rep = RepeatForever::create(seq);
		rep->setTag(tag_effect_map);
		m_objs.front()->runAction( rep );

		playEffect(UseMap);
	}
	else
	{
		m_objs.front()->setOpacity(255);
		m_objs.front()->stopActionByTag(tag_effect_map);
	}

	return true;
}

int MapCell::getAStarCost()
{
	Return_Null_If(m_objs.empty());
	if (m_isFlagged)
	{
		return ObjAttr::AStarMax;
	}
	else if ( !m_objs.empty() )
	{
		return m_objs.front()->getAttr().AStarCost();
	}
	else
	{
		return ObjAttr::AStarMin;
	}
}

void MapCell::clear()
{
	m_isMine = false;
	m_isFlagged = false;
	
	m_objs.clear();
	removeAllChildren();
}
