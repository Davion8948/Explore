#pragma once
#include "loading/loading_shared.h"
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
	void popLayer(Layer *layer);
	void removeTopLayer();
	Layer* getTopLayer();
protected:
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
private:
	Button *settingBtn;
	Button *volumeBtn;
	Button *infoBtn;
	Button *trophyBtn;
	Button *wechatBtn;
	Button *weiboBtn;
	Slider *volumeSilder;
	void onClickPlay(Ref* target, TouchType type);
	void onClickSetting(Ref *target,TouchType type);
	void onClickVolume(Ref *target,TouchType type);
	void onClickInfo(Ref *target,TouchType type);
	void onClickTrophy(Ref *target, TouchType type);
	void onClickSlide(Ref *pSender, ui::Slider::EventType type);
	void onClickWechat(Ref *target, TouchType type);
	void onClickWeibo(Ref *target, TouchType type);
	bool openSetting;//if open setting
	bool openTrophy;
	bool ifShowSlider;// volume slider
	list<Layer*> mLayers;
};

