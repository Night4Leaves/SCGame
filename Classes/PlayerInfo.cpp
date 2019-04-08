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

void PlayerInfo::setItem(std::string item)
{
	m_sctData.map_backpackItems[item] = 1;
}

int PlayerInfo::getItemNum(std::string item)
{
	int num = m_sctData.map_backpackItems[item];
	return num;
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
