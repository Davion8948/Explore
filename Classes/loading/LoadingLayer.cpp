#include "LoadingLayer.h"
#include "cocostudio/CocoStudio.h"
#include "MainLevelScene.h"
using namespace cocostudio;
using namespace ui;

LoadingLayer::LoadingLayer(void):openSetting(true), openTrophy(true)
{
}


LoadingLayer::~LoadingLayer(void)
{
}

bool LoadingLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget *loadingWidget = GUIReader::getInstance()->widgetFromJsonFile("loading/ExploreUI_1.ExportJson");
	addChild(loadingWidget);
	setContentSize(loadingWidget->getContentSize());
	Button *playBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("play"));
	playBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickPlay, this, placeholders::_1, placeholders::_2));
	settingBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("setting"));
	settingBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickSetting, this, placeholders::_1, placeholders::_2));
	infoBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("information"));
	infoBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickInfo, this, placeholders::_1, placeholders::_2));
	volumeBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("volume"));
	volumeBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickVolume, this, placeholders::_1, placeholders::_2));

	trophyBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("trophy"));
	trophyBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickTrophy, this, placeholders::_1, placeholders::_2));
	wechatBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("twitter"));
	wechatBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickTrophy, this, placeholders::_1, placeholders::_2));
	weiboBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("facebook"));
	weiboBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickTrophy, this, placeholders::_1, placeholders::_2));
	return true;
}
void LoadingLayer::onClickPlay(Ref* target, TouchType type)
{
	Return_If(type != TouchType::ENDED);
	CCDirector::sharedDirector()->replaceScene(MainLevelScene::create());
}

void LoadingLayer::onClickSetting( Ref *target,TouchType type )
{
	Return_If(type != TouchType::ENDED);
	RotateTo *rotate = RotateTo::create(0.5f, openSetting ? 180 : 0);
	if(!openSetting)
	{
		MoveTo *move1 = MoveTo::create(0.4f, Vec2(165, 107));
		ScaleTo *scaleTo1 = ScaleTo::create(0.4f, 0.4f);
		RotateTo *rotate1 = RotateTo::create(0.4f, 180);
		infoBtn->runAction(Spawn::create(rotate1, move1, scaleTo1, 0));
		MoveTo *move2 = MoveTo::create(0.5f, Vec2(165, 107));
		ScaleTo *scaleTo2 = ScaleTo::create(0.5f, 0.4f);
		RotateTo *rotate2 = RotateTo::create(0.5f, 180);
		volumeBtn->runAction(Spawn::create(rotate2, move2, scaleTo2, 0));
	}
	else
	{
		MoveTo *moveTo1 = MoveTo::create(0.4f, Vec2(165, 224));
		ScaleTo *scaleTo1 = ScaleTo::create(0.4f, 1.0f);
		RotateTo *rotate1 = RotateTo::create(0.4f, 0);

		MoveTo *moveTo2 = MoveTo::create(0.5f, Vec2(165, 336));
		ScaleTo *scaleTo2 = ScaleTo::create(0.5f, 1.0f);
		RotateTo *rotate2 = RotateTo::create(0.5f, 0);
		infoBtn->runAction(Spawn::create(rotate1, moveTo1, scaleTo1, 0));
		volumeBtn->runAction(Spawn::create(rotate2, moveTo2, scaleTo2, 0));
	}
	openSetting = !openSetting;
	settingBtn->runAction(rotate);
}

void LoadingLayer::onClickVolume( Ref *target,TouchType type )
{
	Return_If(type !=  TouchType::ENDED);
}

void LoadingLayer::onClickInfo( Ref *target,TouchType type )
{
	Return_If(type !=  TouchType::ENDED);
}

void LoadingLayer::onClickTrophy( Ref *target, TouchType type )
{
	Return_If(type !=  TouchType::ENDED);
	RotateTo *rotate = RotateTo::create(0.4f, openTrophy ? 180 : 0);
	if(!openTrophy)
	{
		MoveTo *move1 = MoveTo::create(0.4f, Vec2(810, 107));
		ScaleTo *scaleTo1 = ScaleTo::create(0.4f, 0.4f);
		RotateTo *rotate1 = RotateTo::create(0.4f, 180);
		weiboBtn->runAction(Spawn::create(rotate1, move1, scaleTo1, 0));

		MoveTo *move2 = MoveTo::create(0.5f, Vec2(810, 107));
		ScaleTo *scaleTo2 = ScaleTo::create(0.5f, 0.4f);
		RotateTo *rotate2 = RotateTo::create(0.5f, 180);
		wechatBtn->runAction(Spawn::create(rotate2, move2, scaleTo2, 0));
	}
	else
	{
		MoveTo *moveTo1 = MoveTo::create(0.5f, Vec2(810, 336));
		ScaleTo *scaleTo1 = ScaleTo::create(0.5f, 1.0f);
		RotateTo *rotate1 = RotateTo::create(0.5f, 0);
		wechatBtn->runAction(Spawn::create(rotate1, moveTo1, scaleTo1, 0));

		MoveTo *moveTo2 = MoveTo::create(0.4f, Vec2(810, 224));
		ScaleTo *scaleTo2 = ScaleTo::create(0.4f, 1.0f);
		RotateTo *rotate2 = RotateTo::create(0.4f, 0);
		weiboBtn->runAction(Spawn::create(rotate2, moveTo2, scaleTo2, 0));
	}
	openTrophy = !openTrophy;
	trophyBtn->runAction(rotate);
}
