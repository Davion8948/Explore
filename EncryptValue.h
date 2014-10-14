#pragma once
#define DEBUG_OPEN 1;
template<class T>
class EncryptValue
{
public:
	EncryptValue(void);
	~EncryptValue(void);
	void setValue(T value);
	T getValue();
	EncryptValue<T> operator = (EncryptValue<T> other);
	EncryptValue<T> operator = (T value);
	EncryptValue<T> operator -= (EncryptValue<T> other);
	EncryptValue<T> operator -= (T value);
	EncryptValue<T> operator += (EncryptValue<T> other);
	EncryptValue<T> operator += (T value);
	bool operator == (EncryptValue<T> other);
	bool operator == (T value);
	bool operator != (EncryptValue<T> other);
	bool operator != (T value);
	bool operator > (EncryptValue<T> other);
	bool operator > (T value);
	bool operator >= (EncryptValue<T> other);
	bool operator >= (T value);
	bool operator < (EncryptValue<T> other);
	bool operator < (T value);
	bool operator <= (EncryptValue<T> other);
	bool operator <= (T value);

private:
	T mValue;
	T mEncryptValue;
#if DEBUG_OPEN
	T mRealVal;
#endif

};

