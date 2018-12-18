#include "SCController.h"

SCController::SCController()
{
}

SCController::~SCController()
{
}

void SCController::setControllerListner(GeneralControllerListener * controllerListener)
{
	this->m_pControllerListener = controllerListener;
}
