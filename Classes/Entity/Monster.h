#pragma once
#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Entity.h"

class Monster : public Entity
{
public:
	Monster();
	virtual ~Monster();

	CREATE_FUNC(Monster);
	virtual bool init();
};

#endif // !__MONSTER_H__
