#pragma once
#include "play/play_shared.h"
class MainLevelScene
	:public Scene
{
public:
	MainLevelScene(void);
	~MainLevelScene(void);
	CREATE_FUNC(MainLevelScene);
	virtual bool init() override;
};

