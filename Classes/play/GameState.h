#pragma once
#include "cex/Observer.h"
#include "cex/Singleton.h"

enum GameState
{
	gs_none,
	gs_prepare,
	gs_playing,
	gs_dead,
	gs_win
};

class GameStateListener
{
public:
	GameStateListener();
	virtual ~GameStateListener();
	virtual void onStateChanged(GameState gs) = 0;
};

class GameStateMgr
	: public cex::Monitor<GameStateListener, GameState>
	, public cex::Singleton<GameStateMgr>
{
public:
	GameStateMgr();

	/*
	 *	notify 是否通知其它对象状态已经改变，有时候需要悄悄改变程序状态
	 */
	void change(GameState gs, bool notify = true);

	GameState curState() const;
	GameState lastState() const;

private:
	GameState m_curState;
	GameState m_lastState;
};
