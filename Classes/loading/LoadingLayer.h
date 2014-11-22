#pragma once
#include "play/play_shared.h"
using namespace ui;
typedef cocos2d::ui::Widget::TouchEventType TouchType;

class LoadingLayer :
	public Layer
{
public:
	LoadingLayer(void);
	virtual ~LoadingLayer(void) override;
	CREATE_FUNC(LoadingLayer);
	virtual bool init();
private	:
	Button *settingBtn;
	Button *volumeBtn;
	Button *infoBtn;
	Button *trophyBtn;
	Button *wechatBtn;
	Button *weiboBtn;
	void onClickPlay(Ref* target, TouchType type);
	void onClickSetting(Ref *target,TouchType type);
	void onClickVolume(Ref *target,TouchType type);
	void onClickInfo(Ref *target,TouchType type);
	void onClickTrophy(Ref *target, TouchType type);
	bool openSetting;//if open setting
	bool openTrophy;
};

