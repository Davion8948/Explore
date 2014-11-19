#include "lib4cc3x.h"

using namespace lib4cc3x;

void lib4cc3x::logPoint( const cocos2d::Point& pt, const char* tip/*=nullptr*/ )
{
	if (nullptr != tip)
	{
		CCLOG("%s:(%.3f,%.3f)", tip, pt.x, pt.y);
	}
	else
	{
		CCLOG("(%.3f,%.3f)", pt.x, pt.y);
	}
}

void lib4cc3x::logSize( const cocos2d::Size& size, const char* tip/*=nullptr*/ )
{
	if (nullptr != tip)
	{
		CCLOG("%s:(%.3f,%.3f)", tip, size.width, size.height);
	}
	else
	{
		CCLOG("(%.3f,%.3f)", size.width, size.height);
	}
}

void lib4cc3x::logRect( const cocos2d::Rect& rect, const char* tip/*=nullptr*/ )
{
	if (nullptr != tip)
	{
		CCLOG("%s:(%.3f,%.3f,%.3f,%.3f)", tip, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	}
	else
	{
		CCLOG("(%.3f,%.3f,%.3f,%.3f)", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	}
}

bool lib4cc3x::contain( const cocos2d::ValueMap& cfg, const std::string& key )
{
	return cfg.find(key)!=cfg.end();
}

void lib4cc3x::safe_assign( std::string& val, const cocos2d::ValueMap& cfg, const std::string& key )
{
	auto iter = cfg.find(key);
	if (iter != cfg.end())
	{
		val = iter->second.asString();
	}
}

void lib4cc3x::safe_assign( int& val, const cocos2d::ValueMap& cfg, const std::string& key )
{
	auto iter = cfg.find(key);
	if (iter != cfg.end())
	{
		val = iter->second.asInt();
	}
}

void lib4cc3x::safe_assign( float& val, const cocos2d::ValueMap& cfg, const std::string& key )
{
	auto iter = cfg.find(key);
	if (iter != cfg.end())
	{
		val = iter->second.asFloat();
	}
}
