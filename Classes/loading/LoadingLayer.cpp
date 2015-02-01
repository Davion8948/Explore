#include "LoadingLayer.h"
#include "cocostudio/CocoStudio.h"
#include "MainLevelScene.h"
#include "ExitLayer.h"
#include "SoundMgr.h"
#include "ui/ConfirmLayer.h"
using namespace cocostudio;
using namespace ui;

LoadingLayer::LoadingLayer(void):openSetting(true), openTrophy(true), ifShowSlider(true)
{
}


LoadingLayer::~LoadingLayer(void)
{
}

bool LoadingLayer::init()
{
	Return_False_If(!Layer::init());

	ui::Widget *loadingWidget = GUIReader::getInstance()->widgetFromJsonFile("loading/Loading.ExportJson");
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
	wechatBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickWeibo, this, placeholders::_1, placeholders::_2));
	weiboBtn = dynamic_cast<Button*>(loadingWidget->getChildByName("facebook"));
	weiboBtn->addTouchEventListener(std::bind(&LoadingLayer::onClickWechat, this, placeholders::_1, placeholders::_2));

	EventListenerKeyboard *keyBoard = EventListenerKeyboard::create();
	keyBoard->onKeyReleased = std::bind(&LoadingLayer::onKeyReleased, this, placeholders::_1, placeholders::_2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoard, this);
	volumeSilder = dynamic_cast<Slider*>(loadingWidget->getChildByName("volume_slider"));
	volumeSilder->setVisible(false);
	volumeSilder->setPercent(getBackgroundMusicVolume());
	volumeSilder->addEventListener(std::bind(&LoadingLayer::onClickSlide, this, placeholders::_1, placeholders::_2));
	return true;
}
void LoadingLayer::onClickPlay(Ref* target, TouchType type)
{
	Return_If(type != TouchType::ENDED);
	playEffect(ClickButton);
	Scene* scene = TransitionPageTurn::create(1, MainLevelScene::create(), false);
	Director::getInstance()->replaceScene(scene);
}

void LoadingLayer::onClickSetting( Ref *target,TouchType type )
{
	Return_If(type != TouchType::ENDED);
	settingBtn->setEnabled(false);
	playEffect(ClickButton);
	RotateTo *rotate = RotateTo::create(0.5f, openSetting ? 180 : 0);
	auto lamb = [=](){settingBtn->setEnabled(true);};
	if(!ifShowSlider)
	{
		ifShowSlider = true;
		volumeSilder->setVisible(false);
	}
	if(!openSetting)
	{
		MoveTo *move1 = MoveTo::create(0.4f, Vec2(165, 107));
		ScaleTo *scaleTo1 = ScaleTo::create(0.4f, 0.4f);
		RotateTo *rotate1 = RotateTo::create(0.4f, 180);
		infoBtn->runAction(Spawn::create(rotate1, move1, scaleTo1, 0));
		MoveTo *move2 = MoveTo::create(0.5f, Vec2(165, 107));
		ScaleTo *scaleTo2 = ScaleTo::create(0.5f, 0.4f);
		RotateTo *rotate2 = RotateTo::create(0.5f, 180);
		volumeBtn->runAction( Sequence::create(Spawn::create(rotate2, move2, scaleTo2, 0),
			CallFunc::create(lamb),NULL) );
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
		volumeBtn->runAction(Sequence::create(Spawn::create(rotate2, moveTo2, scaleTo2, 0), 
			CallFunc::create(lamb), NULL));
		volumeBtn->runAction(Spawn::create(rotate2, moveTo2, scaleTo2, 0));

	}
	openSetting = !openSetting;
	settingBtn->runAction(rotate);
}

void LoadingLayer::onClickVolume( Ref *target,TouchType type )
{
	Return_If(type !=  TouchType::ENDED);
	playEffect(ClickButton);
	volumeSilder->setVisible(ifShowSlider);
	ifShowSlider = !ifShowSlider;
}

void LoadingLayer::onClickInfo( Ref *target,TouchType type )
{
	Return_If(type !=  TouchType::ENDED);
	playEffect(ClickButton);

}

