#pragma once
#ifndef __PANE_LAYER_H__
#define __PANE_LAYER_H__

#include "cocos2d.h"
#include "CustomizeStruct.h"

USING_NS_CC;

class Player;

class PaneLayer : public Layer
{
public:
	PaneLayer();
	virtual ~PaneLayer();

	CREATE_FUNC(PaneLayer);
	virtual bool init();	

private:
	//显示层
	void showPaneLayer(Ref* pSender);

	//打开商店
	void openStore();
	//暂停
	void startPause();

	//显示选择游戏关卡界面
	void selectGameScene();
	void selectGameScene_1_1(Ref* pSender);
	void selectGameScene_1_2(Ref* pSender);
	void selectGameScene_2_1(Ref* pSender);
	void selectGameScene_2_2(Ref* pSender);
	void selectGameScene_3_1(Ref* pSender);
	void selectGameScene_3_2(Ref* pSender);
	void selectGameScene_4_1(Ref* pSender);

	//打开背包
	void openBackpack();
	//打开技能列表
	void openSkilllist();

	//进入主场景
	void enterMainScene();
	//切换到主场景
	void changeMainScene(Ref* pSender);;
	//退出关卡
	void exitGameScene(Ref* pSender);

	//关闭当前显示的界面
	void menuCloseCallback(Ref* pSender);
	//创建新存档数据
	void createNewData();

	//选择玩家角色
	void selectCharacter();

	//选择载入的存档
	void loadFile();

	void gameEnd(bool isSuccess);

private:
	bool m_isOpen;	//层中是否显示内容
	bool m_isLoadSavedata;	//是否为存档数据

	std::vector<PlayerData> m_vecCharacterList;	//玩家角色数据列表
};

#endif // !__PANE_LAYER_H__
