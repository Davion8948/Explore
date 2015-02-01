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
	//m_attr从右向左5位分别是5个属性，其它未用。
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
	 *	将在init之后被调用
	 */
	virtual void config(const ValueMap& cfg);

	/*
	 *	Player将要踏上此Obj之前会被调用
	 *	返回true表示可以进行下一步
	 *	返回false表示不可以进行下一步
	 */
	virtual bool willPlayerEnter(Player* player);

	/*
	 *	Player走到一半时会被调用
	 *	返回true表示可以进行下一步
	 *	返回false表示不可以进行下一步
	 */
	virtual bool onPlayerSteping(Player* player);

	/*
	 *	Player完成本次行走任务时被调用
	 *	需要注意当Player完成本次任务时，不一定会停在目标obj的格子上
	 *	返回是否继续存在
	 *	返回false此obj将被删除
	 */
	virtual bool onPlayerFinished(Player* player);

	/*
	 *	当Player在这个MapObj旁边时被调用，但现在暂时被用于递归拓展挖开MapObj
	 */
	virtual bool onPlayerSurround(Player* player);

	virtual ObjAttr getAttr();

private:
	MapCell* m_pParentCell;
public:
	void setParentCell(MapCell* pCell);
	MapCell* getParentCell();
};

