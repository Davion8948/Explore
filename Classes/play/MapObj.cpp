#include "MapObj.h"


MapObj::MapObj(void)
	:m_row(0)
	,m_col(0)
{
}


MapObj::~MapObj(void)
{
}

MapObj* MapObj::create( const string& name )
{
	MapObj* obj = DynamicCreation::createCast<MapObj*>(name);
	if (obj && obj->init())
	{
		obj->autorelease();
		return obj;
	}
	delete obj;
	return nullptr;
}

void MapObj::config( const cocos2d::ValueMap& cfg )
{
	string texture;
	safe_assign(texture, cfg, "texture");
	if (!texture.empty())
		initWithFile(texture);

	float rotate = 0;
	safe_assign(rotate, cfg, "rotate");
	setRotation(rotate);

// 	float x=0, y=0, w=0, h=0;
// 	safe_assign(w, cfg, "width");
// 	safe_assign(h, cfg, "height");	
}

bool MapObj::willPlayerEnter(Player* player)
{
	return true;
}

bool MapObj::onPlayerSteping(Player* player)
{
	return true;
}

bool MapObj::onPlayerFinished(Player* player)
{
	return true;
}

bool MapObj::onPlayerSurround(Player* player)
{
	return true;
}

bool MapObj::canUseHoe()
{
	return false;
}

bool MapObj::canUseBomb()
{
	return false;
}

bool MapObj::canUseMap()
{
	return false;
}

bool MapObj::canUseFlag()
{
	return false;
}

bool MapObj::canAStar()
{
	return false;
}

// 
// int MapObj::row() const
// {
// 	return m_row;
// }
// 
// int MapObj::col() const
// {
// 	return m_col;
// }
// 
// void MapObj::setRow( int row )
// {
// 	m_row = row;
// }
// 
// void MapObj::setCol( int col )
// {
// 	m_col = col;
// }
// 
