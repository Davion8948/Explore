#include "Effect.h"
#include "cex/cex.h"

USING_NS_CC;

cocos2d::Sequence* Effect::fromName( const char* animation_name, int loop_times/* = 1*/ )
{
	Effect* ret = new Effect;
	if (ret->init())
	{
		ret->autorelease();

		Animation* amn = AnimationCache::getInstance()->getAnimation(animation_name);
		Animate* amt = Animate::create(amn);
		Repeat* repeat = Repeat::create(amt, loop_times);
		return Sequence::createWithTwoActions(amt, CallFunc::create( std::bind(&Effect::onAnimateFinished, ret) ) );
	}
	delete ret;
	return nullptr;
}

// cocos2d::Animate* Effect::fromFiles( const char* format, int end, int start/*=0*/ )
// {
// 	Animation* animation = Animation::create();
// 	for (int i=start; i<end; ++i)
// 	{
// 		animation->addSpriteFrameWithFile(cex::cstr(format, i));
// 	}
// 	animation->set
// }

void Effect::onAnimateFinished()
{
	removeFromParent();
}

cocos2d::Sequence* autoRemoveAction( cocos2d::Node* target, cocos2d::FiniteTimeAction* action1 )
{
	return Sequence::create( action1, CallFunc::create(std::bind(&Node::removeFromParent, target)), nullptr );
}


void showVividly( cocos2d::Node* node )
{
	node->setScale(0.5f);
	node->runAction( Sequence::createWithTwoActions(ScaleTo::create(0.2f, 1.2f), ScaleTo::create(0.1f,1.0f)));
}
