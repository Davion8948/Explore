#pragma once

#include "play_shared.h"
#include "Player.h"

class Player;
class MapCell;
enum MoveStatus;
class GameMap
	: public TMXTiledMap
{
public:
	GameMap(void);
	virtual ~GameMap(void);

	static GameMap* create(const std::string& tmxFile);

	//TMXTiledMap坐标系
	void onClick(const Point& pt);
	void onLongTouches(const Point& pt);
	
	void onEffectHoe();
	void onEffectBomb();
	void onEffectMap();
protected:
	virtual bool initWithTMXFile(const std::string& tmxFile);

	//相对于本地的坐标转换
	typedef std::pair<int,int> Index2;
	Index2 tmxToIndex2(const Point& pt);
	Point index2ToTMX(const Index2& index);
	Point cocosToTMX(Point pt);//转换y的方向
	Point tmxToCocos(Point pt);

	list<Index2> getPath(const Index2& from, const Index2& to);

	void stepPlayer();
	void onPlayerFinishOneStep(const Index2& index, MoveStatus ms);

	std::vector<Index2> getSurrounding(const Index2& center, int radius = 1);
	void dig(const Index2& center);

	void onKeyDown(EventKeyboard::KeyCode, Event*);
private:
	typedef vector<MapCell*> MapRow;
	typedef vector<MapRow> TotalMap;
	TotalMap m_objects;

	Player* m_pPlayer;

	list<Index2> m_curPath;
	bool m_restartPlayer;
	Point m_playerTarget;

	float m_tw;//tile width
	float m_th;//tile height

	bool m_bUsingHoe;
	bool m_bUsingBomb;
	bool m_bUsingMap;
};

