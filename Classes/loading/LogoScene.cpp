#include "LogoScene.h"
#include "LogoLayer.h"

LogoScene::LogoScene(void)
{
}


LogoScene::~LogoScene(void)
{
}

bool LogoScene::init()
{
	Return_False_If(!Scene::init());
	addChild(LogoLayer::create());
	return true;
}

