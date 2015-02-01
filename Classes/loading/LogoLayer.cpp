#include "LogoLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ProgressScene.h"
using namespace cocostudio;
using namespace ui;
LogoLayer::LogoLayer(void)
{
}


LogoLayer::~LogoLayer(void)
{
}

bool LogoLayer::init()
{
	Return_False_If(!Layer::init());
	//Widget *logoWidget = GUIReader::getInstance()->widgetFromJsonFile("loading/LogoUi.ExportJson");
	logoSp = Sprite::create("loading/logo.jpg");
	logoSp->setAnchorPoint(Point::ZERO);
	logoSp->setOpacity(0);
	addChild(logoSp);
	//setContentSize(logoSp->getContentSize());
	logoSp->runAction(FadeIn::create(1.0f));
	this->schedule(schedule_selector(LogoLayer::logoEnd), 2.f);
	return true;
}

void LogoLayer::logoEnd( float dt )
{
	Sequence *seq = Sequence::create(FadeOut::create(1.f), CallFunc::create([=](){
		Director::getInstance()->replaceScene(ProgressScene::create());
	}), nullptr);
	logoSp->runAction(seq);
}
