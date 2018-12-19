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
	 *	�󶨾������
	 *	@sprite	�������
	 */
	void bindSprite(Sprite* sprite);

	/**
	 *	������ɫ�������ؽ���������
	 */
	void createAnimations();

protected:
	Sprite* m_sprite;
};

#endif // !__ENTITY_H__
