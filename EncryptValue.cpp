#include "stdafx.h"
#include "EncryptValue.h"

template<class T>
EncryptValue::EncryptValue(void)
{
	setValue(0);
}

template<class T>
EncryptValue::~EncryptValue(void)
{
}
template<class T>
EncryptValue<T> EncryptValue<T>::operator=(EncryptValue<T> other)
{
	setValue(other.getValue());
	return *this;
}
template<class T>
EncryptValue<T> EncryptValue<T>::operator=(T value)
{
	setValue(value);
	return *this;
}
template<class T>
EncryptValue<T> EncryptValue<T>::operator+=(EncryptValue<T> other)
{
	setValue(getValue() + other.getValue());
	return *this;
}
template<class T>
EncryptValue<T> EncryptValue<T>::operator += (T value)
{
	setValue(getValue() + value);
	return *this;
}
template<class T>
EncryptValue<T> EncryptValue<T>::operator-=(EncryptValue<T> other)
{
	setValue(getValue() - other.getValue());
	return *this;
}
template<class T>
EncryptValue<T> EncryptValue<T>::operator-=(T value)
{
	setValue(getValue() - value);
	return *this;
}
template<class T>
bool EncryptValue<T>::operator==(EncryptValue<T> other)
{
	return getValue() == other.getValue();
}
template<class T>
bool EncryptValue<T>::operator==(T value)
{
	return getValue() == value;
}
template<class T>
bool EncryptValue<T>::operator!=(EncryptValue<T> other)
{
	return getValue() != other.getValue();
}
template<class T>
bool EncryptValue<T>::operator!=(T value)
{
	return getValue() != value;
}
template <class T>
bool EncryptValue<T>::operator > (EncryptValue<T> other)
{
	return getValue() > other.getValue();
}
template<class T>
bool EncryptValue<T>::operator > (T value)
{
	return getValue() > value;
}
template<class T> 
bool EncryptValue<T>::operator >= (EncryptValue<T> other)
{
	return getValue() >= other.getValue();
}
template<class T>
bool EncryptValue<T>::operator >= (T value)
{
	return getValue() >= value;
}
template <class T>
bool EncryptValue<T>::operator < (EncryptValue<T> other)
{
	return getValue() < other.getValue();
}
template <class T>
bool EncryptValue<T>::operator < (T value)
{
	return getValue() < value;
}
template<class T>
bool EncryptValue<T>::operator<=(EncryptValue<T> other)
{
	return getValue() <= other.getValue();
}
template <class T>
bool EncryptValue<T>::operator<=(T value)
{
	return getValue() <= value;
}
template <class T>
T EncryptValue<T>::getValue()
{
	return mValue * mEncryptValue;
}
template <class T>
void EncryptValue<T>::setValue(T value)
{
	mValue = value;
	mEncryptValue = (T)rand();
	mValue ^= mEncryptValue;

#if DEBUG_OPEN
	mRealVal = value;
#endif

}
