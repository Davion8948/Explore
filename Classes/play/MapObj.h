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
	 *	����init֮�󱻵���
	 */
	virtual void config(const cocos2d::ValueMap& cfg);

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
	 *	��Player�����MapObj�Ա�ʱ�����ã���������ʱ�����ڵݹ���չMapObj
	 */
	virtual bool onPlayerSurround(Player* player);

	/*
	 *	�Ƿ��������ʹ�õ���
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

