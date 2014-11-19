#include "FinishLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
using namespace ui;

bool FinishLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget* finish = GUIReader::getInstance()->widgetFromJsonFile("eui/finish.json");
	addChild(finish);
	setContentSize(finish->getContentSize());

	Size win = CCDirector::getInstance()->getVisibleSize();
	setPosition( (win-finish->getContentSize())/2 );

	for (int i=0; i<item_count; ++i)
	{
		m_pItems[i] = finish->getChildByName( sstr("item%d", i) );
	}

	Button* btn = nullptr;
	
	btn = dynamic_cast<Button*>(finish->getChildByName("next"));
	btn->addTouchEventListener( std::bind(&FinishLayer::onBtnNextLevel, this, placeholders::_1, placeholders::_2) );

	return true;
}

void FinishLayer::onEnter()
{
	Layer::onEnter();

	for (int i=0; i<item_count; ++i)
	{
		m_pItems[i]->setScaleY(0);
		m_pItems[i]->runAction( Sequence::create( DelayTime::create(0.1*i), ScaleTo::create(0.2f, 1, 1), nullptr) );
	}
}

void FinishLayer::onBtnNextLevel( Ref*, Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	//GameStateMgr::inst().change(gs_);
	mainlayer->startLevel(0);
}
