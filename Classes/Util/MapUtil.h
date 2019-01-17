#pragma once
#ifndef __MAP_UTIL__
#define __MAP_UTIL__

#include "cocos2d.h"
USING_NS_CC;

class MapUtil
{
public:
	/**
	 *	把怪物安置到预定位置上
	 *	@objectsPoints 对象组 
	 */
	static void installMonsters(TMXObjectGroup* objectsPoints);
};

#endif // !__MAP_UTIL__
