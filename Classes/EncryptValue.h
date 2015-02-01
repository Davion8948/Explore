#pragma once
#include "cstdlib"
#define DEBUG_OPEN 1
/************************************************************************/
/* 
	“‡ªÚº”√‹¿‡
	sample:
	{		
	EVI i;
	EVI j(5);
	i = 4;
	i += 1;
	i -= 2;
	bool a1 = i<3;
	bool a2 = i<=1;
	bool a3 = i>3;
	bool a4 = i>=1;
	bool a5 = i==4;
	bool a6 = i!=4;
	bool s = i<=j;// 3 5
	bool s2 = i<j;
	bool s3 = i>j;
	bool s4 = i>=j;
	bool s5 = i==j;
	bool s6 = i!=j;
	}
*/
/************************************************************************/
template<class T>
class EncryptValue
{
	
private:
	T getValue() const
	{
		return mValue ^ mEncryptValue;
	}
	void setValue(T value)
	{
		mEncryptValue = (T)rand();
		mValue = value ^ mEncryptValue;
	}
public:
	EncryptValue(void)
	{
		setValue(0);
	}
	EncryptValue(T value)
	{
		setValue(value);
	}
	~EncryptValue(void)
	{

	}

	const EncryptValue<T>& operator = (T value)
	{
		setValue(value);
		return *this;
	}
	operator T() const
	{
		return getValue();
	}

// 	template<class U>
// 	void operator += (const EncryptValue<U>& u)
// 	{
// 		setValue(getValue()+u.getValue());
// 	}
	template<class U>
	void operator += (U u)
	{
		setValue(getValue()+u);
	}

private:
	T mValue;
	T mEncryptValue;
};
typedef EncryptValue<int> EVI;

template<class T, class U>
bool operator < (const EncryptValue<T>& t, const EncryptValue<U>& u)
{
	return t.getValue() < u.getValue();
}
