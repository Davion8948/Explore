#include "ShopLayer.h"
#include "MainLayer.h"
#include "cocostudio/CocoStudio.h"
#include "LevelData.h"
#include "UDWhenPlay.h"
#include "MainLayer.h"

using namespace cocostudio;
using namespace ui;

bool ShopLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget* shop = GUIReader::getInstance()->widgetFromJsonFile("eui/shop.json");
	addChild(shop);
	setContentSize(shop->getContentSize());
// 
// 	Size win = CCDirector::getInstance()->getVisibleSize();
// 	setPosition( (win-shop->getContentSize()+Size(0,toolbar->getContentSize().height))/2 );
	
	Button* btn = nullptr;
	for (int i=0; i<7; ++i)
	{
		btn = dynamic_cast<Button*>(shop->getChildByName( to_string(i) ));
		btn->setTag(i);
		btn->addTouchEventListener( std::bind(&ShopLayer::onBtnBuy, this, placeholders::_1, placeholders::_2) );
		m_btns.push_back(btn);
	}

	btn = dynamic_cast<Button*>(shop->getChildByName("continue"));
	btn->addTouchEventListener( std::bind(&ShopLayer::onBtnContinue, this, placeholders::_1, placeholders::_2) );

	btn = dynamic_cast<Button*>(shop->getChildByName("rand"));
	btn->addTouchEventListener( std::bind(&ShopLayer::onBtnRandom, this, placeholders::_1, placeholders::_2) );

	btn = dynamic_cast<Button*>(shop->getChildByName("getcoin"));
	btn->addTouchEventListener( std::bind(&ShopLayer::onBtnGetCoin, this, placeholders::_1, placeholders::_2) );

	m_bRandoming = false;
	return true;
}

void ShopLayer::onExit()
{
	if (m_bRandoming)
	{
		udi_t indexes[] = 
		{
			udi_t::udi_bomb, udi_t::udi_clover, udi_t::udi_key,
			udi_t::udi_hoe, udi_t::udi_arrow,
			udi_t::udi_heart,udi_t::udi_shield
		};
		UDWhenPlay::inst().addValue(indexes[ rand()%7 ], 1);
	}
	Layer::onExit();
}

void ShopLayer::onBtnBuy( Ref* sender, Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	Button* btn = dynamic_cast<Button*>(sender);
	int id_tag = btn->getTag();
	int costs[] = 
	{
		200, 100, 100,
		100, 100, 
		600, 300
	};
	udi_t indexes[] = 
	{
		udi_t::udi_bomb, udi_t::udi_clover, udi_t::udi_key,
		udi_t::udi_hoe, udi_t::udi_arrow,
		udi_t::udi_heart,udi_t::udi_shield
	};
	
	int price = costs[id_tag];
	if( price>UDWhenPlay::inst().getValue(udi_t::udi_coin) )
	{
		playEffect(ClickError);
	}
	else
	{
		UDWhenPlay::inst().addValue(udi_t::udi_coin, -price);
		UDWhenPlay::inst().addValue(indexes[id_tag], 1);

		Label* tip = Label::createWithSystemFont("+1", "Arial", 32);
		tip->setPosition( btn->getContentSize()/2 );
		tip->runAction( autoRemoveAction(tip, MoveBy::create(2,Vec2(0,32))) );
		btn->addChild(tip);

		playEffect(ClickButton);
	}
}

// void ShopLayer::onBtnBack( Ref*, ui::Widget::TouchEventType type )
// {
// 	Return_If(type != Widget::TouchEventType::ENDED);
// 	Director::getInstance()->replaceScene( LoadingScene::create() );
// }

void ShopLayer::onBtnContinue( Ref*, ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickButton);
	runAction(CallFunc::create(std::bind(&MainLayer::removeTopLayer, mainlayer)));
}

void ShopLayer::onBtnRandom( Ref*, ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	if (m_bRandoming || UDWhenPlay::inst().getValue(udi_t::udi_coin)<100)
	{
		playEffect(ClickError);
		return;
	}
	m_bRandoming = true;
	UDWhenPlay::inst().addValue(udi_t::udi_coin, -100);
	playEffect(ClickButton);

	vector<int> candy;
	for (int i=0; i<m_btns.size(); ++i)
	{
		candy.push_back(i);
	}
	std::random_shuffle(candy.begin(), candy.end());

	for (int i=0; i<candy.size(); ++i)
	{
		DelayTime* pre1 = DelayTime::create( i*0.05 );
		Sequence* seq = Sequence::create( ScaleTo::create(0.05f,1.5f), ScaleTo::create(0.1f,1.0f), nullptr);
		DelayTime* post1 = DelayTime::create( (m_btns.size()-i)*0.05 );
		Repeat* rep = Repeat::create( Sequence::create(pre1, seq, post1, nullptr), 5 );
		DelayTime* pre2 = DelayTime::create( i*0.05*3 );
		Sequence* seq2 = Sequence::create( ScaleTo::create(0.1f,1.5f), ScaleTo::create(0.1f,1.0f), nullptr);
		DelayTime* pre3 = DelayTime::create( i*0.05*6 );
		Sequence* seq3 = Sequence::create( ScaleTo::create(0.1f,1.5f), ScaleTo::create(0.1f,1.0f), nullptr);
		Sequence* final = Sequence::create(rep, pre2, seq2, pre3, seq3, nullptr);

		int idx = candy[i];
		if (i != candy.back())
		{
			m_btns[idx]->runAction(final);
		}
		else
		{
			m_btns[idx]->runAction(Sequence::create(final, DelayTime::create(1.5f), seq3->clone(), CallFunc::create([=](){
				udi_t indexes[] = 
				{
					udi_t::udi_bomb, udi_t::udi_clover, udi_t::udi_key,
					udi_t::udi_hoe, udi_t::udi_arrow,
					udi_t::udi_heart,udi_t::udi_shield
				};
				UDWhenPlay::inst().addValue(indexes[idx], 1);
				Label* tip = Label::createWithSystemFont("+1", "Arial", 32);
				tip->setPosition( m_btns[idx]->getContentSize()/2 );
				tip->runAction( autoRemoveAction(tip, MoveBy::create(2,Vec2(0,32))) );
				m_btns[idx]->addChild(tip);

				playEffect(ClickButton);
				m_bRandoming = false;
			}), nullptr));
		}
	}
}

void ShopLayer::onBtnGetCoin( Ref*, ui::Widget::TouchEventType type )
{
	Return_If(type != Widget::TouchEventType::ENDED);
	playEffect(ClickError);
	CCLOG("getcoin");
}
