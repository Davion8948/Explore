#include "MainLayer.h"
#include "GameMap.h"
#include "Player.h"
#include "Toobar.h"
#include "FinishLayer.h"
#include "UDWhenPlay.h"
#include "LevelData.h"
#include "ShopLayer.h"
#include "ud/LevelDataMgr.h"

MainLayer::MainLayer(void)
	:m_bCurLongTouchEnd(true)
	,m_mLevel(-1)
	,m_vLevel(-1)
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

	EventListenerKeyboard* keyboard = EventListenerKeyboard::create();
	keyboard->onKeyReleased = std::bind(&MainLayer::onKeyReleased, this, std::placeholders::_1, std::placeholders::_2);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard, this);

	CCAssert(mainlayer==nullptr, "");
	mainlayer = this;

	setCascadeColorEnabled(true);

	GameStateMgr::inst().change(gs_playing);

	return true;
}

void MainLayer::onStateChanged( GameState gs )
{
	GameState last = GameStateMgr::inst().lastState();
	//Return_If(last==gs_win || last==gs_dead);
	switch (gs)
	{
	case gs_playing:
		{
			LevelData::inst().reset( LevelData::inst().getCurLevel()+1 );
			UDWhenPlay::inst().backup();
		}
		break;
	case gs_dead:
		{
			lazyInitAnimation(false);
			runAction( Sequence::create( DelayTime::create(2), 
				CallFunc::create(std::bind(&MainLayer::restartCurrentLevel, this)), nullptr));

			UserDataMgr::inst().setValue(udi_t::udi_shield, 0);
			UserDataMgr::inst().setValue(udi_t::udi_heart, 1);
		}
 		break;
	case gs_win:
		{
			runAction( Sequence::create( DelayTime::create(1), CallFunc::create( [=](){
				addChild(FinishLayer::create());
			}), nullptr));
			UDWhenPlay::inst().commit();
		}		
		break;
	default:
		break;
	}
}

void MainLayer::onTouchesBegan( const std::vector<Touch*>& touches, Event *unused_event )
{
	m_startTouchTime = time(0);
}

void MainLayer::onTouchesMoved( const std::vector<Touch*>& touches, Event *unused_event )
{
	int cur = time(0);
	if (cur-m_startTouchTime>=1 && m_bCurLongTouchEnd)
	{
		m_bCurLongTouchEnd = false;
		gamemap->onLongTouches(convertToTileCoordinate(touches.front()->getLocation()));
	}
}

void MainLayer::onTouchesEnded( const std::vector<Touch*>& touches, Event *unused_event )
{
	Return_If(GameStateMgr::inst().curState() != gs_playing);
	Point dstPoint = convertToTileCoordinate(touches.front()->getLocation());
	if (m_bCurLongTouchEnd)
	{
		gamemap->onClick(dstPoint);
	}
	else
	{
		m_bCurLongTouchEnd = true;
	}
}

void MainLayer::onKeyReleased( EventKeyboard::KeyCode keyCode, Event* event )
{
	Return_If(keyCode != EventKeyboard::KeyCode::KEY_ESCAPE);
	Layer* top = getTopLayer();
	if (top == nullptr)
	{
		popLayer( ShopLayer::create() );
	}
	else
	{
		removeTopLayer();
	}
}

Point MainLayer::convertToTileCoordinate( Point pt )
{
	Rect rc = gamemap->getBoundingBox();
	pt.x -= rc.origin.x;
	pt.y = rc.size.height + rc.origin.y - pt.y;
	return pt;
}

void MainLayer::setMainLevel( int level )
{
	m_mLevel = level;
}

void MainLayer::startViceLevel( int level )
{
	runAction( CallFunc::create( std::bind(&MainLayer::startViceLevelImpl, this, level) ) );
	GameStateMgr::inst().change(gs_playing);
	if (UDWhenPlay::inst().getValue(udi_t::udi_heart)<1)
	{
		UDWhenPlay::inst().setValue(udi_t::udi_heart, 1);
	}
}

void MainLayer::startNextLevel()
{
	++m_vLevel;
	if (m_vLevel == LevelDataMgr::inst().getViceLevelCount())
	{
		m_vLevel = 0;
		++m_mLevel;
		if (m_mLevel == LevelDataMgr::inst().getMainLevelCount())
		{
			m_mLevel = 0;//Í¨¹Ø
		}
	}
	this->setMainLevel(m_mLevel);
	this->startViceLevel(m_vLevel);
	LevelDataMgr::inst().setMainLevel(m_mLevel);
	LevelDataMgr::inst().setViceLevel(m_vLevel);
}

void MainLayer::restartCurrentLevel()
{
	startViceLevel(m_vLevel);
}

int MainLayer::getCurrentLevel()
{
	return m_vLevel;
}

void MainLayer::startViceLevelImpl( int level )
{
	m_vLevel = level;

	removeChild(gamemap);
	removeChild(toolbar);
	removeAllChildren();

	gamemap = GameMap::create(cstr("lvl/lvl%d.%d.tmx", m_mLevel, m_vLevel));
	addChild(gamemap);

	toolbar = Toolbar::create();
	addChild(toolbar);

	lazyInitAnimation(true);
}

void MainLayer::lazyInitAnimation( bool in_or_out )
{
	Sprite* shield = Sprite::create("bg.png");
	Size win = Director::getInstance()->getWinSize();
	shield->setScaleX( win.width/shield->getContentSize().width );
	shield->setScaleY( win.height/shield->getContentSize().height );
	shield->setPosition(win.width/2, win.height/2);
	if (!in_or_out)
	{
		shield->setOpacity(0);
		shield->runAction(FadeIn::create(2));
	}
	else
	{
		shield->runAction(FadeOut::create(2));
	}
	addChild(shield);
	runAction( Sequence::create( DelayTime::create(2), CallFunc::create(std::bind(&MainLayer::removeChild,this,shield,true)), nullptr ) );
}

void MainLayer::popLayer( Layer* layer )
{
	m_uiLayers.push_back(layer);
	addChild(layer);
}

void MainLayer::removeTopLayer()
{
	Return_If(m_uiLayers.empty());
	removeChild(m_uiLayers.back());
	m_uiLayers.pop_back();
}

Layer* MainLayer::getTopLayer()
{
	Return_Null_If(m_uiLayers.empty());
	return m_uiLayers.back();
}
