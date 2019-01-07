#pragma once
#ifndef __PORTAL_H__
#define __PORTAL_H__

#include "Entity.h"

class Portal : public Entity
{
public:
	CREATE_FUNC(Portal);
	virtual bool init();

	void checkPlayerPoint(Ref* pSender);

private:
	Portal();
	virtual ~Portal();
};

#endif // !__PORTAL_H__
