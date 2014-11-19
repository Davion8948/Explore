#include "UserData.h"
#include "Toobar.h"

UserData::UserData()
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

UserData::~UserData()
{
	ValueMap data;
	for (int i=udi_heart; i<udi_count; ++i)
	{
		data[ to_string(i) ] = getValue( (UserDataIndex)i );
	}
	string fpath = FileUtils::getInstance()->getWritablePath();
	FileUtils::getInstance()->writeToFile(data, fpath+"user.txt");
}

int UserData::getValue( UserDataIndex idx ) const
{
	return m_val[idx];
}

void UserData::setValue( UserDataIndex idx, int val )
{
	m_val[idx] = val;
	if (idx<udi_prop_count)
	{
		toolbar->setProperty( (Toolbar::PropType)idx, val );
	}
	else if (idx==udi_clover)
	{
		toolbar->setClover(val);
	}
	else if (idx==udi_coin)
	{
		toolbar->setCoin(val);
	}
}

void UserData::addValue( UserDataIndex idx, int val_diff )
{
	setValue(idx, m_val[idx]+val_diff);
}
