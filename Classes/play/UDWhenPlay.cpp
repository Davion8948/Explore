#include "UDWhenPlay.h"
#include "Toolbar.h"

UDWhenPlay::UDWhenPlay()
{
	backup();
}

UDWhenPlay::~UDWhenPlay()
{
}

int UDWhenPlay::getValue( udi_t idx ) const
{
	return m_val[idx];
}

void UDWhenPlay::setValue( udi_t idx, int val )
{
	m_val[idx] = val;
	if (idx<UserDataMgr::udi_prop_count)
	{
		toolbar->setProperty( (Toolbar::PropType)idx, val );
	}
	else if (idx==UserDataMgr::udi_clover)
	{
		toolbar->setClover(val);
	}
	else if (idx==UserDataMgr::udi_coin)
	{
		toolbar->setCoin(val);
	}
	else
	{
		CCAssert(false, "");
	}
}

void UDWhenPlay::addValue( udi_t idx, int val_diff )
{
	setValue(idx, m_val[idx]+val_diff);
}

void UDWhenPlay::backup()
{
	for (int i=udi_t::udi_heart; i<udi_t::udi_count; ++i)
	{
		m_val[i] = UserDataMgr::inst().getValue( (udi_t)i );
	}
}

void UDWhenPlay::commit()
{
	for (int i=udi_t::udi_heart; i<udi_t::udi_count; ++i)
	{
		UserDataMgr::inst().setValue((udi_t)i, m_val[i] );
	}
}
