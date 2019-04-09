#include "JsonUtil.h"
#include "PlayerInfo.h"

JsonUtil* JsonUtil::m_pJsonLoadUtil = NULL;

JsonUtil::JsonUtil()
	: m_bIsFirst(true)
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
	playerInfoList.swap(std::vector<PlayerData>());

	if (reader.parse(data, root, false) == true)
	{
		int num = root.size();
		for (int i = 0; i < num; i++)
		{
			PlayerData player;

			this->combatEntityDataLoading(player, root[i]);

			time_t t = time(0);

			player.i_dataNumber = t;
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
	if (m_vecPlayerSavedata.size() != 0
		|| !m_bIsFirst)
	{
		playerInfoList = m_vecPlayerSavedata;
		return;
	}

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
			player.i_dataNumber = root[i]["dataNumber"].asInt();
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

			m_vecPlayerSavedata.push_back(player);
		}
	}

	playerInfoList = m_vecPlayerSavedata;
	m_bIsFirst = false;
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

void JsonUtil::writeSavedata(const char * fileName /*= "json/savedata.json"*/)
{
	PlayerData playerData = PlayerInfo::getInstance()->getPlayerData();
	
	int size = m_vecPlayerSavedata.size();
	int i = 0;
	while (i < size)
	{
		if (playerData.i_dataNumber == m_vecPlayerSavedata[i].i_dataNumber)
		{
			m_vecPlayerSavedata[i] = playerData;
			break;
		}
		i++;
	}
	if (i == size)
	{
		m_vecPlayerSavedata.push_back(playerData);
		size++;
	}

	Json::FastWriter writer;
	Json::Value root;

	for (int i = 0; i < size; i++)
	{
		root[i]["playerName"] = m_vecPlayerSavedata[i].str_playerName;
		root[i]["dataNumber"] = m_vecPlayerSavedata[i].i_dataNumber;
		root[i]["characterName"] = m_vecPlayerSavedata[i].str_characterName;
		root[i]["HP"] = m_vecPlayerSavedata[i].i_HP;
		root[i]["attack"] = m_vecPlayerSavedata[i].i_attack;
		root[i]["money"] = m_vecPlayerSavedata[i].i_money;
		root[i]["xSpeed"] = m_vecPlayerSavedata[i].i_xSpeed;
		root[i]["ySpeed"] = m_vecPlayerSavedata[i].i_ySpeed;
		root[i]["attackRange"] = m_vecPlayerSavedata[i].i_attackRange;
		root[i]["level"] = m_vecPlayerSavedata[i].i_level;

		int temp = m_vecPlayerSavedata[i].vec_csActionName.size();
		for (int j = 0; j < temp; j++)
		{
			root[i]["actionName"][j] = m_vecPlayerSavedata[i].vec_csActionName[j];
		}

		temp = m_vecPlayerSavedata[i].vec_dActionTime.size();
		for (int j = 0; j < temp; j++)
		{
			root[i]["actionTime"][j] = m_vecPlayerSavedata[i].vec_dActionTime[j];
		}

		temp = m_vecPlayerSavedata[i].vec_iActionPlayTime.size();
		for (int j = 0; j < temp; j++)
		{
			root[i]["actionPlayTime"][j] = m_vecPlayerSavedata[i].vec_iActionPlayTime[j];
		}

		temp = m_vecPlayerSavedata[i].map_backpackItems.size();
		for (int j = 0; j < temp; j++)
		{
			std::string itemNamePIN = StringUtils::format("item%02dname", j + 1);
			std::string itemNumberPIN = StringUtils::format("item%02dnum", j + 1);
			auto test = m_vecPlayerSavedata[j].map_backpackItems.begin();
			root[i][itemNamePIN] = test->first;
			root[i][itemNumberPIN] = test->second;
		}

		temp = m_vecPlayerSavedata[i].map_skillList.size();
		
		root[i]["skillList"]["dynamics"] = m_vecPlayerSavedata[i].map_skillList["dynamics"];
		root[i]["skillList"]["neutralization"] = m_vecPlayerSavedata[i].map_skillList["neutralization"];
		root[i]["skillList"]["optics"] = m_vecPlayerSavedata[i].map_skillList["optics"];
		root[i]["skillList"]["electromagnetism"] = m_vecPlayerSavedata[i].map_skillList["electromagnetism"];
		root[i]["skillList"]["chemistry"] = m_vecPlayerSavedata[i].map_skillList["chemistry"];
		root[i]["skillList"]["battery"] = m_vecPlayerSavedata[i].map_skillList["battery"];
	}

	std::string json_file = writer.write(root);

	FILE* file = fopen(fileName, "w");
	fprintf(file, json_file.c_str());
	fclose(file);
}

