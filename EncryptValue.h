#pragma once
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
		mValue = value;
		mEncryptValue = (T)rand();
		mValue ^= mEncryptValue;
	}
public:
	EncryptValue(void)
	{
		setValue(0);
	}
	~EncryptValue(void){

	}
	EncryptValue(T value)
	{
		setValue(value);
	}

	const EncryptValue<T>& operator = (EncryptValue<T> other)
	{
		setValue(other.getValue());
		return *this;
	}
	const EncryptValue<T>& operator = (T value)
	{
		setValue(value);
		return *this;
	}
	const EncryptValue<T>& operator -= (EncryptValue<T> other)
	{
		setValue(getValue() - other.getValue());
		return *this;
	}
	const EncryptValue<T>& operator -= (T value)
	{
		setValue(getValue() - value);
		return *this;
	}
	const EncryptValue<T>& operator += (EncryptValue<T> other)
	{
		setValue(getValue() + other.getValue());
		return *this;
	}
	const EncryptValue<T>& operator += (T value)
	{
		setValue(getValue() + value);
		return *this;
	}

	bool operator == (EncryptValue<T> other)
	{
		return getValue() == other.getValue();
	}
	bool operator == (T value)
	{
		return getValue() == value;
	}
	bool operator != (EncryptValue<T> other)
	{
		return getValue() != other.getValue();
	}
	bool operator != (T value)
	{
		return getValue() != value;
	}
	bool operator > (EncryptValue<T> other)
	{
		return getValue() > other.getValue();
	}
	bool operator > (T value)
	{
		return getValue() > value;
	}
	bool operator >= (EncryptValue<T> other)
	{
		return getValue() >= other.getValue();
	}
	bool operator >= (T value)
	{
		return getValue() >= value;
	}
	bool operator < (EncryptValue<T> other)
	{
		return getValue() < other.getValue();
	}
	bool operator < (T value)
	{
		return getValue() < value;
	}
	bool operator <= (EncryptValue<T> other)
	{
		return getValue() <= other.getValue();
	}
	bool operator <= (T value)
	{
		return getValue() <= value;
	}
	operator T()
	{
		return getValue();
	}
private:
	T mValue;
	T mEncryptValue;
};
typedef EncryptValue<int> EVI;
