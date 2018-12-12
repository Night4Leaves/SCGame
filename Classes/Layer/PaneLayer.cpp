#include "PaneLayer.h"

PaneLayer::PaneLayer()
{
}

PaneLayer::~PaneLayer()
{
}

bool PaneLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		return true;
	} while (0);
	return false;
}
