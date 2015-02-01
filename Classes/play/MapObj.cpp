#include "MapObj.h"


ObjAttr::ObjAttr()
	:m_attr(0)
	,m_astar(0)
{
// 	setTrap(false);
// 	setUseHoe(false);
// 	setUseBomb(false);
// 	setUseMap(false);
// 	setUseFlag(false);
}

bool ObjAttr::isTrap()
{
	return m_attr&0x01;
}

void ObjAttr::setTrap(bool trap)
{
	m_attr |= trap?0x01:0x00;
}

bool ObjAttr::canUseHoe()
{
	return m_attr>>1&0x01;
}

bool ObjAttr::canUseBomb()
{
	return m_attr>>2&0x01;
}

bool ObjAttr::canUseMap()
{
	return m_attr>>3&0x01;
}

bool ObjAttr::canUseFlag()
{
	return (m_attr&0x0F)!=0;
}

void ObjAttr::setUseHoe(bool use)
{
	m_attr |= use?0x02:0x00;
}
void ObjAttr::setUseBomb(bool use)
{
	m_attr |= use?0x04:0x00;
}
void ObjAttr::setUseMap(bool use)
{
	m_attr |= use?0x08:0x00;
}
void ObjAttr::setUseFlag(bool use)
{
	m_attr |= use?0x0F:0x00;
}

int ObjAttr::AStarCost()
{
	return m_astar;
}
void ObjAttr::setAStarCost(AStarLevel val)
{
	m_astar = val;
}
//////////////////////////////////////////////////////////////////////////
//
MapObj::MapObj(void)
	:m_pParentCell(nullptr)
{
}


MapObj::~MapObj(void)
{
}

MapObj* MapObj::create( const string& type, const ValueMap& cfg )
{
	MapObj* obj = DynamicCreation::createCast<MapObj*>(type);
	if (obj && obj->init())
	{
		obj->autorelease();
        obj->config(cfg);
		return obj;
	}
	delete obj;
	return nullptr;
}

void MapObj::config( const ValueMap& cfg )
{
	string texture;
	safe_assign(texture, cfg, "texture");
	if (!texture.empty())
		initWithFile(texture);
// 
// 	string animation;
// 	safe_assign(animation, cfg, "animation");
//     if(!animation.empty())
//     {
//         Animation* ani = AnimationCache::getInstance()->getAnimation(animation);
//         CCAssert(ani, "");
//         runAction( Animate::create(ani) );
//     }
// 	setAnchorPoint(Point(0,1));
	Size tmp = getContentSize()/2;
	setPosition(tmp.width, -tmp.height);
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

ObjAttr MapObj::getAttr()
{
	return ObjAttr();
}

void MapObj::setParentCell( MapCell* pCell )
{
	m_pParentCell = pCell;
}

MapCell* MapObj::getParentCell()
{
	return m_pParentCell;
}
