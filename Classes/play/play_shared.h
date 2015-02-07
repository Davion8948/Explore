#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cex/cex.h"
#include "lib4cc3x/lib4cc3x.h"
#include "list"
#include "vector"
#include "string"
#include "map"

#include "loading/LoadingScene.h"
#include "SoundMgr.h"
#include "Effect.h"

using namespace cocos2d;
using namespace cex;
using namespace lib4cc3x;
using namespace std;
// class Player;
//extern Player* g_player;

class MainLayer;
extern MainLayer* mainlayer;

class GameMap;
extern GameMap* gamemap;

class Toolbar;
extern Toolbar* toolbar;

static const int tw = 68;
static const int th = 70;