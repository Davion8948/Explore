#pragma once
#include "loading_shared.h"
class LogoLayer
	: public Layer
{
public:
	LogoLayer(void);
	~LogoLayer(void);
	CREATE_FUNC(LogoLayer);
	virtual bool init();
	void logoEnd(float dt);
	Sprite *logoSp;
};

