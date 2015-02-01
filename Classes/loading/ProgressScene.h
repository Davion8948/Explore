#pragma once
#include "loading_shared.h"
class ProgressScene
	:public Scene
{
public:
	ProgressScene(void);
	~ProgressScene(void);
	CREATE_FUNC(ProgressScene);
	virtual bool init();
};

