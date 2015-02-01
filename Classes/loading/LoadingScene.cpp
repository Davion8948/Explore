#include "LoadingScene.h"
#include "LoadingLayer.h"
#include "LogoLayer.h"
LoadingScene::LoadingScene(void)
{
}


LoadingScene::~LoadingScene(void)
{
}

bool LoadingScene::init()
{
	Return_False_If(!Scene::init());
	Layer *loadingLayer = LoadingLayer::create();
	addChild(loadingLayer);
	return true;
}

