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
	addChild(MainLevelLayer::create());
	return true;
}

