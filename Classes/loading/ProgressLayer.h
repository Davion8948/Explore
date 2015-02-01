#pragma once
#include "loading_shared.h"
class ProgressLayer
	:public Layer
{
public:
	ProgressLayer(void);
	~ProgressLayer(void);
	CREATE_FUNC(ProgressLayer);
	virtual bool init();
	 void update(float dt);
	void loadResource();
private: 
	float count;
};

