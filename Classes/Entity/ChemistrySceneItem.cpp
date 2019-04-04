#include "ChemistrySceneItem.h"

ChemistrySceneItem * ChemistrySceneItem::cteate(const SceneItemInfomation & sceneItemInfo)
{
	ChemistrySceneItem *pRet = new(std::nothrow) ChemistrySceneItem();
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

void ChemistrySceneItem::startPause(Ref * pSender)
{
}

void ChemistrySceneItem::endPause(Ref * pSender)
{
}

ChemistrySceneItem::ChemistrySceneItem()
{
}

ChemistrySceneItem::~ChemistrySceneItem()
{
}

void ChemistrySceneItem::checkItemType(Ref * pSender)
{
	int check = (int)pSender;
	switch (check)
	{
	case en_consumableItemType_recovery:
		break;
	case en_consumableItemType_sceneItem:
		break;
	case en_consumableItemType_fe:
		if (m_enPH == en_ph_strongAcid)
		{

		}
		break;
	case en_consumableItemType_cu:
		break;
	case en_consumableItemType_ag:
		break;
	default:
		break;
	}
}
