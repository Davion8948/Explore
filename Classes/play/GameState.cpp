#include "GameState.h"


GameStateListener::GameStateListener()
{
	GameStateMgr::inst().addListener(this);
}

GameStateListener::~GameStateListener()
{
	GameStateMgr::inst().removeListener(this);
}

//////////////////////////////////////////////////////////////////////////
GameStateMgr::GameStateMgr()
	:m_curState(gs_none)
	,m_lastState(gs_none)
{

}

void GameStateMgr::change( GameState gs, bool notify /* = true*/ )
{
	m_lastState = m_curState;
	m_curState = gs;
	if (notify)
	{
		this->notifyStateChanged(gs);
	}
}

GameState GameStateMgr::curState() const
{
	return m_curState;
}

GameState GameStateMgr::lastState() const
{
	return m_lastState;
}
