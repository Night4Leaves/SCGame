#include "SCController.h"

SCController::SCController()
{
}

SCController::~SCController()
{
}

void SCController::setControllerListner(PlayerControllerListener * controllerListener)
{
	this->m_pControllerListener = controllerListener;
}
