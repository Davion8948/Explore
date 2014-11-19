#pragma once
#include "play/play_shared.h"
class LoadingLayer :
	public Layer
{
public:
	LoadingLayer(void);
	virtual ~LoadingLayer(void) override;
	CREATE_FUNC(LoadingLayer);
	virtual bool init();
private	:
	void onClickPlay(Ref* target, cocos2d::ui::Widget::TouchEventType type);
};

