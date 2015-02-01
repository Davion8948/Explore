#include "ProgressLayer.h"
#include "LoadingScene.h"


ProgressLayer::ProgressLayer(void):count(0)
{
}


ProgressLayer::~ProgressLayer(void)
{
}

bool ProgressLayer::init()
{
	Return_False_If(!Layer::init());
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(winSize.width/2, winSize.height/2);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("loading/loading.plist");
	Sprite *background = Sprite::createWithSpriteFrameName("loading.png");
	background->setPosition(center);
	addChild(background);
	// bian kuang
	Sprite *border = Sprite::createWithSpriteFrameName("button1.png");
	Sprite *borderInner =  Sprite::createWithSpriteFrameName("button2.png");
	Vec2 progressPos = Vec2(center.x , center.y* 0.3f);
	border->setPosition(progressPos);
	borderInner->setPosition(progressPos);
	ProgressTimer *progressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("button3.png"));
	progressBar->setType(ProgressTimer::Type::BAR);
	progressBar->setPosition(progressPos);
	progressBar->setMidpoint(Vec2(0, 0));
	progressBar->setBarChangeRate(Vec2(1, 0));
	progressBar->setParent(0);
	progressBar->setTag(987);
	addChild(border, 2);
	addChild(borderInner);
	addChild(progressBar,1);
	scheduleUpdate();
	return true;
}

void ProgressLayer::update( float dt )
{
	ProgressTimer *progress = (ProgressTimer *)getChildByTag(987);
	if(count==0)
	{
		loadResource();
		count++;
	}
	else
	{
		
		float percent = progress->getPercentage();
		if(percent >= 100.f)
		{
			unscheduleAllSelectors();
			Director::getInstance()->replaceScene(LoadingScene::create());
		}
		else if(percent >= 40.f&& percent<80 )
		{
			count += 0.6f;
			progress->setPercentage(count);
		}else
		{
			count += 0.3f;
			progress->setPercentage(count);
	
		}

	}
}

void ProgressLayer::loadResource()
{
	 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mainlevel/mainlevel.plist");
	 CCLOG("load done");
}
