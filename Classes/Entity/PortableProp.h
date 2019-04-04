#pragma once
#ifndef __PORTABLE_PROP_H__
#define __PORTABLE_PROP_H__

#include "CustomizeStruct.h"

class PortableProp : public Node
{
public:
	virtual void checkPropType(Ref* pSender) = 0;

protected:
	PortableProp();
	virtual ~PortableProp();

protected:
	bool m_bIsTake;	//是否是玩家携带中
};

#endif // !__PORTABLE_PROP_H__
