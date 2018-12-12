#include "SCController.h"

SCController::SCController()
{
}

SCController::~SCController()
{
}

void SCController::setControllerListner(ControllerListener * controllerListener)
{
	this->m_pControllerListener = controllerListener;
}
