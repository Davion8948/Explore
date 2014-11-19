#pragma once

#include "MapObj.h"

enum CellState
{
	tNone = 0,
	tTrap = 1,
	tBlock = 2,
};
#define Is_Trap(x) ((x)&tTrap)
#define Is_Block(x) ((x)&tBlock)
#define Can_Expand(x) ( Is_Block(x)&&(!Is_Trap(x)) )

class MapCell
	: public Sprite
{
public:
	MapCell(void);
	virtual ~MapCell(void) override;

	CREATE_FUNC(MapCell);

	virtual bool init();

	void addBy(const cocos2d::ValueMap& data);

	bool checkPlayerEnter(Player* player);
	bool checkPlayerSteping(Player* player);
	void checkPlayerFinished(Player* player);
	void onPlayerSurround(Player* player);

	void push_top(MapObj*);
	void remove(MapObj*);

	int getSurroundMineCount() const;
	void setSurroundMineCount(int num);

	CellState getState() const;

	void onEffectHoe(bool start_or_end, bool bUse);
	void onEffectBomb(bool start_or_end, bool bUse);
	void onEffectMap(bool start_or_end);
private:
	void refreshDisplay(); 
private:
	list<MapObj*> m_objs;
	Label* m_pDisplayNumber;
	int m_surroundMineCount;

	int m_type;//为了方便运算，所以定义成int
};

