#pragma once
#include "loading/loading_shared.h"

class LoadingScene 
	: public Scene
{
public:
	LoadingScene(void);
	virtual ~LoadingScene(void);
	CREATE_FUNC(LoadingScene);
	virtual bool init() override;
};

