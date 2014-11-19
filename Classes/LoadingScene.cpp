#include "LoadingScene.h"
#include "LoadingLayer.h"

LoadingScene::LoadingScene(void)
{
}


LoadingScene::~LoadingScene(void)
{
}

bool LoadingScene::init()
{
	Return_False_If(!Scene::init());
	addChild(LoadingLayer::create());
	return true;
}
