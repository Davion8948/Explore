#pragma once

#include "play_shared.h"
#include "Player.h"

class Player;
class MapCell;
enum MoveStatus;
class GameMap
	: public Node
{
public:
	GameMap(void);
	virtual ~GameMap(void);

	static GameMap* create(int mainLevel, int viceLevel);

	//cocos-coordinate
	void onClick(const Point& pt);
	void onLongTouches(const Point& pt);
	
	/*
	 *	返回true表示成功执行
	 */
	bool onEffectHoe();
	bool onEffectBomb();
	bool onEffectMap();

protected:

	typedef std::pair<int, int> Index2;

	virtual void makeMap(int mLevel, int vLevel) = 0;
// 	virtual Index2 makePlayer() = 0;
// 	virtual Index2 makeStair() = 0;

protected:
	/*
	 *	generate map
	 */
	virtual bool initWithLevel(int mainLevel, int viceLevel);

	/*
	 *	point-coordinate to vertex-coordinate
	 *	Index2(0,0)==left_bottom(0,0)
	 */
	Point index2ToPoint(const Index2& index);
	Index2 pointToIndex2(const Point& point);

	list<Index2> getPath(const Index2& from, const Index2& to);
	int loss(const Index2& arg1, const Index2& arg2);

	void stepPlayer();
	void onPlayerFinishOneStep(const Index2& index, MoveStatus ms);

	std::vector<Index2> getSurrounding(const Index2& center, int radius = 1);
	void dig(const Index2& center);

protected:
	const float m_tw;//tile width
	const float m_th;//tile height
//	const Size m_border;

	typedef vector<MapCell*> MapRow;
	typedef vector<MapRow> TotalMap;
	TotalMap m_objects;

	Player* m_pPlayer;

private:
	list<Index2> m_curPath;
	bool m_restartPlayer;
	Point m_playerTarget;

	bool m_bUsingHoe;
	bool m_bUsingBomb;
	bool m_bUsingMap;
};

