/*
 *	UDWhenPlay := UserDataWhenPlay
 *
 *	UserDataWhenPlay是UserDataMgr和PlayScene之间的桥梁
 *	由于玩家死亡时要回滚数据，所以不建议直接操作UserDataMgr
 *	利用UserDataWhenPlay做一个缓冲区，负责与PlayScene相关数据的管理
 *	当用户数据有变化时，负责通知相应的UI界面做刷新。
 */
#pragma once

#include "play_shared.h"
#include "EncryptValue.h"
#include "ud/UserDataMgr.h"
#include "Toobar.h"

typedef UserDataMgr::UserDataIndex udi_t;

class UDWhenPlay
	: public Singleton<UDWhenPlay>
{
public:
	UDWhenPlay();
	~UDWhenPlay();

	//using UserDataMgr::UserDataIndex;

	int getValue(udi_t idx) const;
	void setValue(udi_t idx, int val);
	void addValue(udi_t idx, int val_diff);

	void backup();
	void commit();
private:
	EVI m_val[udi_t::udi_count];
};
