#pragma once

#include "play_shared.h"

class Player;
class MapObj
	: public Sprite
{
public:
	MapObj(void);
	virtual ~MapObj(void);

	static MapObj* create(const string& name);

	/*
	 *	将在init之后被调用
	 */
	virtual void config(const cocos2d::ValueMap& cfg);

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
	 *	当Player在这个MapObj旁边时被调用，但现在暂时被用于递归拓展MapObj
	 */
	virtual bool onPlayerSurround(Player* player);

	/*
	 *	是否可在其上使用道具
	 */
	virtual bool canUseHoe();
	virtual bool canUseBomb();
	virtual bool canUseMap();
	virtual bool canUseFlag();

	virtual bool canAStar();
private:
	int m_row;
	int m_col;
};

