#include "cocos2d.h"

class Effect : public cocos2d::Node
{
public:

	static cocos2d::Sequence* fromName(const char* animation_name, int loop_times = 1);
	//static cocos2d::Animate* fromFiles(const char* format, int end, int start=0);

private:
	void onAnimateFinished();
};
