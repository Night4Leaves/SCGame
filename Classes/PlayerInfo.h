#pragma once
#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include "CustomizeStruct.h"

class PlayerInfo : public Ref
{
public:
	static PlayerInfo * getInstance();

	void setPlayerData(PlayerData playerData);
	PlayerData getPlayerData();

	void setMoney(int money);
	int getMoney();
	void setLevel(int level);
	int getLevel();
	void setAttack(int attack);
	int getAttack();
	void setShopItemType(ShopItemType shopItemType);

	void setItem(std::string item);
	int getItemNum(std::string item);
	void useItem();

private:
	virtual bool init();

	PlayerInfo();
	virtual ~PlayerInfo();

private:
	PlayerData m_sctData;
	static PlayerInfo* m_pPlayerInfo;
	ShopItemType m_enShopItemType;
};

#endif // !__PLAYER_INFO_H__
