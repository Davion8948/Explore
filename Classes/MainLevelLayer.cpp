#include "MainLevelLayer.h"
#include "cocostudio/CocoStudio.h"
#include "play/PlayScene.h"
using namespace cocostudio;
using namespace ui;
MainLevelLayer::MainLevelLayer(void)
{

}


MainLevelLayer::~MainLevelLayer(void)
{
}

void MainLevelLayer::onClickLevel( Ref *target, cocos2d::ui::Widget::TouchEventType type )
{
	Return_If(type !=  cocos2d::ui::Widget::TouchEventType::ENDED);
	ValueMap intent;
	intent["level"] = 1; 
		
	PlayScene *playScene = PlayScene::create();
	playScene->setIntent(intent);
	CCDirector::sharedDirector()->replaceScene(playScene);
}

bool MainLevelLayer::init()
{
	Return_False_If(!Layer::init());
	ui::Widget *LevelWidget = GUIReader::getInstance()->widgetFromJsonFile("mainlevel/MainLevel_1.ExportJson");
	addChild(LevelWidget);
	setContentSize(LevelWidget->getContentSize());
	Button *level1Btn = dynamic_cast<ui::Button*>(LevelWidget->getChildByName("level1"));
	level1Btn->addTouchEventListener(std::bind(&MainLevelLayer::onClickLevel,this,  placeholders::_1, placeholders::_2));
	return true;
}
