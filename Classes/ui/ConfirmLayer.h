#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ConfirmLayer
	: public cocos2d::Layer
{
public:
	ConfirmLayer();
	virtual ~ConfirmLayer();

	//CREATE_FUNC(ConfirmLayer);
	static ConfirmLayer* create(const char* tipID, std::function<void(void)> ok=nullptr, std::function<void(void)> cancel=nullptr);

	virtual bool init() override;

	/*
	 *	tipID是.xml文件里文字的key
	 */
	void setTipFromID(const char* tipID);

	std::function<void(void)> onOk;
	std::function<void(void)> onCancel;

private:
	void onBtnOk(Ref*, cocos2d::ui::Widget::TouchEventType type);
	void onBtnCancel(Ref*, cocos2d::ui::Widget::TouchEventType type);

private:
	cocos2d::ui::Text* m_pTipText;
};
