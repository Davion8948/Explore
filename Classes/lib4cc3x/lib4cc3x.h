#pragma once
#include "cocos2d.h"

namespace lib4cc3x
{
	void logPoint(const cocos2d::Point& pt, const char* tip=nullptr);
	void logSize(const cocos2d::Size& size, const char* tip=nullptr);
	void logRect(const cocos2d::Rect& rect, const char* tip=nullptr);

	bool contain(const cocos2d::ValueMap& cfg, const std::string& key);
	void safe_assign(std::string& val, const cocos2d::ValueMap& cfg, const std::string& key);
	void safe_assign(int& val, const cocos2d::ValueMap& cfg, const std::string& key);
	void safe_assign(float& val, const cocos2d::ValueMap& cfg, const std::string& key);

}