void LoadingLayer::onClickTrophy( Ref *target, TouchType type )
{
	Return_If(type !=  TouchType::ENDED);
	trophyBtn->setEnabled(false);
	playEffect(ClickButton);
	RotateTo *rotate = RotateTo::create(0.5f, openTrophy ? 180 : 0);
	auto lamb = [=](){trophyBtn->setEnabled(true);};
	if(!openTrophy)
	{
		MoveTo *move1 = MoveTo::create(0.4f, Vec2(810, 107));
		ScaleTo *scaleTo1 = ScaleTo::create(0.4f, 0.4f);
		RotateTo *rotate1 = RotateTo::create(0.4f, 180);

		MoveTo *move2 = MoveTo::create(0.5f, Vec2(810, 107));
		ScaleTo *scaleTo2 = ScaleTo::create(0.5f, 0.4f);
		RotateTo *rotate2 = RotateTo::create(0.5f, 180);
		weiboBtn->runAction(Spawn::create(rotate1, move1, scaleTo1, 0));
		wechatBtn->runAction(Sequence::create(Spawn::create(rotate2, move2, scaleTo2, 0), CallFunc::create(lamb), NULL));
		wechatBtn->runAction(Spawn::create(rotate2, move2, scaleTo2, 0));
	}
	else
	{
		MoveTo *moveTo1 = MoveTo::create(0.5f, Vec2(810, 336));
		ScaleTo *scaleTo1 = ScaleTo::create(0.5f, 1.0f);
		RotateTo *rotate1 = RotateTo::create(0.5f, 0);

		MoveTo *moveTo2 = MoveTo::create(0.4f, Vec2(810, 224));
		ScaleTo *scaleTo2 = ScaleTo::create(0.4f, 1.0f);
		RotateTo *rotate2 = RotateTo::create(0.4f, 0);
		weiboBtn->runAction(Spawn::create(rotate2, moveTo2, scaleTo2, 0));
		wechatBtn->runAction(Sequence::create(Spawn::create(rotate1, moveTo1, scaleTo1, 0),CallFunc::create(lamb), NULL));
		wechatBtn->runAction(Spawn::create(rotate1, moveTo1, scaleTo1, 0));

	}
	openTrophy = !openTrophy;
	trophyBtn->runAction(rotate);
}

void LoadingLayer::onKeyReleased( EventKeyboard::KeyCode keyCode, Event* event )
{
	Return_If(keyCode != EventKeyboard::KeyCode::KEY_ESCAPE);
	Layer *topLayer = getTopLayer();
	if(topLayer == nullptr)
	{
		char key[20] = "return2";
		ConfirmLayer *confirmLayer = ConfirmLayer::create(key, [](){
			Director::getInstance()->end();
			#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS 
				exit(0);
			#endif
		}, [=](){
			this->runAction(CallFunc::create(std::bind(&LoadingLayer::removeTopLayer, this)));
		});
		playEffect(ClickButton);
		popLayer(confirmLayer);
	}
	else
	{
		//this->runAction(CallFunc::create(std::bind(&)));
	}
}

void LoadingLayer::popLayer(Layer *layer)
{
	mLayers.push_back(layer);
	this->addChild(layer);
}

void LoadingLayer::removeTopLayer()
{
	Return_If(mLayers.empty());
	this->removeChild(mLayers.back());
	mLayers.pop_back();
}

Layer* LoadingLayer::getTopLayer()
{
	Return_Null_If(mLayers.empty());
	return mLayers.back();
}

void LoadingLayer::onClickSlide( Ref *pSender, ui::Slider::EventType type )
{
	if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider *slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		CCLOG("persent=====%d", percent);
		setEffectsVolume(percent);
	}
}

void LoadingLayer::onClickWeibo( Ref *target, TouchType type )
{
	Return_If(type != TouchType::ENDED);
	playEffect(ClickButton);
}

void LoadingLayer::onClickWechat( Ref *target, TouchType type )
{
	Return_If(type != TouchType::ENDED);
	playEffect(ClickButton);

}
