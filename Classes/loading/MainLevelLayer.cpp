#include "MainLevelLayer.h"
#include "cocostudio/CocoStudio.h"
#include "play/PlayScene.h"
#include "loading/LoadingScene.h"
#include "ud/LevelDataMgr.h"
using namespace cocostudio;
using namespace ui;
MainLevelLayer::MainLevelLayer(void)
{
}

MainLevelLayer::~MainLevelLayer(void)
{
}

bool MainLevelLayer::init()
{
	Return_False_If(!Layer::init());
	Sprite *background = Sprite::createWithSpriteFrameName("background.jpg");
	background->setAnchorPoint(Vec2(0,0));
	background->setPosition(0, 0);
	this->addChild(background);
	Sprite *backDown = Sprite::createWithSpriteFrameName("back_down.png");
	Sprite *backUp = Sprite::createWithSpriteFrameName("back_up.png");
	Size winSize =  Director::getInstance()->getWinSize();
	MenuItemSprite *mis = MenuItemSprite::create(backUp, backDown, [=](Ref *sender){
		playEffect(ClickButton);
		Director::getInstance()->replaceScene(LoadingScene::create());
	});
	Menu *menu = Menu::create(mis, nullptr);
	menu->setPosition(Vec2(winSize.width*0.1f,winSize.height*0.85f));
	this->addChild(menu, 2);
	createScrollView();
	//if(!mIntent.empty())
	//{
		//int mainLevel = 2;//mIntent["m_level"].asInt();
		//MenuItemSprite *menuItem  = (MenuItemSprite *)(menu->getChildByTag(mainLevel));
		//Sprite *actionSprite = Sprite::create();
		//this->addChild(actionSprite);
		//actionSprite->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=](){
		//	char pName[32];
		//	sprintf(pName, "level_%02d_01.png", mainLevel);
		//	auto sprite =Sprite::createWithSpriteFrameName(pName);
		//	sprintf(pName, "level_%02d_00.png", mainLevel);
		//	auto downSprite = Sprite::createWithSpriteFrameName(pName);
		//	//menuItem->setNormalImage(sprite);
		//	//menuItem->setDisabledImage(downSprite);
		//	menuItem->setEnabled(true);
		//}),nullptr));
		//menuItem->runAction(DelayTime::create(1));
		//menuItem->runAction(Sequence::create(DelayTime::create(1), CallFunc::create([=](){
		///*	char pName[32];
		//	sprintf(pName, "level_%02d_1.png", mainLevel);
		//	auto sprite =Sprite::createWithSpriteFrameName(pName);
		//	sprintf(pName, "level_%02d_0.png", mainLevel);
		//	auto downSprite = Sprite::createWithSpriteFrameName(pName);
		//	menuItem->setNormalImage(sprite);
		//	menuItem->setDisabledImage(downSprite);
		//	menuItem->setEnabled(true)*/;
		//}), nullptr));
	/*}*/
	return true;
}

void MainLevelLayer::createScrollView()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto scrollView =ScrollView::create();
	//scrollView->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	scrollView->setContentSize(visibleSize);
	//Point ss = scrollView->getAnchorPoint();
	Point p =  scrollView->getPosition();
	//scrollView->setAnchorPoint(Point::ZERO);
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	auto containerSize = Size(visibleSize.width*2, visibleSize.height);
	scrollView->setInnerContainerSize(containerSize);
	scrollView->addChild(createMenu(containerSize));
	//Point ss2 = scrollView->getAnchorPoint();
	Point p2 =  scrollView->getPosition();
	addChild(scrollView);

}

Menu * MainLevelLayer::createMenu(const Size &contentSize)
{
	menu = Menu::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < MAX_MAIN_LEVEL; ++i)
	{
		bool unlock = LevelDataMgr::inst().isUnlock(i);
		char frameName[32], downFrame[32];
		sprintf(frameName, "level_%02d_%02d.png", i, unlock?1:0);
		sprintf(downFrame, "level_%02d_%02d.png", i,0);
		auto sprite = Sprite::createWithSpriteFrameName(frameName);
		auto downSprite = Sprite::createWithSpriteFrameName(downFrame);
		auto menuItem = MenuItemSprite::create(sprite, downSprite, [=](Ref *sender){
			playEffect(ClickButton);
			ValueMap intent;
			intent["mLevel"] = i;
			intent["vLevel"] = LevelDataMgr::inst().getViceLevel();
			auto scene = PlayScene::create();
			scene->setIntent(intent);
			Director::getInstance()->replaceScene(scene);
		});
		menuItem->setEnabled(unlock);
		menuItem->setAnchorPoint(Point(0, 0.5f));
		float xPos = -visibleSize.width/2.f+40.f + i*(menuItem->getContentSize().width+25.f);
		menuItem->setPosition(Point(xPos, -40.f));
		menu->addChild(menuItem, 1, i);
	}
	return menu;
}

void MainLevelLayer::setIntent( const ValueMap &intent )
{
	mIntent = intent;
	//	int mainLevel = mIntent["mLevel"].asInt();
	//int fromFlag = mIntent["fromFlag"].asInt();
}
