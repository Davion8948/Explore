/*
 * CocosDenshion提供的SimpleAudioEngine
 * 当同时播放大量声音时会卡死
 * 
 * EffectAudio封装了SimpleAudioEngine的playEffect动作
 * 当effect的播放过于密集时
 * 不响应新添加的声音
 *
*/
#pragma once

#include "SimpleAudioEngine.h"
#include <map>
#include <string>
#include <time.h>


namespace lib4cc3x
{
	using namespace CocosDenshion;

	static const float OptimalLowerLimitForAndroid = 0.05f;

	class EffectAudio
	{
	public:
		EffectAudio();

		unsigned int playEffect(const char* pszFileName, bool bLoop=false);

		/*
		 * 预设值为OptimalLowerLimitForAndroid
		 * 可以通过这个函数设置新的时间下限
		 * 控制多长时间内
		 * 当同样的声音需要播放
		 * EffectAudio不理会这次请求
		*/
		void setLowerLimit(float second);

	private:
		typedef std::map<std::string, clock_t> audio2play;
		audio2play m_audio2playtime;//audio_file to last_played_time

		float m_limit_second;//in second
	};
}
