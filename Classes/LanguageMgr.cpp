#include "LanguageMgr.h"
#include "cex/config_t.h"

using namespace cex;
USING_NS_CC;

LanguageMgr::LanguageMgr()
{
	m_id2text = FileUtils::getInstance()->getValueMapFromFile("chinese.xml");
}

LanguageMgr::~LanguageMgr()
{

}

std::string LanguageMgr::getText( const string& id )
{
	auto pos = m_id2text.find(id);
	return pos!=m_id2text.end() ? pos->second.asString() : string();
}
