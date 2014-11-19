#pragma once
#include "mapobj.h"

class Block :
	public MapObj
{
public:
	virtual ~Block(void) = 0;
};

