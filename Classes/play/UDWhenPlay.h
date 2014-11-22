/*
 *	UDWhenPlay := UserDataWhenPlay
 *
 *	UserDataWhenPlay��UserDataMgr��PlayScene֮�������
 *	�����������ʱҪ�ع����ݣ����Բ�����ֱ�Ӳ���UserDataMgr
 *	����UserDataWhenPlay��һ����������������PlayScene������ݵĹ���
 *	���û������б仯ʱ������֪ͨ��Ӧ��UI������ˢ�¡�
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
