#pragma once
#include "play_shared.h"

class PlayScene 
	: public Scene
{
public:
	PlayScene(void);
	virtual ~PlayScene(void);

	CREATE_FUNC(PlayScene);

	virtual bool init() override;

	void setIntent(const cocos2d::ValueMap& intent);
	cocos2d::ValueMap getIntent() const;

private:
	ValueMap m_intent;
};

