﻿#include "LoadingLayer.h"
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
void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *shareInfo, __Dictionary *error)
{
	switch (state) {
	case C2DXResponseStateSuccess:
		C2DXShareSDK::toast("分享成功");
		break;
	case C2DXResponseStateFail:
		C2DXShareSDK::toast("分享失败");
		break;
	default:
		C2DXShareSDK::toast("分享取消");
		break;
	}
}
void LoadingLayer::onClickWeibo( Ref *target, TouchType type )
{
	Return_If(type != TouchType::ENDED);
	playEffect(ClickButton);
	__Dictionary *content = __Dictionary::create();
	//Dictionary可用的Key如下，如果需要用到其它字段，可自行参考Sample中的代码实现：
	// (并不是所有平台都有这些字段，需要参考文档http://wiki.mob.com/Android_%E4%B8%8D%E5%90%8C%E5%B9%B3%E5%8F%B0%E5%88%86%E4%BA%AB%E5%86%85%E5%AE%B9%E7%9A%84%E8%AF%A6%E7%BB%86%E8%AF%B4%E6%98%8E)

	content -> setObject(String::create("扫雷"), "content"); //要分享的内容，注意在文档中content对应的是text字段
	content -> setObject(String::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image"); //可以是本地路径（如：/sdcard/a.jpg）或是一个URL
	content -> setObject(String::create("Title"), "title");
	content -> setObject(String::create("测试描述"), "description");
	content -> setObject(String::create("http://sharesdk.cn"), "url");
	content -> setObject(String::createWithFormat("%d", C2DXContentTypeNews), "type");
	content -> setObject(String::create("http://sharesdk.cn"), "siteUrl");
	content -> setObject(String::create("ShareSDK"), "site");
	content -> setObject(String::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
	content -> setObject(String::create("extInfo"), "extInfo"); //微信分享应用时传给应用的附加信息
	C2DXShareSDK::showShareMenu(NULL, content, cocos2d::Point(100, 100), C2DXMenuArrowDirectionLeft,shareResultHandler);
}

void LoadingLayer::onClickWechat( Ref *target, TouchType type )
{
	Return_If(type != TouchType::ENDED);
	playEffect(ClickButton);

}
