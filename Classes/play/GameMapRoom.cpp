#include "GameMapRoom.h"

GameMapRoom::GameMapRoom(void)
{
}


GameMapRoom::~GameMapRoom(void)
{
}

void GameMapRoom::makeMap( int mLevel, int vLevel )
{
	//10*20 -> 20*20 -> 20*30 -> 30*30
	m_mapRows = 10*(vLevel/2+1);
	m_mapCols = 20+10*vLevel/2;

	m_roomNum = 100;//3 + vLevel/2;
	m_roomSize = 5;//3 + vLevel/2;

	m_mineMax = 5 + 10*vLevel;
	m_coinMax = 5 + 10*vLevel;
	m_propMax = 5 + 10*vLevel;

	m_hallMin = max(2, 5 - vLevel/2);

	//
	m_objects.resize(m_mapRows);
	for (int r=0; r<m_mapRows; ++r)
	{
		m_objects[r].resize(m_mapCols);
		for (int c=0; c<m_mapCols; ++c)
		{
			MapCell* cell = MapCell::create();
			cell->setPosition( Point(c*m_tw, r*m_th) + Point(m_tw/2, m_th/2) );
			cell->setLocalZOrder((m_mapRows-r-1)*m_mapCols + c);
			addChild(cell);
			m_objects[r][c] = cell;
		}
	}

	//
	this->setContentSize(Size(m_mapCols*m_tw, m_mapRows*m_th));

	//
	generateBound();

  	const int roomW = 3+rand()%m_roomSize;//算墙壁
  	const int roomH = 3+rand()%m_roomSize;
  	for (int i=0; i<m_roomNum; ++i)
  	{
  		int x = rand();
  		int y = rand();
  		int r = x%(m_mapRows-roomH-1)+1;
  		int c = y%(m_mapCols-roomW-1)+1;
  		generateRoom(r, c, roomW, roomH);
  	}

	while (m_mineMax>0)
	{
		int r = rand()%(m_mapRows-2)+1;
		int c = rand()%(m_mapCols-2)+1;
		generateTrap(r, c);
	}

	while (m_propMax > 0)
	{
		int r = rand()%(m_mapRows-2)+1;
		int c = rand()%(m_mapCols-2)+1;
		generateProp(r, c);
	}

	for (int r = 0; r < m_mapRows; r++)
	{
		for (int j=0; j < m_mapCols; ++j)
		{
			if (m_objects[r][j]->empty())
			{
				if (rand()%100<70)
				{
					ValueMap val;
					val["type"] = "Soil";
					val["texture"] = "soil0.png";
					m_objects[r][j]->pushObjBy(val);
				}
			}
		}
	}

	//
	m_pPlayer = Player::create();
	m_pPlayer->setPosition(Point(m_tw, m_th)+Point(m_tw/2, m_th/2));
	addChild(m_pPlayer);

	//
// 	ValueMap val;
// 	val["type"] = "LevelStair";
// 	m_objects[2][1]->clear();
// 	m_objects[2][1]->pushObjBy(val);
}

void GameMapRoom::fillBound( int rs, int cs, int re, int ce, const ValueMap& val )
{
	for (int c=cs; c<ce; ++c)
	{
		m_objects[rs][c]->pushObjBy(val);
		m_objects[re-1][c]->pushObjBy(val);
	}
	for (int r=rs+1; r<re-1; ++r)
	{
		m_objects[r][cs]->pushObjBy(val);
		m_objects[r][ce-1]->pushObjBy(val);
	}
}

void GameMapRoom::generateBound()
{
	ValueMap val;
	val["type"] = "Landscape";
	val["texture"] = "bounding.png";
	for (int c=0; c<m_mapCols; ++c)
	{
		m_objects[0][c]->pushObjBy(val);
		m_objects[m_mapRows-1][c]->pushObjBy(val);
	}
	for (int r=1; r<m_mapRows-1; ++r)
	{
		m_objects[r][0]->pushObjBy(val);
		m_objects[r][m_mapCols-1]->pushObjBy(val);
	}
}

void GameMapRoom::generateRoom( int r, int c, int w, int h )
{
	Return_If(w<3 || h<3);

	auto inRect = [](const Index2& start, const Index2& end, int r, int c)->bool{
		if (r<start.first || r>=end.first)
			return false;
		if (c<start.second || c>=end.second)
			return false;
		return true;
	};//(r,c)是否在房间内部，房间的墙算作房间的外部

	ValueMap val;
	val["type"] = "Rock";

	bool isCombined = false;
	for (auto it = m_roomCounter.begin(); it != m_roomCounter.end(); ++it)
	{
		if (inRect(it->first, it->second, r, c)
			|| inRect(it->first, it->second, r+h-1, c)
			|| inRect(it->first, it->second, r+h-1, c+w-1)
			|| inRect(it->first, it->second, r, c+w-1))
		{
			isCombined = true;
// 			clearBound(r, c, r+h, c+w);
// 			
// 			for (int i=r; i<r+h; ++i)
// 			{
// 				if (!inRect(it->first, it->second, i, c))
// 					generateRock(i, c);
// 				if (!inRect(it->first, it->second, i, c+w-1))
// 					generateRock(i, c+w-1);
// 			}
// 			for (int j=c+1; j<c+w-1; ++j)
// 			{
// 				if (!inRect(it->first, it->second, r, j))
// 					generateRock(r, j);
// 				if (!inRect(it->first, it->second, r+h-1, j))
// 					generateRock(r+h-1, j);
// 			}
// 
// 			int rs = min( it->first.first, r );
// 			int cs = min( it->first.second, c );
// 			int re = max( it->second.first, r+h );
// 			int ce = max( it->second.second, c+w );
// 			m_roomCounter.erase(it);
// 			m_roomCounter[ Index2(rs, cs) ] = Index2(re, ce);
			break;
		}
	}

	if (!isCombined)
	{
		clearBound(r, c, r+h, c+w);
		fillBound(r, c, r+h, c+w, val);
		int cr = r+1, cc = c+1;
		if (h>3)
			cr = r + rand()%(h-2)+1;
		if (w>3)
			cc = c + rand()%(w-2)+1;
//  		generateFeature(cr, cc);
		switch (rand()%4)
		{
		case 0:
			generateHole(cr, c);
			break;
		case 1:
			generateHole(cr, c+w-1);
			break;
		case 2:
			generateHole(r, cc);
			break;
		case 3:
			generateHole(r+h-1, cc);
			break;
		}
		m_roomCounter[ Index2(r, c) ] = Index2(r+h, c+w);
	}
}

