#pragma once

#include "GameMap.h"

class GameMapRoom
	: public GameMap
{
	friend GameMap* GameMap::create(int mainLevel, int viceLevel);

protected:
	GameMapRoom(void);
	virtual ~GameMapRoom(void);

protected:
	virtual void makeMap(int mLevel, int vLevel) override;

private:
	void generateRecursive(int rs, int cs, int re, int ce);
	void generateBound();
	void generateRoom(int r, int c, int w, int h);
	void generateProp(int r, int c);
	void generateTrap(int r, int c);
	void generateCoin(int r, int c);
	//void generateEmpty(int r, int c);
	void generateFeature(int r, int c);
	void generateRock(int r, int c);
	void generateHole(int r, int c);

	void fillBound(int rs, int cs, int re, int ce, const ValueMap& val);
	void clearBound(int rs, int cs, int re, int ce);
private:
	int m_mapRows;
	int m_mapCols;

	int m_roomNum;//���ŵ�ͼ��Ҫ��������С����
	int m_roomSize;//ÿ��С��������ߴ�

	int m_mineMax;
	int m_coinMax;
	int m_propMax;

	int m_hallMin;

	/*
	 *	��¼�����Ѿ������ķ���λ��
	 *	��������������غϵģ�����Ϊ��һ������
	 *	m_roomCounter: start_index2end_index
	 */
	map<Index2, Index2> m_roomCounter;
};

