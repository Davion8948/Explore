#include "ProgressScene.h"
#include "ProgressLayer.h"

ProgressScene::ProgressScene(void)
{
}


ProgressScene::~ProgressScene(void)
{
}

bool ProgressScene::init()
{
	Return_False_If(!Scene::init());
	addChild(ProgressLayer::create());
	return true;
}
