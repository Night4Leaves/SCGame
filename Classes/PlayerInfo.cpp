#include "PlayerInfo.h"

PlayerInfo* PlayerInfo::m_pPlayerInfo = NULL;

PlayerInfo * PlayerInfo::getInstance()
{
	if (m_pPlayerInfo == NULL)
	{
		m_pPlayerInfo = new PlayerInfo();
		if (m_pPlayerInfo && m_pPlayerInfo->init())
		{
			m_pPlayerInfo->autorelease();
			m_pPlayerInfo->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pPlayerInfo);
			m_pPlayerInfo = NULL;
		}
	}
	return m_pPlayerInfo;
}

void PlayerInfo::setPlayerData(PlayerData playerData)
{
	m_sctData = playerData;
}

PlayerData PlayerInfo::getPlayerData()
{
	return m_sctData;
}

void PlayerInfo::setMoney(int money)
{
	m_sctData.i_money = money;
	NotificationCenter::getInstance()->postNotification("update_score");
}

int PlayerInfo::getMoney()
{
	return m_sctData.i_money;
}

void PlayerInfo::setLevel(int level)
{
	if (m_sctData.i_level == level)
	{
		++m_sctData.i_level;
	}
}

int PlayerInfo::getLevel()
{
	return m_sctData.i_level;
}

void PlayerInfo::setAttack(int attack)
{
	if (m_sctData.i_attack < attack)
	{
		m_sctData.i_attack = attack;
	}
}

int PlayerInfo::getAttack()
{
	return m_sctData.i_attack;
}

void PlayerInfo::setShopItemType(ShopItemType shopItemType)
{
	m_enShopItemType = shopItemType;
}

void PlayerInfo::setItem(std::string item)
{
	m_sctData.map_backpackItems[item]++;
}

int PlayerInfo::getItemNum(std::string item)
{
	int num = m_sctData.map_backpackItems[item];
	return num;
}

void PlayerInfo::useItem()
{
	switch (m_enShopItemType)
	{
	case en_consumableItemType_bandaid:
		if (m_sctData.map_backpackItems["bandaid"] > 0)
		{
			m_sctData.map_backpackItems["bandaid"]--;
			NotificationCenter::getInstance()->postNotification("revocer_HP");
		}
		break;
	case en_consumableItemType_mirror:
		if (m_sctData.map_backpackItems["mirror"] > 0)
		{
			m_sctData.map_backpackItems["mirror"]--;
			NotificationCenter::getInstance()->postNotification("set_mirror");
		}
		break;
	case en_consumableItemType_sword:
		m_sctData.map_backpackItems["sword"];
		break;
	default:
		break;
	}
}

bool PlayerInfo::init()
{
	return true;
}

PlayerInfo::PlayerInfo()
{
}

PlayerInfo::~PlayerInfo()
{
}
