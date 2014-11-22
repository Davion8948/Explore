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
	Index2 pos = tmxToIndex2(pt);
	if (pos.first>0 && pos.first<m_objects.size()-1 && pos.second>0 && pos.second<m_objects[0].size()-1)
	{
		m_objects[pos.first][pos.second]->onFlagged();
	}
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
			m_objects[pos.first][pos.second]->pushObjBy(obj);
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
				if (m_objects[x.first][x.second]->isMine())
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
	struct AStarInfo
	{
		int g;
		int h;
		Index2 parent;
		int f(){ return g+h; }
		AStarInfo(int argg, int argh){
			g = argg;
			h = argh;
			parent.first = parent.second = -1;
		}
	};
	map<Index2, AStarInfo> opened;
	map<Index2, AStarInfo> closed;
	auto last_obj = opened.end();
	opened.insert( make_pair(from, AStarInfo(0,0)) );
	do
	{
		Break_If( opened.empty() );

		int min_cost = INT_MAX;
		Index2 curPos(-1,-1);
		AStarInfo curInfo(INT_MAX, 0);
		map<Index2, AStarInfo>::iterator cur;
		for (map<Index2, AStarInfo>::iterator it = opened.begin(); it != opened.end(); ++it)
		{
			if (it->second.f() < curInfo.f())
			{
				curPos = it->first;
				curInfo = it->second;
				cur = it;
			}
		}
		opened.erase(cur);
		closed.insert( make_pair(curPos, curInfo) );

		auto surround = getSurrounding(curPos, 1);
		for (auto it = surround.begin(); it != surround.end(); ++it)
		{
			MapCell* cell = m_objects[it->first][it->second];
			if ( cell->getAStarCost()==INT_MAX || closed.find(*it)!=closed.end() )
			{
				//do nothing
			}
			else if ( opened.find(*it) == opened.end() )
			{
				AStarInfo info( curInfo.g+loss(curPos,*it), loss(*it, to) );
				info.parent = curPos;
				opened.insert( make_pair(*it, info) );
			}
			else//已经在开启列表中，检查新的路径是否更好
			{
				auto has = opened.find(*it);
				if (has->second.g > curInfo.g+loss(curPos,*it))
				{
					has->second.parent = curPos;
					has->second.g = curInfo.g+loss(curPos,*it);
				}
			}
		}
		
		last_obj = opened.find(to);
		if (last_obj != opened.end())
			break;

	} while (true);

	if (last_obj == opened.end())
	{
		return list<Index2>();
	}

	list<Index2> ret;
	ret.push_front( last_obj->first );
	auto path = closed.find( last_obj->second.parent );
	while (path != closed.end())
	{
		ret.push_front(path->first);
		path = closed.find( path->second.parent );
	}
	if (!ret.empty())
		ret.pop_front();
	return ret;
}

int GameMap::loss(const GameMap::Index2& arg1, const GameMap::Index2& arg2)
{
	int deltaX = abs(arg1.first-arg2.first);
	int deltaY = abs(arg1.second-arg2.second);
	return (min(deltaX,deltaY)*15 + abs(max(deltaX,deltaY)-min(deltaX,deltaY))*10);
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
	m_objects[center.first][center.second]->checkDig(m_pPlayer);

	for (auto x : getSurrounding(center, 2))
	{
		m_objects[x.first][x.second]->checkDig(m_pPlayer);
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

bool GameMap::onEffectHoe()
{
	Return_False_If(m_bUsingHoe);

	Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	vector<Index2> surround = getSurrounding(pos, 1);
	for (Index2& x : surround)
	{
		bool ret = m_objects[x.first][x.second]->onEffectHoe(true, false);
		m_bUsingHoe = ret||m_bUsingHoe;
	}
	return m_bUsingHoe;
}

bool GameMap::onEffectBomb()
{
	Return_False_If(m_bUsingBomb);

	Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	vector<Index2> surround = getSurrounding(pos, 1);
	for (Index2& x : surround)
	{
		bool ret = m_objects[x.first][x.second]->onEffectBomb(true, false);
		m_bUsingBomb = ret||m_bUsingBomb;
	}
	return m_bUsingBomb;
}

bool GameMap::onEffectMap()
{
	Return_False_If(m_bUsingMap);

	Index2 pos = tmxToIndex2(cocosToTMX(m_pPlayer->getPosition()));
	vector<Index2> surround = getSurrounding(pos, 2);
	for (Index2& x : surround)
	{
		bool ret = m_objects[x.first][x.second]->onEffectMap(true);
		m_bUsingMap = ret||m_bUsingMap;
	}
	return m_bUsingMap;
}
