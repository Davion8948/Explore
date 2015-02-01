#include "play_shared.h"

class FinishLayer
	: public Layer
{
public:
	CREATE_FUNC(FinishLayer);

	virtual bool init();

	virtual void onEnter();

protected:
	void onBtnReturn(Ref*, ui::Widget::TouchEventType);
	void onBtnNextLevel(Ref*, ui::Widget::TouchEventType);
	void onBtnShare(Ref*, ui::Widget::TouchEventType);
private:
	static const int item_count = 5;
	Node* m_pItems[item_count];
};