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

//物理系场景道具所属分组
enum PhysicsSceneItemGroup
{
	en_psig_null,	//无组别
	en_psig_lever,	//杠杆组
	en_psig_pulley,	//滑轮组
	en_psig_electromagnetism	//电磁组
};

//杠杆部件
enum LeverPart
{
	en_leverPart_fulcrum,	//杠杆支点
	en_leverPart_rod,	//杠杆
	en_leverPart_stone	//杠杆阻力物
};

//滑轮部件
enum PulleyPart
{
	en_pulleyPart_pulley,	//滑轮
	en_pulleyPart_fulcrum,	//支点
	en_pulleyPart_bracket,	//支架
	en_pulleyPart_rope	//绳子
};

//电磁部件
enum RailgunPart
{
	en_railgunPart_battery,	//电池
	en_railgunPart_powerBox,	//电池盒
	en_railgunPart_barrel,	//主体
	en_railgunPart_shell	//发射物
};

enum ConsumableItemType
{
	en_consumableItemType_recovery,
	en_consumableItemType_sceneItem,
	en_consumableItemType_fe,
	en_consumableItemType_cu,
	en_consumableItemType_ag
};

enum SkillType
{
	en_st_closeCombet,
	en_st_beam,
	en_st_missile,
	en_st_summon,
	en_st_debuff,
	en_st_recovery
};
#endif // !__CUSTOMIZE_ENUM_H__
