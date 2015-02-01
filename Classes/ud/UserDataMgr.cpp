#include "UserDataMgr.h"
#include "string"
#include "cocos2d.h"

using namespace std;
using namespace cex;
USING_NS_CC;

UserDataMgr::UserDataMgr()
{

}

UserDataMgr::~UserDataMgr()
{
}

int UserDataMgr::getValue( UserDataIndex idx ) const
{
	return m_val[idx];
}

void UserDataMgr::setValue( UserDataIndex idx, int val )
{
	m_val[idx] = val;
}

void UserDataMgr::addValue( UserDataIndex idx, int val_diff )
{
	setValue(idx, m_val[idx]+val_diff);
}

void UserDataMgr::loadFromDisk()
{
	string fpath = FileUtils::getInstance()->getWritablePath();
	ValueMap data = FileUtils::getInstance()->getValueMapFromFile(fpath+"user.txt");
	if (data.empty())
	{
		for (int i=udi_heart; i<udi_count; ++i)
		{
			m_val[i] = 0;
		}
	}
	else
	{
		for (int i=udi_heart; i<udi_count; ++i)
		{
			m_val[i] = data.at( to_string(i) ).asInt();			
		}
	}

	if (m_val[0] == 0)
		m_val[0] = 1;
}

void UserDataMgr::saveToDisk()
{
	ValueMap data;
	for (int i=udi_heart; i<udi_count; ++i)
	{
		data[ to_string(i) ] = getValue( (UserDataIndex)i );
	}
	string fpath = FileUtils::getInstance()->getWritablePath();
	FileUtils::getInstance()->writeToFile(data, fpath+"user.txt");
}
