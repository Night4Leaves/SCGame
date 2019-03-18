#include "GameManager.h"

GameManager* GameManager::m_pGameManager = NULL;

GameManager * GameManager::getInstance()
{
	if (m_pGameManager == NULL)
	{
		m_pGameManager = new GameManager();
		if (m_pGameManager && m_pGameManager->init())
		{
			m_pGameManager->autorelease();
			m_pGameManager->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pGameManager);
			m_pGameManager = NULL;
		}
	}
	return m_pGameManager;
}

bool GameManager::init()
{
	return true;
}

void GameManager::setMap(TMXTiledMap * map)
{
	m_pMap = map;
	m_pMeta = m_pMap->getLayer("meta");

	Size mapTiledNum = m_pMap->getMapSize();	//获得地图中块的数量
	Size tiledSize = m_pMap->getTileSize();		//获得地图中块的尺寸

	m_sizeMap = Size(mapTiledNum.width * tiledSize.width,
					mapTiledNum.height * tiledSize.height);

}

Point GameManager::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = m_pMap->getMapSize();
	Size tiledSize = m_pMap->getTileSize();

	float x = pos.x / tiledSize.width * 1.0;

	float y = (m_sizeMap.height - pos.y) / tiledSize.height * 1.0;	//块地图的Y轴坐标与cocos2dx是相反的

	if (x - mapTiledNum.width >= 0)
	{
		x = mapTiledNum.width - 1;
	}
	else if (x < 0)
	{
		x = 0;
	}

	if (y - mapTiledNum.height >= 0)
	{
		y = mapTiledNum.height - 1;
	}
	else if (y < 0)
	{
		y = 0;
	}

	return Point(x, y);
}

bool GameManager::checkBoolAttribute(Point tiledPos, const char * attribute)
{
	int tiledGid = m_pMeta->getTileGIDAt(tiledPos);

	if (tiledGid != 0)
	{
		//根据GID取得该图块的属性集
		Value properties = m_pMap->getPropertiesForGID(tiledGid);

		auto collidableProp = properties.asValueMap().at(attribute);

		if (!collidableProp.isNull() && collidableProp.asBool())
		{
			return true;
		}
	}

	return false;

}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

