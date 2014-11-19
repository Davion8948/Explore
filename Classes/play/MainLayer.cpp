#include "MainLayer.h"
#include "GameMap.h"
#include "Player.h"
#include "Toobar.h"
#include "FinishLayer.h"
#include "UserData.h"

MainLayer::MainLayer(void)
{
}


MainLayer::~MainLayer(void)
{
	mainlayer = nullptr;
}

bool MainLayer::init()
{
	Return_False_If(!Layer::init());

	EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = std::bind(&MainLayer::onTouchesBegan, this, std::placeholders::_1, std::placeholders::_2);
 	listener->onTouchesMoved = std::bind(&MainLayer::onTouchesMoved, this, std::placeholders::_1, std::placeholders::_2);
 	listener->onTouchesEnded = std::bind(&MainLayer::onTouchesEnded, this, std::placeholders::_1, std::placeholders::_2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	CCAssert(mainlayer==nullptr, "");
	mainlayer = this;

	setCascadeColorEnabled(true);

	startLevelImpl(0);

	GameStateMgr::inst().change(gs_playing);

	return true;
}

void MainLayer::onStateChanged( GameState gs )
{
	GameState last = GameStateMgr::inst().lastState();
	Return_If(last==gs_win || last==gs_dead);
	switch (gs)
	{
	case gs_dead:
		{
			Sprite* shield = Sprite::create("bg.png");
			Size win = Director::getInstance()->getWinSize();
			shield->setScaleX( win.width/shield->getContentSize().width );
			shield->setScaleY( win.height/shield->getContentSize().height );
			shield->setPosition(win.width/2, win.height/2);
			shield->setOpacity(0);
			shield->runAction( FadeIn::create(2) );
			addChild(shield);
			runAction( Sequence::create( DelayTime::create(2), CallFunc::create([=]{
				startLevel(0);
			}), nullptr));
		}
 		break;
	case gs_win:
		//startLevel(0);
		runAction( Sequence::create( DelayTime::create(1), CallFunc::create( [=](){
			addChild(FinishLayer::create());
		}), nullptr));
		break;
	default:
		break;
	}
}

void MainLayer::onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event )
{
// 	Point pt = touches.front()->getLocation();
// 	m_pMap->onClick( pt );
}

void MainLayer::onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event )
{

}

void MainLayer::onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event )
{
	Return_If(GameStateMgr::inst().curState() != gs_playing);
	gamemap->onClick( convertToTileCoordinate(touches.front()->getLocation()) );
}

Point MainLayer::convertToTileCoordinate( Point pt )
{
	Rect rc = gamemap->getBoundingBox();
	pt.x -= rc.origin.x;
	pt.y = rc.size.height + rc.origin.y - pt.y;
	return pt;
}

void MainLayer::startLevel( int level )
{
	runAction( CallFunc::create( std::bind(&MainLayer::startLevelImpl, this, level) ) );
	GameStateMgr::inst().change(gs_playing);
	if (UserData::inst().getValue(UserData::udi_heart)<1)
	{
		UserData::inst().setValue(UserData::udi_heart, 1);
	}
}

void MainLayer::startLevelImpl( int level )
{
	removeChild(gamemap);
	removeChild(toolbar);
	removeAllChildren();

	gamemap = GameMap::create("lvl/lvl1.4.tmx");
	addChild(gamemap);

	toolbar = Toolbar::create();
	addChild(toolbar);
}
