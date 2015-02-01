#pragma once

#include "GameMap.h"

class GameMapRecrusive
	: public GameMap
{
	friend GameMap* GameMap::create(int mainLevel, int viceLevel);

protected:
	GameMapRecrusive(void);
	virtual ~GameMapRecrusive(void);

protected:
	virtual void makeMap(int mLevel, int vLevel) override;

private:
	void generate(int rs, int cs, int re, int ce);
	int generateRow(int rs, int cs, int re, int ce);
	int generateCol(int rs, int cs, int re, int ce);

	void setRock(int r, int c);
	void setSoil(int r, int c, bool cls);
	void setMouth(int r, int c);
	void setTrap(int r, int c);
	void setProp(int r, int c);
	void setCoin(int r, int c);

	bool canPlaceDoorMonster(int r, int c);

private:
	int m_mapRows;
	int m_mapCols;

	int m_roomSize;//ÿ��С�������С�ߴ�

	int m_mineCount;
	int m_coinCount;
	int m_propCount;

	int m_hallMin;

	/*
	 *	��¼�����Ѿ������ķ���λ��
	 *	��������������غϵģ�����Ϊ��һ������
	 *	m_roomCounter: start_index2end_index
	 */
	map<Index2, Index2> m_roomCounter;
};

