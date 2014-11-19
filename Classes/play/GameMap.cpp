#include "GameMap.h"
#include "Player.h"
#include "MapCell.h"
#include "SoilBlock.h"

GameMap::GameMap(void)
	:m_restartPlayer(false)
	,m_bUsingMap(false)
	,m_bUsingBomb(false)
	,m_bUsingHoe(false)
{
}


GameMap::~GameMap(void)
{
}

GameMap* GameMap::create( const std::string& tmxFile )
{
	GameMap* ret = new GameMap;
	if (ret->initWithTMXFile(tmxFile))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void GameMap::onClick( const Point& pt )
{
	if (m_bUsingHoe)
	{
		Index2 click = tmxToIndex2(pt);
		//Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
		vector<Index2> surround = getSurrounding(tmxToIndex2(cocosToTMX(m_pPlayer->getPosition())), 2);
		for (Index2& x : surround)
		{
			m_objects[x.first][x.second]->onEffectHoe(false, click==x);
		}
		m_bUsingHoe = false;
		return;
	}
	//
	if (m_bUsingBomb)
	{
		Index2 click = tmxToIndex2(pt);
		//Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
		vector<Index2> surround = getSurrounding(tmxToIndex2(cocosToTMX(m_pPlayer->getPosition())), 2);
		for (Index2& x : surround)
		{
			m_objects[x.first][x.second]->onEffectBomb(false, click==x);
		}
		m_bUsingBomb = false;
		return;
	}
	//
	if (m_bUsingMap)
	{
		m_bUsingMap = false;
		Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
		vector<Index2> surround = getSurrounding(pos, 2);
		for (Index2& x : surround)
		{
			m_objects[x.first][x.second]->onEffectMap(false);
		}
	}

	//
	if (m_curPath.empty())
	{
		m_restartPlayer = false;
		auto x = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
		m_curPath = getPath( x, tmxToIndex2(pt) );
		stepPlayer();
	}
	else
	{
		m_restartPlayer = true;
		m_playerTarget = pt;
	}
}

void GameMap::onLongTouches( const Point& pt )
{

}

bool GameMap::initWithTMXFile( const std::string& tmxFile )
{
	Return_False_If(!TMXTiledMap::initWithTMXFile(tmxFile));

	const int width = static_cast<int>(getMapSize().width);
	const int height = static_cast<int>(getMapSize().height);
	m_tw = getTileSize().width;
	m_th = getTileSize().height;

	m_objects.resize(height);
	for (int r=0; r<height; ++r)
	{
		m_objects[r].resize(width);
		for (int c=0; c<width; ++c)
		{
			MapCell* cell = MapCell::create();
			cell->setPosition( tmxToCocos(index2ToTMX(Index2(r,c)))+Point(m_tw/2, -m_th/2) );
			addChild(cell);
			m_objects[r][c] = cell;
		}
	}

	string obj_layers[] = {"objs2", "objs"};
	for (string x : obj_layers)
	{
		auto unnamed_objs = getObjectGroup(x);
		auto objs = unnamed_objs->getObjects();
		for (auto it = objs.begin(); it != objs.end(); ++it)
		{
			auto obj = it->asValueMap();
			float x = obj["x"].asFloat();
			float y = obj["y"].asFloat();
			Index2 pos = tmxToIndex2( cocosToTMX(Point(x, y)) );
			m_objects[pos.first][pos.second]->addBy(obj);
		}
	}	

	TMXObjectGroup* named_objs = getObjectGroup("named_objs");
	if (nullptr != named_objs)
	{
		ValueMap cfg = named_objs->getObject("player");
		m_pPlayer = Player::create();
		float x = cfg["x"].asFloat();
		float y = cfg["y"].asFloat();
		float w = cfg["width"].asFloat();
		float h = cfg["height"].asFloat();

		m_pPlayer->setPosition(x+w/2,y+h/2);
		addChild(m_pPlayer, 10);
		
		Size size = this->getContentSize(); 
		this->runAction( Follow::create(m_pPlayer, Rect(0, -64, size.width, size.height+64)));
	}

	//init display number
	for (int r=0; r<height; ++r)
	{
		for (int c=0; c<width; ++c)
		{
			int mine_count = 0;
			for (auto&x : getSurrounding(Index2(r,c)))
			{
				if (Is_Trap(m_objects[x.first][x.second]->getState()))
				{
					++mine_count;
				}
			}
			m_objects[ r ][ c ]->setSurroundMineCount(mine_count);
		}
	}

	EventListenerKeyboard* key = EventListenerKeyboard::create();
	key->onKeyPressed = std::bind(&GameMap::onKeyDown, this, std::placeholders::_1, std::placeholders::_2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(key, this);

	dig(tmxToIndex2(cocosToTMX(m_pPlayer->getPosition())));

	return true;
}

GameMap::Index2 GameMap::tmxToIndex2( const Point& pt )
{
	return Index2( (int)((pt.y-0.5)/this->getTileSize().height), int(pt.x)/int(this->getTileSize().width) );
}

Point GameMap::index2ToTMX( const Index2& index )
{
	return Point(index.second*getTileSize().width, index.first*getTileSize().height);
}

Point GameMap::cocosToTMX( Point pt )
{
	return Point(pt.x, this->getContentSize().height-pt.y);
}

Point GameMap::tmxToCocos( Point pt )
{
	return cocosToTMX(pt);
}

list<GameMap::Index2> GameMap::getPath( const Index2& from, const Index2& to )
{
	list<Index2> ret;
	do 
	{
		Break_If(from.first == to.first);
		int rdiff = from.first<to.first ? 1 : -1;
		for (int i=from.first+rdiff; i!=to.first+rdiff; i+=rdiff)
		{
			ret.push_back( make_pair(i, from.second) );
		}
	} while (false);

	do 
	{
		Break_If(from.second == to.second);
		int cdiff = from.second<to.second ? 1 : -1;
		for (int i=from.second+cdiff; i!=to.second+cdiff; i+=cdiff)
		{
			ret.push_back( make_pair(to.first, i) );
		}
	} while (false);

	return ret;
}

void GameMap::stepPlayer()
{
	Return_If(m_curPath.empty());
	auto x = m_curPath.front();
	m_pPlayer->stepTo(
		tmxToCocos(index2ToTMX(x)) + Point(m_tw/2, -m_th/2)
		,m_objects[x.first][x.second]
		,[=](MoveStatus ms){this->onPlayerFinishOneStep(x, ms);} );
}

void GameMap::onPlayerFinishOneStep( const Index2& index, MoveStatus ms )
{
	m_objects[index.first][index.second]->checkPlayerFinished(m_pPlayer);

	if(ms != msFullyFinish)
	{
		m_curPath.clear();
	}
	else
	{
		//dig surrounding
		dig(index);		

		if (m_restartPlayer)
		{
			m_restartPlayer = false;
			m_curPath.clear();
			auto x = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
			m_curPath = getPath( x, tmxToIndex2(m_playerTarget) );
			stepPlayer();
		}
		else if (!m_curPath.empty())
		{
			m_curPath.pop_front();
			stepPlayer();
		}
	}
}

std::vector<GameMap::Index2> GameMap::getSurrounding( const Index2& center, int radius /*= 1*/)
{
	vector<Index2> ret;

	int r_start = center.first-radius;
	int r_end = center.first+radius+1;
	int c_start = center.second-radius;
	int c_end = center.second+radius+1;
	for (int r=max(1,r_start); r<min(r_end, (int)m_objects.size()-1); ++r)
	{
		for (int c=max(1,c_start); c<min(c_end, (int)m_objects[0].size()-1); ++c)
		{
			Continue_If( make_pair(r, c)==center );
			ret.push_back( make_pair(r,c) );
		}
	}

	return ret;
}

void GameMap::dig( const Index2& center )
{
 	int surround_mine = m_objects[center.first][center.second]->getSurroundMineCount();
	Return_If(surround_mine!=0);

	m_objects[center.first][center.second]->onPlayerSurround(m_pPlayer);

	for (auto x : getSurrounding(center, 1))
	{
		Continue_If(x.first==0 || x.first==getMapSize().height-1);
		Continue_If(x.second==0 || x.second==getMapSize().width-1);
		Continue_If(!Can_Expand(m_objects[x.first][x.second]->getState()));
		dig(x);
	}
}

void GameMap::onKeyDown( EventKeyboard::KeyCode key, Event* )
{
	Index2 next = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	Point cur = m_pPlayer->getPosition();
	switch (key)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		--next.second;
		cur.x -= 64;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		++next.second;
		cur.x += 64;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		--next.first;
		cur.y += 64;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		++next.first;
		cur.y -= 64;
		break;
	}

	next.first = max(next.first, 0);
	next.first = min(next.first, (int)getMapSize().height-1);
	next.second = max(next.second, 0);
	next.second = min(next.second, (int)getMapSize().width-1);

	
	onClick(cocosToTMX(cur));
}

void GameMap::onEffectHoe()
{
	Return_If(m_bUsingHoe);

	m_bUsingHoe = true;
	Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	vector<Index2> surround = getSurrounding(pos, 1);
	for (Index2& x : surround)
	{
		m_objects[x.first][x.second]->onEffectHoe(true, false);
	}
}

void GameMap::onEffectBomb()
{
	Return_If(m_bUsingBomb);

	m_bUsingBomb = true;
	Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	vector<Index2> surround = getSurrounding(pos, 1);
	for (Index2& x : surround)
	{
		m_objects[x.first][x.second]->onEffectBomb(true, false);
	}
}

void GameMap::onEffectMap()
{
	Return_If(m_bUsingMap);

	m_bUsingMap = true;
	Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	vector<Index2> surround = getSurrounding(pos, 2);
	for (Index2& x : surround)
	{
		m_objects[x.first][x.second]->onEffectMap(true);
	}
}
