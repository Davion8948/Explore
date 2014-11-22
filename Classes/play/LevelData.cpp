#include "LevelData.h"
#include "UDWhenPlay.h"

LevelData::LevelData()
{
	reset(-1);
}

void LevelData::reset(int level)
{
	m_curLevel = level;
	m_initialTime = time(0);
	m_collectedCoin = 0;
	m_destroyedTrap = 0;
	m_killedMonster = 0;
	m_openedDoor = 0;
}

int LevelData::getCurLevel()
{
	return m_curLevel;
}

int LevelData::getElapsedTime()
{
	return time(0)-m_initialTime;
}

void LevelData::addCollectedCoin( int val )
{
	m_collectedCoin += val;
}

int LevelData::getCollectedCoin()
{
	return m_collectedCoin;
}

void LevelData::addDestroyedTrap( int val )
{
	m_destroyedTrap += val;
}

int LevelData::getDestroyedTrap()
{
	return m_destroyedTrap;
}

void LevelData::addKilledMonster( int val )
{
	m_killedMonster += val;
}

int LevelData::getKilledMonster()
{
	return m_killedMonster;
}

void LevelData::addOpenedDoor( int val )
{
	m_openedDoor += val;
}

int LevelData::getOpenedDoor()
{
	return m_openedDoor;
}
