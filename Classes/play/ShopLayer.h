#include "play_shared.h"

class ShopLayer
	: public Layer
{
public:
	CREATE_FUNC(ShopLayer);

	virtual bool init() override;

protected:
	void onBtnBuy(Ref*, ui::Widget::TouchEventType);
	void onBtnBack(Ref*, ui::Widget::TouchEventType);
	void onBtnContinue(Ref*, ui::Widget::TouchEventType);
private:
};