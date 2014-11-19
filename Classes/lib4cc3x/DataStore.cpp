#include "DataStore.h"

using namespace lib4cc3x;
using namespace std;

void DataStore::setInt( QueryKey tag, int value )
{
	m_key2int[tag] = value;
}

int DataStore::getInt( QueryKey tag, int def /*= 0*/ )
{
	auto iter = m_key2int.find(tag);
	return (iter==m_key2int.end() ? def : iter->second);
}

void DataStore::setFloat( QueryKey tag, float value )
{
	m_key2float[tag] = value;
}

float DataStore::getFloat( QueryKey tag, float def /*= 0*/ )
{
	auto iter = m_key2float.find(tag);
	return (iter==m_key2float.end() ? def : iter->second);
}

void DataStore::setString( QueryKey tag, const string& value )
{
	m_key2str[tag] = value;
}

std::string DataStore::getString( QueryKey tag, const string& def /*= string()*/ )
{
	auto iter = m_key2str.find(tag);
	return (iter==m_key2str.end() ? def : iter->second);
}

void DataStore::setBool( QueryKey tag, bool value )
{
	m_key2bool[tag] = value;
}

bool DataStore::getBool( QueryKey tag, bool def /*= false*/ )
{
	auto iter = m_key2bool.find(tag);
	return (iter==m_key2bool.end() ? def : iter->second);
}
