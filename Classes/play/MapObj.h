#pragma once

#include "play_shared.h"
#include "SoundMgr.h"

class ObjAttr
{
public:
    ObjAttr();
    
    bool isTrap();
	void setTrap(bool trap);
    
    bool canUseHoe();
	bool canUseBomb();
	bool canUseMap();
	bool canUseFlag();

	void setUseHoe(bool use);
	void setUseBomb(bool use);
	void setUseMap(bool use);
	void setUseFlag(bool use);
    
	enum AStarLevel
	{
		AStarMin = 0,
// 		AStarLevel1 = 100,
// 		AStarLevel2 = 150,
		AStarMax = INT_MAX
	};
    int AStarCost();
	void setAStarCost(AStarLevel val);
private:
	//m_attr��������5λ�ֱ���5�����ԣ�����δ�á�
	int m_attr;
	int m_astar;
};

class Player;
class MapCell;
class MapObj
	: public Sprite
{
public:
	MapObj(void);
	virtual ~MapObj(void);

    
	static MapObj* create(const string& type, const ValueMap& cfg);

	/*
	 *	����init֮�󱻵���
	 */
	virtual void config(const ValueMap& cfg);

	/*
	 *	Player��Ҫ̤�ϴ�Obj֮ǰ�ᱻ����
	 *	����true��ʾ���Խ�����һ��
	 *	����false��ʾ�����Խ�����һ��
	 */
	virtual bool willPlayerEnter(Player* player);

	/*
	 *	Player�ߵ�һ��ʱ�ᱻ����
	 *	����true��ʾ���Խ�����һ��
	 *	����false��ʾ�����Խ�����һ��
	 */
	virtual bool onPlayerSteping(Player* player);

	/*
	 *	Player��ɱ�����������ʱ������
	 *	��Ҫע�⵱Player��ɱ�������ʱ����һ����ͣ��Ŀ��obj�ĸ�����
	 *	�����Ƿ��������
	 *	����false��obj����ɾ��
	 */
	virtual bool onPlayerFinished(Player* player);

	/*
	 *	��Player�����MapObj�Ա�ʱ�����ã���������ʱ�����ڵݹ���չ�ڿ�MapObj
	 */
	virtual bool onPlayerSurround(Player* player);

	virtual ObjAttr getAttr();

private:
	MapCell* m_pParentCell;
public:
	void setParentCell(MapCell* pCell);
	MapCell* getParentCell();
};

