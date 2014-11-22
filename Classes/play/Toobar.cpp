#include "Toobar.h"
#include "cocostudio/CocoStudio.h"
#include "UDWhenPlay.h"
#include "GameMap.h"
#include "MainLayer.h"

using namespace cocostudio;
using namespace ui;

Toolbar::Toolbar()
{

}

Toolbar::~Toolbar()
{

}

bool Toolbar::init()
{
	Return_False_If(!Layer::init());

	ui::Widget* tool_widget = GUIReader::getInstance()->widgetFromJsonFile("eui/toolbar.json");
	addChild(tool_widget);
	setContentSize(tool_widget->getContentSize());

	m_ui[prop_heart].pUI = tool_widget->getChildByName("heart");
	m_ui[prop_heart].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("heart_num"));
	m_ui[prop_shield].pUI = tool_widget->getChildByName("shield");
	m_ui[prop_shield].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("shield_num"));
	m_ui[prop_key].pUI = tool_widget->getChildByName("key");
	m_ui[prop_key].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("key_num"));
	m_ui[prop_arrow].pUI = tool_widget->getChildByName("arrow");
	m_ui[prop_arrow].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("arrow_num"));
	m_ui[prop_hoe].pUI = tool_widget->getChildByName("hoe");
	m_ui[prop_hoe].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("hoe_num"));
	m_ui[prop_bomb].pUI = tool_widget->getChildByName("bomb");
	m_ui[prop_bomb].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("bomb_num"));
	m_ui[prop_map].pUI = tool_widget->getChildByName("map");
	m_ui[prop_map].pText = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("map_num"));

	m_pCloverBtn = dynamic_cast<ui::Button*>(tool_widget->getChildByName("clover"));
	m_pCoinNum = dynamic_cast<ui::TextAtlas*>(tool_widget->getChildByName("coin_num"));

	ui::Button* pBtn = nullptr;
	{
		pBtn = dynamic_cast<ui::Button*>(tool_widget->getChildByName("map"));
		pBtn->addTouchEventListener( std::bind(&Toolbar::onClickMap, this, placeholders::_1, placeholders::_2) );

		pBtn = dynamic_cast<ui::Button*>(tool_widget->getChildByName("bomb"));
		pBtn->addTouchEventListener( std::bind(&Toolbar::onClickBomb, this, placeholders::_1, placeholders::_2) );

		pBtn = dynamic_cast<ui::Button*>(tool_widget->getChildByName("hoe"));
		pBtn->addTouchEventListener( std::bind(&Toolbar::onClickHoe, this, placeholders::_1, placeholders::_2) );
	}

	int level = mainlayer->getCurrentLevel();
	dynamic_cast<TextAtlas*>(tool_widget->getChildByName("level"))->setString(to_string(level+1));

	refreshDisplay();
	return true;
}

void Toolbar::refreshDisplay()
{
	setCoin(UDWhenPlay::inst().getValue(udi_t::udi_coin));
	for (int i=prop_heart; i<prop_count; ++i)
	{
		setProperty((PropType)i, UDWhenPlay::inst().getValue((udi_t)i));
	}
	setClover(UDWhenPlay::inst().getValue(udi_t::udi_clover));
}

void Toolbar::setClover( int val )
{
	m_pCloverBtn->setVisible( val!=0 );
}

void Toolbar::setCoin( int coin )
{	
	m_pCoinNum->setString( to_string(coin) );
}

void Toolbar::setProperty( PropType prop_tag, int val )
{
	CCAssert(val >= 0, "");
	m_ui[prop_tag].pText->setString( to_string(val) );
	m_ui[prop_tag].pUI->setVisible( val>0 );
}

void Toolbar::onClickHoe( Ref* target, cocos2d::ui::Widget::TouchEventType type )
{
	Return_If(type != cocos2d::ui::Widget::TouchEventType::ENDED);
	int x = UDWhenPlay::inst().getValue(udi_t::udi_hoe);
	Return_If(x==0);
	if (gamemap->onEffectHoe())
	{
		UDWhenPlay::inst().setValue(udi_t::udi_hoe, x-1);
	}
}

void Toolbar::onClickBomb( Ref* target, cocos2d::ui::Widget::TouchEventType type )
{
	Return_If(type != cocos2d::ui::Widget::TouchEventType::ENDED);
	int x = UDWhenPlay::inst().getValue(udi_t::udi_bomb);
	Return_If(x==0);
	if (gamemap->onEffectBomb())
	{
		UDWhenPlay::inst().setValue(udi_t::udi_bomb, x-1);
	}
}

void Toolbar::onClickMap( Ref* target, cocos2d::ui::Widget::TouchEventType type )
{
	Return_If(type != cocos2d::ui::Widget::TouchEventType::ENDED);
	int x = UDWhenPlay::inst().getValue(udi_t::udi_map);
	Return_If(x==0);
	if (gamemap->onEffectMap())
	{
		UDWhenPlay::inst().setValue(udi_t::udi_map, x-1);
	}
}
