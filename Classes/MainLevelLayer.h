#pragma once
#include "play/play_shared.h"
class MainLevelLayer
	:public Layer
{
public:
	MainLevelLayer(void);
	~MainLevelLayer(void);
	CREATE_FUNC(MainLevelLayer);
	virtual bool init();
	void onClickLevel(Ref *target, cocos2d::ui::Widget::TouchEventType type);
};

