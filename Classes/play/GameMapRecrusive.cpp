#include "GameMapRecrusive.h"

GameMapRecrusive::GameMapRecrusive(void)
    :m_mLevel(0)
    ,m_vLevel(0)
{
}


GameMapRecrusive::~GameMapRecrusive(void)
{
}

void GameMapRecrusive::makeMap(int mLevel, int vLevel)
{
    m_mLevel = mLevel;
    m_vLevel = vLevel;

    //10*20 -> 20*20 -> 20*30 -> 30*30
    m_mapRows = 10* (vLevel/2+1);
    m_mapCols = 20+10*vLevel/2;
    m_mapCols = min(50, m_mapCols);

    m_roomSize = 5-vLevel/3;//3 + vLevel/2;
    m_roomSize = max(3, m_roomSize);

    m_mineCount = 5 + 10*vLevel;
    m_coinCount = 5 + 10*vLevel;
    m_propCount = 5 + 10*vLevel;
// 	m_hallMin = max(2, 5 - vLevel/2);
    //
    m_objects.resize(m_mapRows);

    for(int r=0; r<m_mapRows; ++r)
    {
        m_objects[r].resize(m_mapCols);

        for(int c=0; c<m_mapCols; ++c)
        {
            MapCell* cell = MapCell::create();
            cell->setPosition(Point(c*m_tw, r*m_th) + Point(0, m_th) /*+ m_border*/);
            cell->setLocalZOrder((m_mapRows-r-1)*m_mapCols + c);
            addChild(cell);
            m_objects[r][c] = cell;
        }
    }

    //
    this->setContentSize(Size(m_mapCols*m_tw/*+m_border.width*2*/, m_mapRows*m_th/*+m_border.height*2*/));
    generate(0, 0, m_mapRows, m_mapCols);

    while(m_mineCount>0)
    {
        int r = rand()% (m_mapRows-2)+1;
        int c = rand()% (m_mapCols-2)+1;
        setTrap(r, c);
    }

    while(m_coinCount>0)
    {
        int r = rand()% (m_mapRows-2)+1;
        int c = rand()% (m_mapCols-2)+1;
        setCoin(r, c);
    }

    while(m_propCount > 0)
    {
        int r = rand()% (m_mapRows-2)+1;
        int c = rand()% (m_mapCols-2)+1;
        setProp(r, c);
    }

	for (int r = 0; r < m_mapRows; ++r)
	{
		for (int j=0; j < m_mapCols; ++j)
		{
			if (m_objects[r][j]->empty())
			{
				if (rand()%100<70)
				{
					setSoil(r, j, false);
				}
			}
		}
	}
    //
    const Index2 pos(rand()%m_mapRows,0);
    m_pPlayer = Player::create();
    m_pPlayer->setPosition(index2ToPoint(pos)+Point(m_tw/2, m_th/2));
    addChild(m_pPlayer, m_mapRows*m_mapCols+1);
    m_objects[pos.first][pos.second]->clear();

    for(auto x : getSurrounding(pos))
    {
        m_objects[x.first][x.second]->clear();
    }

    //
    ValueMap val;
    val["type"] = "LevelStair";
    const Index2 win(rand()%m_mapRows, m_mapCols-1);
    m_objects[win.first][win.second]->clear();
    m_objects[win.first][win.second]->pushObjBy(val);
}

int rand(int start, int end)
{
    if(start==end)
    {
        return start;
    }

    return rand()% (end-start)+start;
}

void GameMapRecrusive::generate(int rs, int cs, int re, int ce)
{
    int ro = generateRow(rs, cs, re, ce);
    int co = generateCol(rs, cs, re, ce);

    if(ro==co && ro==-1)
        return;

    bool allowTrap = (m_vLevel>1);

    if(ro!=-1 && co==-1)
    {
        int cm = rand(cs, ce);
        setMouth(ro, cm, allowTrap);
        generate(rs, cs, ro, ce);
        generate(ro+1, cs, re, ce);
    }
    else if(ro==-1 && co!=-1)
    {
        int rm = rand(rs, re);
        setMouth(rm, co, allowTrap);
        generate(rs, cs, re, co);
        generate(rs, co+1, re, ce);
    }
    else
    {
        int candy[] = {0, 1, 2, 3};
        std::random_shuffle(candy, candy+4);

        for(int i=0; i<3; ++i)
        {
            int r,c;

            switch(candy[i])
            {
            case 0:
                r = rand(rs, ro);
                c = co;
                break;

            case 1:
                r = ro;
                c = rand(co+1, ce);
                break;

            case 2:
                r = rand(ro+1, re);
                c = co;
                break;

            case 3:
                r = ro;
                c = rand(cs+1, co);
                break;

            default:
                break;
            }

            setMouth(r, c, allowTrap);
        }

        generate(rs, cs, ro, co);
        generate(rs, co+1, ro, ce);
        generate(ro+1, co+1, re, ce);
        generate(ro+1, cs, re, co);
    }
}

