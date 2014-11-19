#pragma once

#include "MapCell.h"

enum MoveStatus
{
	msCanotMove,
	msMoveThenBack,
	msFullyFinish
};


class Player
	: public Sprite
{
public:
	Player(void);
	virtual ~Player(void);

	CREATE_FUNC(Player);

	virtual bool init();

 	void stepTo(const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish);

	void showTip(Sprite* tip);
protected:
	void stepMid(const Point& dst, MapCell* cell, std::function<void(MoveStatus)> whenFinish);
 	void backToLastPos();

protected:
	void initWithPlayerName(const string& name);

	enum Direction
	{
		d_up, d_right, d_down, d_left
	};
private:
	string m_player;
};

