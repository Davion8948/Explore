#include "ShopLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "LevelData.h"
#include "UDWhenPlay.h"
#include "MainLayer.h"
#include "loading/LoadingScene.h"

using namespace cocostudio;
using namespace ui;

bool ShopLayer::init()
{
	Return_False_If(!Layer::init());
	setTouchEnabled(false);

	ui::Widget* shop = GUIReader::getInstance()->widgetFromJsonFile("eui/shop.json");
	addChild(shop);
	setContentSize(shop->getContentSize());

	Size win = CCDirector::getInstance()->getVisibleSize();
	setPosition( (win-shop->getContentSize())/2 );
	
	Button* btn = nullptr;
	for (int i=0; i<6; ++i)
	{
		btn = dynamic_cast<Button*>(shop->getChildByName( to_string(i) ));
		btn->addTouchEventListener( std::bind(&ShopLayer::onBtnBuy, this, placeholders::_1, placeholders::_2) );
	}

	btn = dynamic_cast<Button*>(shop->getChildByName("back"));
	btn->addTouchEventListener( std::bind(&ShopLayer::onBtnBack, this, placeholders::_1, placeholders::_2) );
	btn = dynamic_cast<Button*>(shop->getChildByName("continue"));
	btn->addTouchEventListener( std::bind(&ShopLayer::onBtnContinue, this, placeholders::_1, placeholders::_2) );

	return true;
}

void ShopLayer::onBtnBuy( Ref* sender, Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	int idx = stoi(dynamic_cast<Button*>(sender)->getName());
	int costs[] = {50, 50, 100, 300, 600, 600};
	udi_t indexes[] = {udi_t::udi_bomb, udi_t::udi_clover, udi_t::udi_key, udi_t::udi_hoe, udi_t::udi_shield, udi_t::udi_arrow};
	
	int price = costs[idx];
	Return_If( price>UDWhenPlay::inst().getValue(udi_t::udi_coin) );

	UDWhenPlay::inst().addValue(udi_t::udi_coin, -price);
	UDWhenPlay::inst().addValue(indexes[idx], 1);
}

void ShopLayer::onBtnBack( Ref*, ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	Director::getInstance()->replaceScene( LoadingScene::create() );
}

void ShopLayer::onBtnContinue( Ref*, ui::Widget::TouchEventType type )
{
	//Return_If(type != Widget::TouchEventType::ENDED);
	Return_If(type != Widget::TouchEventType::ENDED);
	//mainlayer->removeTopLayer();
	//removeFromParentAndCleanup(false);
}
