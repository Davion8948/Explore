#pragma once
#include "loading/loading_shared.h"
class MainLevelScene
	:public Scene
{
public:
	MainLevelScene(void);
	~MainLevelScene(void);
	CREATE_FUNC(MainLevelScene);
	virtual bool init() override;
	void setIntent(const cocos2d::ValueMap &intent);
	cocos2d::ValueMap getIntent();
	cocos2d::ValueMap mIntent;
};

