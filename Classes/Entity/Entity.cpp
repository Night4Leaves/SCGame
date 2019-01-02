#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::bindSprite(Sprite * sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);
}

Size Entity::getCollisionSize()
{
	return m_sprite->getContentSize();
}
