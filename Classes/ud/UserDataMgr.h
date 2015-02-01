/*
 *	用户数据的枢纽，负责用户数据的保存与读取
 */
#pragma once

#include "cex/cex.h"
#include "EncryptValue.h"

class UserDataMgr
	: public cex::Singleton<UserDataMgr>
{
public:
	UserDataMgr();
	~UserDataMgr();

	enum UserDataIndex
	{
		udi_heart,
		udi_shield,
		udi_key,
		udi_arrow,
		udi_hoe,
		udi_bomb,
		udi_map,
		udi_prop_count,

		udi_clover,
		udi_coin,

		udi_count
	};

	int getValue(UserDataIndex idx) const;
	void setValue(UserDataIndex idx, int val);
	void addValue(UserDataIndex idx, int val_diff);

	void loadFromDisk();
	void saveToDisk();
private:
	EVI m_val[udi_count];
};
