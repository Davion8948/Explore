#pragma once

#include "cocos2d.h"
#include "cex/cex.h"
#include "string"
using namespace std;

class LanguageMgr
	: public cex::Singleton<LanguageMgr>
{
public:
	LanguageMgr();
	~LanguageMgr();

	string getText(const string& id);

private:
	cocos2d::ValueMap m_id2text;
};