void GameMapRoom::generateFeature( int r, int c )
{
	int percent = rand()%100;
	if (percent<33)
	{
		generateTrap(r, c);
	}
	else if (percent<66)
	{
		generateProp(r, c);
	}
	else
	{
		generateCoin(r, c);
	}

// 	ValueMap val;
// 	val["type"] = "Soil";
// 	m_objects[r][c]->pushObjBy(val);
}

void GameMapRoom::clearBound( int rs, int cs, int re, int ce )
{
	for (int r=rs; r<re; ++r)
	{
		for (int c=cs; c<ce; ++c)
		{
			m_objects[r][c]->clear();
		}
	}
}

void GameMapRoom::generateRock( int r, int c )
{
	ValueMap val;
	val["type"] = "Rock";
	m_objects[r][c]->clear();
	m_objects[r][c]->pushObjBy(val);
}

void GameMapRoom::generateTrap( int r, int c )
{
	Return_If(m_mineMax==0);
	ValueMap val;
	val["type"] = rand()%2==0 ? "TrapBomb" : "TrapFire";
	m_objects[r][c]->clear();
	m_objects[r][c]->pushObjBy(val);
	m_mineMax--;

	val["type"] = "Soil";
	val["texture"] = "soil0.png";
	m_objects[r][c]->pushObjBy(val);
}

void GameMapRoom::generateProp( int r, int c )
{
	Return_If(m_propMax==0);
	string candy[] = {
		"heart.png", "shield.png", "key.png", "arrow.png", "hoe.png", "bomb.png", "map.png"
	};
	ValueMap val;
	val["type"] = "Prop";
	val["texture"] = candy[ rand()%6 ];
	m_objects[r][c]->clear();
	m_objects[r][c]->pushObjBy(val);
	m_propMax--;

	val["type"] = "Soil";
	m_objects[r][c]->pushObjBy(val);
}

void GameMapRoom::generateCoin( int r, int c )
{
	Return_If(m_coinMax-- == 0);
	ValueMap val;
	val["type"] = "Coin";
	val["coin"] = rand()%10<7 ? 10 : 100;
	m_objects[r][c]->clear();
	m_objects[r][c]->pushObjBy(val);
}

void GameMapRoom::generateHole( int r, int c )
{
	m_objects[r][c]->clear();

	ValueMap monster;
	ValueMap door;
	door["type"] = "LockedDoor";
	monster["type"] = "Monster";
	monster["texture"] = "monster1.png";
	int percent = rand()%100;
	if (percent<=80)
	{
		m_objects[r][c]->pushObjBy( rand()%2 ? monster : door );
	}
}

void GameMapRoom::generateRecursive( int rs, int cs, int re, int ce )
{
	int rdiff = re-rs;
	int cdiff = ce-cs;
	if (rdiff<m_hallMin || cdiff<m_hallMin)
		return;

	int rc = rand()%rdiff + rs;
	int cc = rand()%cdiff + cs;

	int r;
	for (r = rc; r>=rs; --r)
	{
		if (!m_objects[r][cc]->empty())
			break;
		generateRock(r, cc);
	}
	r = (max(r, rs)-rc) + max(r, rs);
	generateHole(r, cc);

	int c;
	for (c=cc; c<ce; ++c)
	{
		if (!m_objects[rc][c]->empty())
			break;
		generateRock(rc, c);
	}
	c = rand()%(min(c, ce)-cc) + cc;
	generateHole(rc, c);

	for (r=rc; r<re; ++r)
	{
		if (!m_objects[r][cc]->empty())
			break;
		generateRock(r, cc);
	}
	r = rand()%(min(r, re)-rc) + rc;
	generateHole(r, rc);

	for (c = cc; c>=cs; --c)
	{
		if (!m_objects[rc][c]->empty())
			break;
		generateRock(rc, c);
	}
	c = rand()%(max(c, cs)) + max(c, cs);
	generateHole(rc, c);

	generateRecursive(rs, cs, rc, cc);
	generateRecursive(rs, cc+1, rc, ce);
	generateRecursive(rc+1, cc+1, re, ce);
	generateRecursive(rc+1, cs, re, cc);
}
