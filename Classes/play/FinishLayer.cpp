#include "FinishLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "LevelData.h"
using namespace cocostudio;
using namespace ui;

bool FinishLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget* finish = GUIReader::getInstance()->widgetFromJsonFile("eui/finish_1.ExportJson");//finish_1.ExportJson eui/finish.json
	addChild(finish);
	setContentSize(finish->getContentSize());

	Size win = CCDirector::getInstance()->getVisibleSize();
	setPosition( (win-finish->getContentSize())/2 );
	
	for (int i=0; i<item_count; ++i)
	{
		m_pItems[i] = finish->getChildByName( sstr("item%d", i) );
	}
	dynamic_cast<Text*>(m_pItems[0]->getChildByName("num0"))->setString( to_string(LevelData::inst().getElapsedTime()) );
	dynamic_cast<Text*>(m_pItems[1]->getChildByName("num1"))->setString( to_string(LevelData::inst().getCollectedCoin()) );
	dynamic_cast<Text*>(m_pItems[2]->getChildByName("num2"))->setString( to_string(LevelData::inst().getKilledMonster()) );
	dynamic_cast<Text*>(m_pItems[3]->getChildByName("num3"))->setString( to_string(LevelData::inst().getDestroyedTrap()) );
	dynamic_cast<Text*>(m_pItems[4]->getChildByName("num4"))->setString( to_string(LevelData::inst().getOpenedDoor()) );

	Button* btn = nullptr;
	{
		btn = dynamic_cast<Button*>(finish->getChildByName("return"));
		btn->addTouchEventListener( std::bind(&FinishLayer::onBtnReturn, this, placeholders::_1, placeholders::_2) );

		btn = dynamic_cast<Button*>(finish->getChildByName("next"));
		btn->addTouchEventListener( std::bind(&FinishLayer::onBtnNextLevel, this, placeholders::_1, placeholders::_2) );

		//btn = dynamic_cast<Button*>(finish->getChildByName("share"));
		//btn->addTouchEventListener( std::bind(&FinishLayer::onBtnShare, this, placeholders::_1, placeholders::_2) );
	}

	int ntime = max(0, 5-LevelData::inst().getElapsedTime()/15);
	runAction(Repeat::create( CCCallFunc::create([=](){
		auto delay = DelayTime::create(min(0.5f, rand()%100/100.0f));
		runAction(Sequence::createWithTwoActions(delay, CallFunc::create([=](){
			auto play = ParticleSystemQuad::create("winfire.plist");
			Size win = Director::getInstance()->getWinSize();
			int w = win.width-200;
			int h = win.height-200;
			play->setPosition(rand()%w+100, rand()%h+100);
			addChild(play);
		})));
	}), ntime) );

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

void FinishLayer::onBtnReturn( Ref*, ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickButton);
	Scene* scene = TransitionPageTurn::create(1, LoadingScene::create(), false);
	Director::getInstance()->replaceScene( scene );
}

void FinishLayer::onBtnNextLevel( Ref*, Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickButton);
	mainlayer->startNextLevel();
}

void FinishLayer::onBtnShare( Ref*, ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickButton);
	CCLOG("onBtnShare");
}
