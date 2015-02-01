#include "MainLevelScene.h"
#include "MainLevelLayer.h"

MainLevelScene::MainLevelScene(void)
{
}


MainLevelScene::~MainLevelScene(void)
{
}

bool MainLevelScene::init()
{
	Return_False_If(!Scene::init());

	auto layer = MainLevelLayer::create();
	layer->setIntent(getIntent());
	addChild(layer);
	return true;
}

void MainLevelScene::setIntent( const cocos2d::ValueMap &intent )
{
	 mIntent = intent;
}

cocos2d::ValueMap MainLevelScene::getIntent()
{
	return mIntent;
}

