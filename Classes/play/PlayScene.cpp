#include "PlayScene.h"
#include "MainLayer.h"

PlayScene::PlayScene(void)
{
}


PlayScene::~PlayScene(void)
{
}

bool PlayScene::init()
{
	Return_False_If(!Scene::init());

	addChild(MainLayer::create());

	return true;
}

void PlayScene::setIntent( const cocos2d::ValueMap& intent )
{
	m_intent = intent;
}

cocos2d::ValueMap PlayScene::getIntent() const
{
	return m_intent;
}
