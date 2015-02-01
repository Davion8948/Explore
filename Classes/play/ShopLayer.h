#include "play_shared.h"

class ShopLayer
	: public Layer
{
public:
	CREATE_FUNC(ShopLayer);

	virtual bool init() override;
	virtual void onExit() override;

protected:
	void onBtnBuy(Ref*, ui::Widget::TouchEventType);
	void onBtnContinue(Ref*, ui::Widget::TouchEventType);
	void onBtnRandom(Ref*, ui::Widget::TouchEventType);
	void onBtnGetCoin(Ref*, ui::Widget::TouchEventType);
private:
	vector<ui::Button*> m_btns;
	bool m_bRandoming;
};