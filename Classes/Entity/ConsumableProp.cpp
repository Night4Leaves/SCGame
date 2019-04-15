//#include "ConsumableProp.h"
//
//void ConsumableProp::checkPropType(Ref * pSender)
//{
//	if (m_bIsTake)
//	{
//		switch (m_enPropType)
//		{
//		case en_consumableItemType_recovery:
//			NotificationCenter::getInstance()->postNotification("prop_type", (Ref*)en_consumableItemType_recovery);
//			break;
//		case en_consumableItemType_sceneItem:
//			NotificationCenter::getInstance()->postNotification("prop_type", (Ref*)en_consumableItemType_sceneItem);
//			break;
//		case en_consumableItemType_fe:
//			NotificationCenter::getInstance()->postNotification("prop_type", (Ref*)en_consumableItemType_fe);
//			break;
//		case en_consumableItemType_cu:
//			NotificationCenter::getInstance()->postNotification("prop_type", (Ref*)en_consumableItemType_cu);
//			break;
//		case en_consumableItemType_ag:
//			NotificationCenter::getInstance()->postNotification("prop_type", (Ref*)en_consumableItemType_ag);
//			break;
//		default:
//			break;
//		}
//	}
//}
//
//void ConsumableProp::setPropType(ConsumableItemType propType)
//{
//	m_enPropType = propType;
//}
//
//ConsumableProp::ConsumableProp()
//{
//}
//
//ConsumableProp::~ConsumableProp()
//{
//}
