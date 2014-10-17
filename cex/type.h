#pragma once

#include <cstdarg>
#include <cassert>

namespace cex
{
	typedef unsigned char uchar;
	typedef unsigned char byte;
	typedef unsigned int uint;
	typedef unsigned short ushort;
	typedef unsigned long ulong;

	
	/*
	 *	多线程版本
	 *	线程安全但效率低一点
	 *	
	 *	本来应该使用变参模板去做
	 *	但vs2012不支持
	 */
	template<int buffsize>
	std::string to_str(const char* format, ...)
	{
		char temp[buffsize] = {0};
		va_list list;
		long ret;

		va_start (list, format);
		ret = vsnprintf_s(temp, buffsize, format, list);
		assert(ret<buffsize);
		va_end (list);

		return temp;
	}

	/*
	 *	单线程版本
	 *	非线程安全但效率高一点
	 */
	template<int buffsize>
	const char* to_cstr(const char* format, ...)
	{
		static char static_buff[buffsize] = {0};
		va_list list;
		long ret;

		va_start (list, format);
		ret = vsnprintf_s(static_buff, buffsize, format, list);
		assert(ret<buffsize);
		va_end (list);

		return static_buff;
	}

	/*
	 *	一般情况下，可以使用这两个宏定义简化代码编写
	 */
	#define cstr to_cstr<128>
	#define sstr to_str<128>
}