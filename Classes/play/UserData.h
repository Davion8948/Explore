/*
 *	UserData是数据管理的枢纽，负责硬盘与内存的数据交换
 *	当用户数据有变化时，负责通知相应的UI界面做刷新。

 *	关于UI界面刷新部分的声明：这是一个耦合度极高的设计。
 *	事实上最理想的做法是UserData作为单例，同时结合监听者模式，向外界提供一系列接口；
 *	当数据改变时，通过接口来通知外界。这样一来UserData就做到了真正的“开放封闭”。
 *	但对于Explore这个系统来说，完美的做法有点大材小用，所以暂时不实现监听者模式。
 */
#pragma once

#include "play_shared.h"
#include "EncryptValue.h"
#include "Toobar.h"

class UserData
	: public Singleton<UserData>
{
public:
	UserData();
	~UserData();

	enum UserDataIndex
	{
		udi_heart = Toolbar::prop_heart,
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

private:
	EVI m_val[udi_count];
};
