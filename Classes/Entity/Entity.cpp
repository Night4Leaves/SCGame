#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::bindSprite(Sprite * sprite)
{
	m_pSprite = sprite;
	this->addChild(m_pSprite);
}

