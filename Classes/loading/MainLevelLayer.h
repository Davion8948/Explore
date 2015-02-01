#pragma once
#include "loading/loading_shared.h"
using namespace ui;
#define MAX_MAIN_LEVEL 6
class MainLevelLayer
	:public Layer
{
public:
	MainLevelLayer(void);
	~MainLevelLayer(void);
	CREATE_FUNC(MainLevelLayer);
	virtual bool init();
	void onClickLevel(Ref *target);
	void onClickBack(Ref *sender);
	void createScrollView();
	void setIntent(const ValueMap &intent);
private:
	ValueMap mIntent;
	Menu *menu ;
	Menu * createMenu(const Size &contentSize);
};

