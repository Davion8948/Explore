#pragma once
#include "play_shared.h"
#include "GameState.h"

class GameMap;
class Player;

class MainLayer
	: public Layer
	, public GameStateListener
{
public:
	MainLayer(void);
	virtual ~MainLayer(void);

	CREATE_FUNC(MainLayer);

	virtual bool init();

	virtual void onStateChanged(GameState gs) override;

	void startLevel(int level);

protected:

	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);

	//返回相对于GameMap左上角的坐标，纵坐标向下
	Point convertToTileCoordinate(Point pt);

	//level base-0
	
private:
	void startLevelImpl(int level);
private:
// 	GameMap* m_pMap;
};

