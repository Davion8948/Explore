#include "ExitLayer.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
ExitLayer::ExitLayer(void)
{
}


ExitLayer::~ExitLayer(void)
{
}

bool ExitLayer::init()
{
	Return_False_If(!Layer::init());
	Widget *exitWidget = GUIReader::getInstance()->widgetFromJsonFile("loading/NewUi_1.ExportJson");
	this->addChild(exitWidget);
	setContentSize(exitWidget->getContentSize());

	Size win = CCDirector::getInstance()->getVisibleSize();
	Size win2 =  exitWidget->getContentSize();
	CCLOG("win.size=====%f,%f", win2.height, win2.width);
	//this->setPosition((win - exitWidget->getContentSize())/2);
	Button *okBtn = dynamic_cast<Button*>(exitWidget->getChildByName("ok"));
	okBtn->addTouchEventListener(std::bind(&ExitLayer::onClickOk, this, placeholders::_1, placeholders::_2));
	Button *cancelBtn = dynamic_cast<Button*>(exitWidget->getChildByName("cancel"));
	cancelBtn->addTouchEventListener(std::bind(&ExitLayer::onClickCancel, this, placeholders::_1, placeholders::_2));

	return true;
}

void ExitLayer::onClickOk( Ref *ref, TouchType type )
{
	Return_If(type != TouchType::ENDED);
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void ExitLayer::onClickCancel( Ref *ref, TouchType type )
{
	Return_If(type != TouchType::ENDED);
}
