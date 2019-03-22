#include "JsonUtil.h"

JsonUtil* JsonUtil::m_pJsonLoadUtil = NULL;

JsonUtil::JsonUtil()
{
}

JsonUtil::~JsonUtil()
{
}

JsonUtil * JsonUtil::getInstance()
{
	if (m_pJsonLoadUtil == nullptr)
	{
		m_pJsonLoadUtil = new JsonUtil();
		if (m_pJsonLoadUtil && m_pJsonLoadUtil->init())
		{
			m_pJsonLoadUtil->autorelease();
			m_pJsonLoadUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pJsonLoadUtil);
			m_pJsonLoadUtil = nullptr;
		}
	}

	return m_pJsonLoadUtil;
}

bool JsonUtil::init()
{
	return true;
}

void JsonUtil::combatEntityDataLoading(CombatEntityData& combatEntityData, const Json::Value & data)
{
	combatEntityData.str_characterName = data["characterName"].asCString();
	combatEntityData.i_HP = data["HP"].asInt();
	combatEntityData.i_attack = data["attack"].asInt();
	combatEntityData.i_money = data["money"].asInt();
	combatEntityData.i_xSpeed = data["xSpeed"].asInt();
	combatEntityData.i_ySpeed = data["ySpeed"].asInt();
	combatEntityData.i_attackRange = data["attackRange"].asInt();

	Json::Value tempArr = data["actionName"];
	int tempArrSize = tempArr.size();
	for (int ii = 0; ii < tempArrSize; ++ii)
	{
		std::string tempStr = tempArr[ii].asCString();
		combatEntityData.vec_csActionName.push_back(tempStr.c_str());
	}

	tempArr = data["actionTime"];
	tempArrSize = tempArr.size();
	for (int ii = 0; ii < tempArrSize; ++ii)
	{
		double tempDouble = tempArr[ii].asDouble();
		combatEntityData.vec_dActionTime.push_back(tempDouble);
	}

	tempArr = data["actionPlayTime"];
	tempArrSize = tempArr.size();
	for (int ii = 0; ii < tempArrSize; ++ii)
	{
		int tempInt = tempArr[ii].asInt();
		combatEntityData.vec_iActionPlayTime.push_back(tempInt);
	}

}

void JsonUtil::readPlayerInfo(std::vector<PlayerData>& playerInfoList, const char * fileName /*= "json/player_info.json"*/)
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile(fileName);

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			PlayerData player;

			this->combatEntityDataLoading(player, root[i]);

			player.b_isMonster = false;

			player.map_skillList["dynamics"] = true;
			player.map_skillList["neutralization"] = false;
			player.map_skillList["optics"] = false;
			player.map_skillList["electromagnetism"] = false;
			player.map_skillList["chemistry"] = false;
			player.map_skillList["battery"] = false;

			playerInfoList.push_back(player);
		}
	}
}

void JsonUtil::readSavedata(std::vector<PlayerData>& playerInfoList, const char * fileName /*= "json/savedata.json"*/)
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile(fileName);

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			PlayerData player;

			this->combatEntityDataLoading(player, root[i]);

			player.str_playerName = root[i]["playerName"].asCString();
			player.i_level = root[i]["level"].asInt();
			player.b_isMonster = false;

			player.map_skillList["dynamics"] = root[i]["skillList"]["dynamics"].asBool();
			player.map_skillList["neutralization"] = root[i]["skillList"]["neutralization"].asBool();
			player.map_skillList["optics"] = root[i]["skillList"]["optics"].asBool();
			player.map_skillList["electromagnetism"] = root[i]["skillList"]["electromagnetism"].asBool();
			player.map_skillList["chemistry"] = root[i]["skillList"]["chemistry"].asBool();
			player.map_skillList["battery"] = root[i]["skillList"]["battery"].asBool();

			int backpackArraySize = root[i]["backpackItems"].size();
			int backpackSize = backpackArraySize / 2;

			for (int ii = 1; ii < backpackSize + 1; ++ii)
			{
				std::string itemNamePIN = StringUtils::format("item%02dname", ii);
				std::string itemNumberPIN = StringUtils::format("item%02dnum", ii);

				const char* itemName = root[i]["backpackItems"][itemNamePIN].asCString();
				int itemNumber = root[i]["backpackItems"][itemNumberPIN].asInt();

				player.map_backpackItems[itemName] = itemNumber;
			}

			playerInfoList.push_back(player);
		}
	}
}

void JsonUtil::readMonsterInfo(std::vector<MonsterData>& monsterInfoList, const char * fileName /*= "json/monster_info.json"*/)
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile(fileName);

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			MonsterData monster;

			this->combatEntityDataLoading(monster, root[i]);

			monster.i_warningRange = root[i]["warningRange"].asInt();
			monster.i_attackCDTime = root[i]["attackCDTime"].asInt();
			monster.b_isFlying = root[i]["flying"].asBool();
			monster.b_isAttackMove = root[i]["attackMove"].asBool();
			monster.b_isMonster = true;

			monsterInfoList.push_back(monster);
		}
	}
}

void JsonUtil::readBossInfo(std::vector<BossData>& bossInfoList, const char * fileName /*= "json/boss_info.json"*/)
{
	Json::Reader reader;
	Json::Value root;

	std::string data = FileUtils::getInstance()->getStringFromFile(fileName);

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			BossData boss;

			this->combatEntityDataLoading(boss, root[i]);

			boss.b_isMonster = true;

			boss.i_firstSkillDamage = root[i]["firstSkillDamage"].asInt();
			boss.i_firstSkillCDTime = root[i]["firstSkillCDTime"].asInt();
			boss.i_secondSkillDamage = root[i]["secondSkillDamage"].asInt();
			boss.i_secondSkillCDTime = root[i]["secondSkillCDTime"].asInt();
			boss.i_thirdSkillDamage = root[i]["thirdSkillDamage"].asInt();
			boss.i_thirdSkillCDTime = root[i]["thirdSkillCDTime"].asInt();
			

			bossInfoList.push_back(boss);
		}
	}
}
