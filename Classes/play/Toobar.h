#pragma once

#include "play_shared.h"

class Toolbar : public Layer
{
public:
	Toolbar();
	virtual ~Toolbar() override;

	CREATE_FUNC(Toolbar);

	virtual bool init() override;

	friend class UDWhenPlay;

private:
	void setClover(int val);
	void setCoin(int val);

	enum PropType
	{
		prop_heart = 0,
		prop_shield = 1,
		prop_key = 2,
		prop_arrow = 3,
		prop_hoe = 4,
		prop_bomb = 5,
		prop_map = 6,
		prop_count = 7
	};
	void setProperty(PropType prop_tag, int val);

private:
	void refreshDisplay();
	
	void onClickHoe(Ref* target, cocos2d::ui::Widget::TouchEventType type);
	void onClickBomb(Ref* target, cocos2d::ui::Widget::TouchEventType type);
	void onClickMap(Ref* target, cocos2d::ui::Widget::TouchEventType type);
private:
	struct UIStorage
	{
		Node* pUI;
		cocos2d::ui::TextAtlas* pText;
	};
	UIStorage m_ui[prop_count];

	cocos2d::ui::Button* m_pCloverBtn;
	cocos2d::ui::TextAtlas* m_pCoinNum;

	//cocos2d::ui::Button* m_pMap;
	//cocos2d::ui::Button* m_pBomb;
};
