#pragma once
#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameManager : public Ref
{
public:
	static GameManager * getInstance();
	virtual bool init();

	//保存块地图
	void setMap(TMXTiledMap* map);
	TMXTiledMap* getMap();
	//获取地图尺寸
	Size getMapSize();

	//计算脚下砖块在块地图中的坐标
	Point tileCoordForPosition(Point pos);
	//检测指定属性的值
	bool checkBoolAttribute(Point tiledPos, const char* attribute);

	void setCheckPoint(Point pos);
	Point getCheckPoint();

private:
	GameManager();
	~GameManager();

private:
	static GameManager* m_pGameManager;	//游戏管理器对象

	TMXTiledMap* m_pMap;	//记录地图
	TMXLayer* m_pMeta;		//障碍判定层

	Size m_sizeMap;	//地图尺寸

	Point tmp_pos;
	bool m_bCheck;
};

#endif // !__GAME_MANAGER_H__
