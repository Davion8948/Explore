#pragma once

#include "MapObj.h"

class MapCell
	: public Sprite
{
public:
	MapCell(void);
	virtual ~MapCell(void) override;

	CREATE_FUNC(MapCell);

	virtual bool init() override;

	void pushObjBy(const cocos2d::ValueMap& data);
	void clear();
	bool empty();

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

	void playTopEffect(Node* node);
private:
	void refreshDisplay(); 
private:
	/*
	 *	�б�ǰ����������
	 */
	list<MapObj*> m_objs;

	Label* m_pDisplayNumber;
	int m_surroundMineCount;

	bool m_isMine;
	bool m_isFlagged;
};

