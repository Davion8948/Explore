#include "ConfirmLayer.h"
#include "cex/cex.h"
#include "cocostudio/CocoStudio.h"
#include "LanguageMgr.h"
#include "SoundMgr.h"
#include "Effect.h"

using namespace std;
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio;

ConfirmLayer::ConfirmLayer()
{

}

ConfirmLayer::~ConfirmLayer()
{

}

ConfirmLayer* ConfirmLayer::create( const char* tipID, std::function<void(void)> ok/*=nullptr*/, std::function<void(void)> cancel/*=nullptr*/ )
{
	ConfirmLayer* ret = new ConfirmLayer;
	CCAssert(nullptr != ret, "");
	if (!ret->init())
	{
		delete ret;
		return NULL;
	}
	ret->autorelease();
	ret->setTipFromID(tipID);
	ret->onOk = ok;
	ret->onCancel = cancel;
	return ret;
}

bool ConfirmLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget* layer = GUIReader::getInstance()->widgetFromJsonFile("eui/confirm.ExportJson");
	addChild(layer);
	setContentSize( layer->getContentSize() );

	Button* btn = nullptr;
	{
		btn = dynamic_cast<Button*>(layer->getChildByName("ok"));
		btn->addTouchEventListener( std::bind(&ConfirmLayer::onBtnOk, this, placeholders::_1, placeholders::_2) );
		showVividly(btn);
		btn = dynamic_cast<Button*>(layer->getChildByName("cancel"));
		btn->addTouchEventListener( std::bind(&ConfirmLayer::onBtnCancel, this, placeholders::_1, placeholders::_2) );
		showVividly(btn);
	}

	m_pTipText = dynamic_cast<Text*>(layer->getChildByName("text"));
	CCAssert(m_pTipText, "");

	return true;
}

void ConfirmLayer::setTipFromID( const char* tipID )
{
	string text = LanguageMgr::inst().getText(tipID);
	m_pTipText->setString( text );
}

void ConfirmLayer::onBtnOk( Ref*, cocos2d::ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickButton);
	if (nullptr != onOk)
	{
		onOk();
	}
	else
	{
		runAction( CallFunc::create(std::bind(&ConfirmLayer::removeFromParent, this)) );
	}
}

void ConfirmLayer::onBtnCancel( Ref*, cocos2d::ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickButton);
	if (nullptr != onCancel)
	{
		onCancel();
	}
	else
	{
		runAction( CallFunc::create(std::bind(&ConfirmLayer::removeFromParent, this)) );
	}
}
