/*
 *	UserData�����ݹ������Ŧ������Ӳ�����ڴ�����ݽ���
 *	���û������б仯ʱ������֪ͨ��Ӧ��UI������ˢ�¡�

 *	����UI����ˢ�²��ֵ�����������һ����϶ȼ��ߵ���ơ�
 *	��ʵ���������������UserData��Ϊ������ͬʱ��ϼ�����ģʽ��������ṩһϵ�нӿڣ�
 *	�����ݸı�ʱ��ͨ���ӿ���֪ͨ��硣����һ��UserData�������������ġ����ŷ�ա���
 *	������Explore���ϵͳ��˵�������������е���С�ã�������ʱ��ʵ�ּ�����ģʽ��
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
