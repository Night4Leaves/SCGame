#pragma once
#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "CustomizeStruct.h"

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

protected:
	Sprite* m_pSprite;
};

#endif // !__ENTITY_H__
