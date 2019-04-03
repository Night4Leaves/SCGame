#include "RailgunSceneItem.h"

RailgunSceneItem * RailgunSceneItem::create(const SceneItemInfomation & sceneItemInfo)
{
	RailgunSceneItem *pRet = new(std::nothrow) RailgunSceneItem();
	if (pRet && pRet->init(sceneItemInfo))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void RailgunSceneItem::setRailgunPart(RailgunPart railgunPart)
{
	m_enRailgunPart = railgunPart;
	switch (railgunPart)
	{
	case en_railgunPart_battery:
		break;
	case en_railgunPart_barrel:
		break;
	case en_railgunPart_shell:
		break;
	default:
		break;
	}

}

void RailgunSceneItem::startPause(Ref * pSender)
{
}

void RailgunSceneItem::endPause(Ref * pSender)
{
}

RailgunSceneItem::RailgunSceneItem()
{
}

RailgunSceneItem::~RailgunSceneItem()
{
}

void RailgunSceneItem::checkEnd(Ref * pSender)
{
}

void RailgunSceneItem::checkPlayerPoint(Ref * pSender)
{
}

void RailgunSceneItem::changeBatteryStatus(Point setPos)
{
}
