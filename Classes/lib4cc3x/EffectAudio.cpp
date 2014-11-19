#include "EffectAudio.h"
#include "algorithm"

using namespace lib4cc3x;
using namespace std;


inline float clockToSecond(clock_t clock)
{
	return clock/static_cast<float>(CLOCKS_PER_SEC);
}

inline clock_t secondToClock(float second)
{
	return second*CLOCKS_PER_SEC;
}


EffectAudio::EffectAudio()
	:m_limit_second(OptimalLowerLimitForAndroid)
{

}

unsigned int EffectAudio::playEffect( const char* pszFileName, bool bLoop/*=false*/ )
{
	unsigned int ret_id = 0;

	audio2play::iterator iter = m_audio2playtime.find(pszFileName);
	if (iter == m_audio2playtime.end())
	{
		m_audio2playtime[pszFileName] = clock();
		ret_id = SimpleAudioEngine::getInstance()->playEffect(pszFileName, bLoop);
	}
	else
	{
		clock_t cur = clock();

		struct greater_equal_pair_clock
		{
			greater_equal_pair_clock(clock_t clock):m_clock(clock){};
			bool operator() (const pair<string, clock_t>& data)
			{
				return (data.second>=m_clock);
			}
		private:
			clock_t m_clock;
		};
		size_t size = count_if( m_audio2playtime.begin(), m_audio2playtime.end(), greater_equal_pair_clock(cur-secondToClock(m_limit_second)) );
		
		if ( clockToSecond(cur - iter->second) >= m_limit_second*size )
		{
			iter->second = clock();
			ret_id = SimpleAudioEngine::getInstance()->playEffect(pszFileName, bLoop);
		}
	}
	
	return ret_id;
}

void EffectAudio::setLowerLimit( float second )
{
	m_limit_second = second;
}
