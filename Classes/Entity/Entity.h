#pragma once
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;

class Entity : public Node
{
public:
	Entity();
	virtual ~Entity();

	/**
	 *	绑定精灵对象
	 *	@sprite	精灵对象
	 */
	void bindSprite(Sprite* sprite);

	/**
	 *	创建角色动画加载进动画缓存
	 */
	void createAnimations();

protected:
	Sprite* m_sprite;
};

#endif // !__ENTITY_H__
