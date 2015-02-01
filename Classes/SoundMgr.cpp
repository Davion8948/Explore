#include "SoundMgr.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "string"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

void playEffect( const char* name )
{
	string full = FileUtils::getInstance()->fullPathForFilename(name);
	SimpleAudioEngine::getInstance()->playEffect(full.c_str());
}

void setBackgroundMusicVolume( int volume )
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume/100.0f);
}

void setEffectsVolume( int volume )
{
	SimpleAudioEngine::getInstance()->setEffectsVolume(volume/100.0f);
}

int getEffectsVolume()
{
	return SimpleAudioEngine::getInstance()->getEffectsVolume()*100;
}

int getBackgroundMusicVolume()
{
	return SimpleAudioEngine::getInstance()->getBackgroundMusicVolume()*100;
}

