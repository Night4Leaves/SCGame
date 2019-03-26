#pragma once
#ifndef __CUSTOMIZE_ENUM_H__
#define __CUSTOMIZE_ENUM_H__

//显示层会收到的展示内容消息
enum PaneLayerStatus
{
	en_paneMsg_selectCharacter,	//角色选择
	en_paneMsg_loadFile,	//存档加载
	en_paneMsg_openItemStore,	//打开道具商店
	en_paneMsg_openSkillStore,	//打开技能商店
	en_paneMsg_pause,	//暂停
	en_paneMsg_selectGameScene,	//选择关卡
	en_paneMsg_openBackpack,	//打开背包
	en_paneMsg_openSkilllist,	//打开技能列表
	en_paneMsg_gameOver,	//过关失败
	en_paneMsg_gameClear	//过关成功
};

//酸碱指示
enum PH
{
	en_ph_strongAcid,	//强酸
	en_ph_weakAcid,	//弱酸
	en_ph_neutral,	//中性
	en_ph_weakAlkali,	//弱碱
	en_ph_strongAlkali	//强碱
};

//场景道具种类
enum SceneItemType
{
	en_sceneItem_special,	//特殊类
	en_sceneItem_physics,	//物理类
	en_sceneItem_chemistry	//化学类
};

#endif // !__CUSTOMIZE_ENUM_H__
