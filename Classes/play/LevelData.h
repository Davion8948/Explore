/*
 *	�������ǰ�ص���Ϣ����ÿ�����¿�ʼһ�ص�ʱ��ᱻ����
 */
#pragma once

#include "play_shared.h"
#include "EncryptValue.h"

class LevelData
	: public Singleton<LevelData>
{
public:
	LevelData();

	void reset(int level);

	int getCurLevel();

	int getElapsedTime();

	void addCollectedCoin(int val);
	int getCollectedCoin();

	void addDestroyedTrap(int val);
	int getDestroyedTrap();

	void addKilledMonster(int val);
	int getKilledMonster();

	void addOpenedDoor(int val);
	int getOpenedDoor();
	
private:
	EVI m_curLevel;

	EVI m_initialTime;
	EVI m_collectedCoin;

	EVI m_destroyedTrap;
	EVI m_killedMonster;
	EVI m_openedDoor;
};
