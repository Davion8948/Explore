#include "GameMap.h"
#include "Player.h"
#include "MapCell.h"
#include "GameMapRoom.h"
#include "GameMapRecrusive.h"
#include "Toolbar.h"

GameMap::GameMap(void)
	:m_restartPlayer(false)
	,m_pPlayer(nullptr)
	,m_bUsingMap(false)
	,m_bUsingBomb(false)
	,m_bUsingHoe(false)
	,m_tw(tw)
	,m_th(th)
{
}


GameMap::~GameMap(void)
{
}

GameMap* GameMap::create( int mainLevel, int viceLevel )
{
	GameMap* ret = new GameMapRecrusive();
	if (ret->initWithLevel(mainLevel, viceLevel))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void GameMap::onClick( const Point& pt )
{
	m_pPlayer->hideTip();

	Index2 click = pointToIndex2(pt);
	Index2 player = pointToIndex2(m_pPlayer->getPosition());

	CCLOG("click(%d, %d)", click.first, click.second);
	Rect asdf = this->getBoundingBox();
	if (m_bUsingHoe)
	{
		vector<Index2> surround = getSurrounding( player, 2);
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
		vector<Index2> surround = getSurrounding(player, 2);
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
		vector<Index2> surround = getSurrounding(player, 2);
		for (Index2& x : surround)
		{
			m_objects[x.first][x.second]->onEffectMap(false);
		}
	}

	Return_If(player == click);
	
	//
	if (m_curPath.empty())
	{
		m_restartPlayer = false;
		auto x = player;
		m_curPath = getPath( x, click );
		if (m_curPath.empty())
		{
			m_pPlayer->showTip("unknown.png");
		}
		else
		{
			stepPlayer();
		}
	}
	else
	{
		m_restartPlayer = true;
		m_playerTarget = pt;
	}
}

void GameMap::onLongTouches( const Point& pt )
{
	m_pPlayer->hideTip();

	Index2 click = pointToIndex2(pt);
	if (click.first>0 && click.first<m_objects.size()-1 && click.second>0 && click.second<m_objects[0].size()-1)
	{
		m_objects[click.first][click.second]->onFlagged();
	}
}

bool GameMap::initWithLevel( int mainLevel, int viceLevel )
{
	Return_False_If(!Node::init());

	this->makeMap(mainLevel, viceLevel);

	const int order = m_objects.size()*m_objects[0].size();
	const Size size = this->getContentSize();
	float x = 0;
	float up_height = 0;
	while (x<size.width)
	{
		Sprite* sp = Sprite::create("bound_up.png");
		sp->setPosition(x, size.height);
		sp->setAnchorPoint(Point(0,0));
		addChild(sp, order);

		x += sp->getContentSize().width;

		up_height = sp->getContentSize().height;
	}
	x = 0;
	float bottom_height = 0;
	while (x<size.width)
	{
		Sprite* sp = Sprite::create("bound_bottom.png");
		sp->setPosition(x, 0);
		sp->setAnchorPoint(Point(0,1));
		addChild(sp, order+1);

		x += sp->getContentSize().width;

		bottom_height = sp->getContentSize().height;
	}

	float y = -bottom_height;
	float left_width = 0;
	while (y<size.height)
	{
		Sprite* sp = Sprite::create("bound_left.png");
		sp->setPosition(0, y);
		sp->setAnchorPoint(Point(1,0));
		addChild(sp, order);

		left_width = sp->getContentSize().width;

		sp = Sprite::create("bound_left.png");
		sp->setAnchorPoint(Point(0,0));
		sp->setRotation(180);
		sp->setPosition(size.width+left_width, y+sp->getContentSize().height);
		addChild(sp, order);

		y += sp->getContentSize().height;
	}

	//init display number
	for (int r=0; r<m_objects.size(); ++r)
	{
		for (int c=0; c<m_objects[r].size(); ++c)
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

	CCAssert(NULL!=m_pPlayer, "");
	dig(pointToIndex2(m_pPlayer->getPosition()));

// 	Size size = this->getContentSize(); 
// 	-m_border.width, -m_border.height, size.width+m_border.width*2, size.height+m_border.height*2
	const float tool = toolbar->getContentSize().height*4/5;
	this->runAction( Follow::create(m_pPlayer, Rect(-left_width, -bottom_height-tool, size.width+left_width*2, size.height+up_height+bottom_height+tool)));
	return true;
}

Point GameMap::index2ToPoint( const Index2& index )
{
	Point pt;
	pt.x = index.second * m_tw;
	pt.y = index.first * m_th;
// 	pt += m_border;
	return pt;
}

GameMap::Index2 GameMap::pointToIndex2( const Point& point )
{
	Index2 index;
	index.first = static_cast<int>( (point.y) / m_th);
	index.second = static_cast<int>( (point.x) / m_tw);
	return index;
}

list<GameMap::Index2> GameMap::getPath( const Index2& from, const Index2& to )
{
	if (from==to || (to.first<0 || to.first>=m_objects.size() || to.second<0 || to.second>=m_objects[0].size()))
		return list<Index2>();

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
			if ( *it == to )
			{
				AStarInfo info( curInfo.g+loss(curPos,*it), loss(*it, to) );
				info.parent = curPos;
				opened.insert( make_pair(*it, info) );
			}
			else if ( cell->getAStarCost()==INT_MAX || closed.find(*it)!=closed.end() )
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

	if (ret.size() > 10)
	{
		ret.clear();
	}
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
		index2ToPoint(x)+Point(m_tw/2, m_th/2),
		m_objects[x.first][x.second],
		[=](MoveStatus ms){this->onPlayerFinishOneStep(x, ms);} );
}

void GameMap::onPlayerFinishOneStep( const Index2& index, MoveStatus ms )
{
	m_objects[index.first][index.second]->checkPlayerFinished(m_pPlayer);

	if (GameStateMgr::inst().curState()==gs_win)
	{
		m_curPath.clear();
	}
	else if(ms != msFullyFinish)
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
			auto x = pointToIndex2(m_pPlayer->getPosition());
			m_curPath = getPath( x, pointToIndex2(m_playerTarget) );
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
	for (int r=max(0,r_start); r<min(r_end, (int)m_objects.size()); ++r)
	{
		for (int c=max(0,c_start); c<min(c_end, (int)m_objects[0].size()); ++c)
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

bool GameMap::onEffectHoe()
{
	Return_False_If(m_bUsingHoe);

	Index2 pos = pointToIndex2(m_pPlayer->getPosition());
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

	Index2 pos = pointToIndex2(m_pPlayer->getPosition());
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

	Index2 pos = pointToIndex2(m_pPlayer->getPosition());
	vector<Index2> surround = getSurrounding(pos, 2);
	for (Index2& x : surround)
	{
		bool ret = m_objects[x.first][x.second]->onEffectMap(true);
		m_bUsingMap = ret||m_bUsingMap;
	}
	return m_bUsingMap;
}
