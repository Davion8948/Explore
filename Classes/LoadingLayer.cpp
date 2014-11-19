#include "LoadingLayer.h"
#include "cocostudio/CocoStudio.h"
#include "MainLevelScene.h"
using namespace cocostudio;
using namespace ui;

LoadingLayer::LoadingLayer(void)
{
}


LoadingLayer::~LoadingLayer(void)
{
}

bool LoadingLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget *loadingWidget = GUIReader::getInstance()->widgetFromJsonFile("loading/ExploreUI_1.ExportJson");
	addChild(loadingWidget);
	setContentSize(loadingWidget->getContentSize());
	Button *playBtn = dynamic_cast<ui::Button*>(loadingWidget->getChildByName("play"));
	playBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickPlay, this, placeholders::_1, placeholders::_2));
	return true;
}
void LoadingLayer::onClickPlay(Ref* target, cocos2d::ui::Widget::TouchEventType type)
{
	Return_If(type != cocos2d::ui::Widget::TouchEventType::ENDED);
	CCLOG("onclick");
	CCDirector::sharedDirector()->replaceScene(MainLevelScene::create());
}