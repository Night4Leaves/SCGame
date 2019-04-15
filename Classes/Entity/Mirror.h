#pragma once
#ifndef __MIRROR_H__
#define __MIRROR_H__

#include "CustomizeStruct.h"

class Mirror : public Node
{
public:
	CREATE_FUNC(Mirror);
	virtual bool init();
	virtual void update(float dt);

	void setMirrorPos(Point pos);

protected:
	Mirror();
	virtual ~Mirror();

private:
	Sprite* m_pSprite;
	float dtCount;
};

#endif // !__MIRROR_H__
