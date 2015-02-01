#pragma once
#include "play_shared.h"
#include "GameState.h"

class GameMap;
class Player;
class ShopLayer;

class MainLayer
	: public Layer
	, public GameStateListener
{
public:
	MainLayer(void);
	virtual ~MainLayer(void);

	CREATE_FUNC(MainLayer);

	virtual bool init();

	virtual void update(float delta) override;

	virtual void onStateChanged(GameState gs) override;

	void setMainLevel(int level);
	void startViceLevel(int level);
	void startNextLevel();
	void restartCurrentLevel();
	int getCurrentLevel();

	// UI 部分
	void popLayer(Layer* layer);
	void removeTopLayer();
	Layer* getTopLayer();
protected:

	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//返回相对于GameMap左上角的坐标，纵坐标向下
	Point convertToTileCoordinate(Point pt);

	void lazyInitAnimation(bool in_or_out);
	
private:
	void startViceLevelImpl(int level);

private:
	float m_longTouchingTimeCount;
	Point m_touchingPoint;

	list<Layer*> m_uiLayers;

	int m_mLevel;
	int m_vLevel;
};

