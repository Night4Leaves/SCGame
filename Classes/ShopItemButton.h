#pragma once
#ifndef __SHOP_ITEM_BUTTON_H__
#define __SHOP_ITEM_BUTTON_H__

#include "CustomizeStruct.h"

class ShopItemButton : public Node
{
public:
	static ShopItemButton * create(ShopItemInfo itemInfo);
	virtual bool init(ShopItemInfo itemInfo);

	void setStoreVol();
	void setBackpackVol();

protected:
	ShopItemButton();
	virtual ~ShopItemButton();

private:
	void buyItem(Ref* pSender);
	void equipItem(Ref* pSender);

private:
	ShopItemType m_enShopItemType;
	std::string m_strName;
	Sprite* m_pItemSprite;
	Menu* m_pMenu;
	int m_iNum;
	int m_iPrice;
};

#endif // !__SHOP_ITEM_BUTTON_H__
