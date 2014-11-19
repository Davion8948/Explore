#include "play_shared.h"

class FinishLayer
	: public Layer
{
public:
	CREATE_FUNC(FinishLayer);

	virtual bool init();

	virtual void onEnter();

protected:
	void onBtnNextLevel(Ref*, ui::Widget::TouchEventType);
private:
	static const int item_count = 3;
	Node* m_pItems[item_count];
};