void JsonUtil::deleteSavedata(int dataNumber)
{
	int size = m_vecPlayerSavedata.size();
	int i = 0;
	while (i < size)
	{
		if (dataNumber == m_vecPlayerSavedata[i].i_dataNumber)
		{
			break;
		}
		i++;
	}

	if (i < size - 1)
	{
		while (i != size - 1)
		{
			m_vecPlayerSavedata[i] = m_vecPlayerSavedata[i + 1];
			i++;
		}
		m_vecPlayerSavedata.pop_back();
	}
	else if (i == size - 1)
	{
		m_vecPlayerSavedata.pop_back();
	}


	Json::FastWriter writer;
	Json::Value root;
	size--;

	for (int i = 0; i < size; i++)
	{
		root[i]["playerName"] = m_vecPlayerSavedata[i].str_playerName;
		root[i]["dataNumber"] = m_vecPlayerSavedata[i].i_dataNumber;
		root[i]["characterName"] = m_vecPlayerSavedata[i].str_characterName;
		root[i]["HP"] = m_vecPlayerSavedata[i].i_HP;
		root[i]["attack"] = m_vecPlayerSavedata[i].i_attack;
		root[i]["money"] = m_vecPlayerSavedata[i].i_money;
		root[i]["xSpeed"] = m_vecPlayerSavedata[i].i_xSpeed;
		root[i]["ySpeed"] = m_vecPlayerSavedata[i].i_ySpeed;
		root[i]["attackRange"] = m_vecPlayerSavedata[i].i_attackRange;
		root[i]["level"] = m_vecPlayerSavedata[i].i_level;

		int temp = m_vecPlayerSavedata[i].vec_csActionName.size();
		for (int j = 0; j < temp; j++)
		{
			root[i]["actionName"][j] = m_vecPlayerSavedata[i].vec_csActionName[j];
		}

		temp = m_vecPlayerSavedata[i].vec_dActionTime.size();
		for (int j = 0; j < temp; j++)
		{
			root[i]["actionTime"][j] = m_vecPlayerSavedata[i].vec_dActionTime[j];
		}

		temp = m_vecPlayerSavedata[i].vec_iActionPlayTime.size();
		for (int j = 0; j < temp; j++)
		{
			root[i]["actionPlayTime"][j] = m_vecPlayerSavedata[i].vec_iActionPlayTime[j];
		}

		temp = m_vecPlayerSavedata[i].map_backpackItems.size() / 2;
		for (int j = 0; j < temp; j++)
		{
			std::string itemNamePIN = StringUtils::format("item%02dname", j + 1);
			std::string itemNumberPIN = StringUtils::format("item%02dnum", j + 1);
			auto test = m_vecPlayerSavedata[j].map_backpackItems.begin();
			root[i][itemNamePIN] = test->first;
			root[i][itemNumberPIN] = test->second;
		}

		temp = m_vecPlayerSavedata[i].map_skillList.size();

		root[i]["skillList"]["dynamics"] = m_vecPlayerSavedata[i].map_skillList["dynamics"];
		root[i]["skillList"]["neutralization"] = m_vecPlayerSavedata[i].map_skillList["neutralization"];
		root[i]["skillList"]["optics"] = m_vecPlayerSavedata[i].map_skillList["optics"];
		root[i]["skillList"]["electromagnetism"] = m_vecPlayerSavedata[i].map_skillList["electromagnetism"];
		root[i]["skillList"]["chemistry"] = m_vecPlayerSavedata[i].map_skillList["chemistry"];
		root[i]["skillList"]["battery"] = m_vecPlayerSavedata[i].map_skillList["battery"];
	}

	std::string json_file = writer.write(root);

	FILE* file = fopen("json/savedata.json", "w");
	fprintf(file, json_file.c_str());
	fclose(file);
}
