#pragma once
#ifndef __JSON_UTIL_H__
#define __JSON_UTIL_H__

#include "cocos2d.h"
USING_NS_CC;
#include "Json/json.h"
#include "CustomizeStruct.h"

class JsonUtil : public Ref
{
public:
	static JsonUtil* getInstance();
	virtual bool init();

	/**
	*	将CombatEntityData中的数据进行装载
	*	@combatEntityData	CombatEntityData结构体
	*	@data	Json::Value
	*/
	void combatEntityDataLoading(CombatEntityData& combatEntityData, const Json::Value & data);

	/**
	*	读取角色信息文件
	*	@playerInfoList	存放角色数据结构体(struct)的vector
	*	@fileName	存放角色信息的文件地址，默认地址为Resources下的"json/player_info.json"
	*/
	void readPlayerInfo(std::vector<PlayerData>& playerInfoList, const char * fileName = "json/player_info.json");

	/**
	*	读取存档文件
	*	@playerInfoList	存放角色数据结构体(struct)的vector
	*	@fileName	存档的文件地址，默认地址为Resources下的"json/savedata.json"
	*/
	void readSavedata(std::vector<PlayerData>& playerInfoList, const char * fileName = "json/savedata.json");

	/**
	*	读取怪物信息文件
	*	@monsterInfoList	存放怪物数据结构体(struct)的vector
	*	@fileName	存放怪物信息的文件地址，默认地址为Resources下的"json/monster_info.json"
	*/
	void readMonsterInfo(std::vector<MonsterData>& monsterInfoList, const char * fileName = "json/monster_info.json");

	/**
	*	读取Boss信息文件
	*	@bossInfoList	存放Boss数据结构体(struct)的vector
	*	@fileName	存放Boss信息的文件地址，默认地址为Resources下的"json/boss_info.json"
	*/
	void readBossInfo(std::vector<BossData>& bossInfoList, const char * fileName = "json/boss_info.json");

private:
	JsonUtil();
	~JsonUtil();

private:
	static JsonUtil* m_pJsonLoadUtil;
};

#endif // !__JSON_UTIL_H__
