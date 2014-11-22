#pragma once

#include "MapObj.h"
// 
// enum CellState
// {
// 	tNone = 0,
// 	tTrap = 1,
// 	tBlock = 2,
// };
// #define Is_Trap(x) ((x)&tTrap)
// #define Is_Block(x) ((x)&tBlock)
// #define Can_Expand(x) ( Is_Block(x)&&(!Is_Trap(x)) )

class MapCell
	: public Sprite
{
public:
	MapCell(void);
	virtual ~MapCell(void) override;

	CREATE_FUNC(MapCell);

	virtual bool init() override;

	void pushObjBy(const cocos2d::ValueMap& data);

	bool isMine();
	void setSurroundMineCount(int num);
	void onFlagged();

	/*
	 *	��player�˶���صļ�������
	 */
	bool checkPlayerEnter(Player* player);
	bool checkPlayerSteping(Player* player);
	void checkPlayerFinished(Player* player);
	void checkDig(Player* player);

	/*
	 *	start_or_end true��ʾ��ʼִ�У�false��ʾ����ִ��
	 *	bUse �û��Ƿ����˵�ǰ����
	 *	����true��ʾִ�гɹ���false��ʾִ��ʧ�ܡ�
	 */
	bool onEffectHoe(bool start_or_end, bool bUse);
	bool onEffectBomb(bool start_or_end, bool bUse);
	bool onEffectMap(bool start_or_end);

	int getAStarCost();
private:
	void refreshDisplay(); 
private:
	list<MapObj*> m_objs;
	Label* m_pDisplayNumber;
	int m_surroundMineCount;
	bool m_isMine;
	bool m_isFlagged;
};

