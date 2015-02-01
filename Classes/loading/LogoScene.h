#pragma once
#include "loading_shared.h"
class LogoScene
	:public Scene
{
public:
	LogoScene(void);
	~LogoScene(void);
	CREATE_FUNC(LogoScene);
	virtual bool init();
};

