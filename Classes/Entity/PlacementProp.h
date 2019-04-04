#pragma once
#ifndef __PLACEMENT_PROP_H__
#define __PLACEMENT_PROP_H__

#include "PortableProp.h"

class PlacementProp : public PortableProp
{
public:
	virtual void checkPropType(Ref* pSender);

protected:
	PlacementProp();
	virtual ~PlacementProp();
};

#endif // !__PLACEMENT_PROP_H__
