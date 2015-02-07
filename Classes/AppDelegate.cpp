#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "play/PlayScene.h"
#include "ud/UserDataMgr.h"
#include "loading/LogoScene.h"
#include "C2DXShareSDK/C2DXShareSDK.h"
USING_NS_CC;
using namespace cn::sharesdk;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	this->initPlatformConfig();
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
		director->setOpenGLView(glview);
		glview->setFrameSize(480*2, 320*2);
    }

	glview->setDesignResolutionSize(480*2, 320*2, ResolutionPolicy::FIXED_WIDTH);

    // turn on display FPS
//     director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	{
		srand(time(0));
		UserDataMgr::inst().loadFromDisk();
		UserDataMgr::inst().setValue(UserDataMgr::udi_bomb, 10);
	}

 	auto scene = LogoScene::create();
    director->runWithScene(scene);

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initPlatformConfig()
{
	C2DXShareSDK::open("api20", false); 
	CCDictionary *sinaConfigDict = CCDictionary::create(); 
	sinaConfigDict -> setObject(CCString::create("59a8c5a0a2b0"), "app_key");                              
	sinaConfigDict -> setObject(CCString::create("e334a448e5f9da9bf4e2459b69b97d58"), "app_secret"); 
	sinaConfigDict -> setObject(CCString::create("http://www.sharesdk.cn"), "redirect_uri"); 
	C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);
	__Dictionary *qqConfigDict = __Dictionary::create();
	qqConfigDict -> setObject(String::create("100371282"), "app_id");
	C2DXShareSDK::setPlatformConfig(C2DXPlatTypeQQ, qqConfigDict);
}
