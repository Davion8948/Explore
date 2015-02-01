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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ocean.plist");
	AnimationCache::getInstance()->addAnimationsWithFile("play_animations.plist");

	int mLevel = m_intent["mLevel"].asInt();
	int vLevel = m_intent["vLevel"].asInt();

	MainLayer* layer = MainLayer::create();
	layer->setMainLevel(mLevel);
	layer->startViceLevel(vLevel);
	addChild(layer);

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
