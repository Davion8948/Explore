#pragma once
#include "loading/loading_shared.h"
using namespace ui;
typedef cocos2d::ui::Widget::TouchEventType TouchType;
class ExitLayer :
	public Layer
{
public:
	ExitLayer(void);
	~ExitLayer(void);
	CREATE_FUNC(ExitLayer);
	virtual bool init();
private:
	void onClickCancel(Ref *ref, TouchType type);
	void onClickOk(Ref *ref, TouchType type);
};

