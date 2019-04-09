#pragma once
#ifndef __BOSS_FLYING_OBJECT_H__
#define __BOSS_FLYING_OBJECT_H__

#include "FlyingObject.h"

class BossFlyingObject : public FlyingObject
{
public:
	static BossFlyingObject* create(BossFlyingObjectInfo info);
	virtual bool init(BossFlyingObjectInfo info);
	virtual void update(float dt);

	void stopFlying(Ref* pSender);

protected:
	BossFlyingObject();
	virtual ~BossFlyingObject();

private:
	bool m_bIsBeam;
};

#endif // !__BOSS_FLYING_OBJECT_H__