int GameMapRecrusive::generateRow(int rs, int cs, int re, int ce)
{
    int diff = re-rs;

    if(diff<m_roomSize)
        return -1;

    int rc = rand(rs+m_roomSize/2-1, re-m_roomSize/2);

    for(int c = cs; c < ce; ++c)
    {
        setRock(rc, c);
    }

    return rc;
}

int GameMapRecrusive::generateCol(int rs, int cs, int re, int ce)
{
    int diff = ce-cs;

    if(diff<m_roomSize)
        return -1;

    int cc = rand(cs+m_roomSize/2-1, ce-m_roomSize/2);

    for(int r = rs; r < re; ++r)
    {
        setRock(r, cc);
    }

    return cc;
}

void GameMapRecrusive::setRock(int r, int c)
{
    m_objects[r][c]->clear();
    ValueMap data;
    data["type"] = "Rock";
    m_objects[r][c]->pushObjBy(data);
}

void GameMapRecrusive::setSoil(int r, int c, bool cls)
{
    if(cls)
        m_objects[r][c]->clear();

    ValueMap data;
    data["type"] = "Soil";
    data["texture"] = cstr("soil%d.png", rand()%2);
    m_objects[r][c]->pushObjBy(data);
}

void GameMapRecrusive::setMouth(int r, int c, bool allowTrap)
{
    if(r<0 || r>=m_mapRows || c<0 || c>=m_mapCols)
        return;

    ValueMap data;

    if(!allowTrap)
    {
        data["type"] = "Soil";
        data["texture"] = cstr("soil%d.png", rand()%2);
    }
    else
    {
        int percent = rand()%100;

        if(percent<80)
        {
            data["type"] = "Soil";
            data["texture"] = cstr("soil%d.png", rand()%2);
        }
        else if(percent<85)
        {
            if(canPlaceDoorMonster(r, c))
            {
                data["type"] = "LockedDoor";
            }
            else
            {
                return;
            }
        }
        else if(percent<90)
        {
            if(canPlaceDoorMonster(r, c))
            {
                data["type"] = "Monster";
                data["texture"] = cstr("monster%d.png", rand()%2);
            }
            else
            {
                m_objects[r][c]->clear();
                return;
            }
        }
        else
        {
            m_objects[r][c]->clear();
            return;
        }
    }

    m_objects[r][c]->clear();
    m_objects[r][c]->pushObjBy(data);
}

bool GameMapRecrusive::canPlaceDoorMonster(int r, int c)
{
    if(r<=0 || r>=m_mapRows-1 || c<=0 || c>=m_mapCols-1)
        return false;

    if(m_objects[r][c-1]->getAStarCost()==ObjAttr::AStarMax &&
            m_objects[r][c+1]->getAStarCost()==ObjAttr::AStarMax &&
            m_objects[r-1][c]->getAStarCost()<ObjAttr::AStarMax &&
            m_objects[r+1][c]->getAStarCost()<ObjAttr::AStarMax
      )
    {
        return true;
    }
    else if(m_objects[r-1][c]->getAStarCost()==ObjAttr::AStarMax &&
            m_objects[r+1][c]->getAStarCost()==ObjAttr::AStarMax &&
            m_objects[r][c-1]->getAStarCost()<ObjAttr::AStarMax &&
            m_objects[r][c+1]->getAStarCost()<ObjAttr::AStarMax
           )
    {
        return true;
    }

    return false;
}

void GameMapRecrusive::setTrap(int r, int c)
{
    ValueMap data;
    data["type"] = rand()%2?"TrapFire":"TrapBomb";
    m_objects[r][c]->clear();
    m_objects[r][c]->pushObjBy(data);
	if (rand()%100<80)
	{
		setSoil(r, c, false);
	}
    m_mineCount--;
}

void GameMapRecrusive::setProp(int r, int c)
{
    string candy[] =
    {
        "heart.png", "shield.png", "key.png", "arrow.png", "hoe.png", "bomb.png", "map.png"
    };
    ValueMap val;
    val["type"] = "Prop";
    val["texture"] = candy[ rand()%7 ];
    m_objects[r][c]->clear();
    m_objects[r][c]->pushObjBy(val);
    m_propCount--;

    if(rand()%100<95)
    {
        setSoil(r, c, false);
    }

    m_propCount--;
}

void GameMapRecrusive::setCoin(int r, int c)
{
    ValueMap val;
    val["type"] = "Coin";

    if(rand()%100<60)
    {
        val["coin"] = 10;
    }
    else if(rand()%100<70)
    {
        val["coin"] = 50;
    }
    else if(rand()%100<80)
    {
        val["coin"] = 100;
    }
    else
    {
        m_coinCount--;
        return;
    }

    m_objects[r][c]->clear();
    m_objects[r][c]->pushObjBy(val);

    if(rand()%100<80)
    {
        setSoil(r, c, false);
    }

    m_coinCount--;
}
