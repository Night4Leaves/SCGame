#include "PauseDevice.h"

PauseDevice::PauseDevice()
{
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(PauseDevice::startPause),
		"start_pause",
		NULL);

	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(PauseDevice::endPause),
		"end_pause",
		NULL);
}

PauseDevice::~PauseDevice()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}
