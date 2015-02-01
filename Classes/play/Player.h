#pragma once

#include "MapCell.h"
#include "GameState.h"

enum MoveStatus
{
	msCanotMove,
	msMoveThenBack,
	msFullyFinish
};


class Player
	: public Sprite
	, public GameStateListener
{
public:
	Player(void);
	virtual ~Player(void);

	CREATE_FUNC(Player);

	virtual bool init();
	virtual void onStateChanged(GameState gs) override;

 	void stepTo(const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish);

	void showTip(const std::string& tip_name);
	void hideTip();

protected:
	void stepMid(const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish);
 	void backToLastPos();

	void initWithPlayerName(const string& name);

	enum Direction
	{
		d_up, d_ur, d_right, d_rd, d_down, d_dl, d_left, d_lt
	};

	Direction getDirection(const Point& start, const Point& end);
private:
	string m_player;
};

