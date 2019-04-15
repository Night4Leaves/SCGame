#pragma once
#ifndef __DOOR_H__
#define __DOOR_H__

#include "CustomizeStruct.h"

class Door : public Node
{
public:
	CREATE_FUNC(Door);
	virtual bool init();
	virtual void update(float dt);

protected:
	Door();
	virtual ~Door();

private:
	void openDoor(Ref* pSender);

private:
	Sprite* m_pSprite;
};

#endif // !__DOOR_H__

