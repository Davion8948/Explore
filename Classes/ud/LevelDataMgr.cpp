#include "LevelDataMgr.h"
#include "cocos2d.h"

USING_NS_CC;

LevelDataMgr::LevelDataMgr()
{
    m_mainLevel = UserDefault::getInstance()->getIntegerForKey("mLevel", 0);
	m_viceLevel = UserDefault::getInstance()->getIntegerForKey("vLevel", 0);
}

LevelDataMgr::~LevelDataMgr()
{
	UserDefault::getInstance()->setIntegerForKey("mLevel", m_mainLevel);
	UserDefault::getInstance()->setIntegerForKey("vLevel", m_viceLevel);
}

void LevelDataMgr::setMainLevel(int val)
{
    m_mainLevel = val;
}

int LevelDataMgr::getMainLevel()
{
    return m_mainLevel;
}

void LevelDataMgr::setViceLevel(int val)
{
    m_viceLevel = val;
}

int LevelDataMgr::getViceLevel()
{
    return m_viceLevel;
}

int LevelDataMgr::getMainLevelCount()
{
    return 7;
}

int LevelDataMgr::getViceLevelCount()
{
    return 10;
}

bool LevelDataMgr::isUnlock( int mainLevel )
{

	return mainLevel==0;
}
