#include "BossSkill.h"
#include "GameManager.h"
#include "Layer/GameLayer.h"
#include "Entity/BossFlyingObject.h"
#include "Entity/Monster.h"

BossSkill* BossSkill::m_pBossSkill = NULL;

BossSkill * BossSkill::getInstance()
{
	if (m_pBossSkill == NULL)
	{
		m_pBossSkill = new BossSkill();
		if (m_pBossSkill && m_pBossSkill->init())
		{
			m_pBossSkill->autorelease();
			m_pBossSkill->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_pBossSkill);
			m_pBossSkill = NULL;
		}
	}
	return m_pBossSkill;
}

void BossSkill::useSkill(SkillType skillType, Point playerPoint)
{
	switch (skillType)
	{
	case en_st_beam:
		this->shootBeam(playerPoint);
		break;
	case en_st_missile:
		this->launchingMissile(playerPoint);
		break;
	case en_st_summon:
		this->summon();
		break;
	case en_st_debuff:
		this->debuff();
		break;
	default:
		break;
	}
}

void BossSkill::setGameLayer(GameLayer * gameLayer)
{
	m_pGameLayer = gameLayer;
}

BossSkill::BossSkill()
{
}

BossSkill::~BossSkill()
{
}

bool BossSkill::init()
{
	return true;
}

void BossSkill::shootBeam(Point playerPoint)
{
	log("beam");
	Point bossPoint = m_pGameLayer->getBossPosition();
	bool isRight;
	if (bossPoint.x > playerPoint.x)
	{
		isRight = false;
	}
	else
	{
		isRight = true;
	}
	
	bossPoint.y += 20;

	BossFlyingObjectInfo info = {"boss_beam", bossPoint, Point(playerPoint.x, bossPoint.y), isRight, true};
	BossFlyingObject* object = BossFlyingObject::create(info);
	m_pGameLayer->addBossFlyingObject(object);
}

void BossSkill::launchingMissile(Point playerPoint)
{
	log("missile");
	BossFlyingObjectInfo info = { "boss_missile", Point(playerPoint.x, playerPoint.y + 150), playerPoint, false, false };
	BossFlyingObject* object = BossFlyingObject::create(info);
	m_pGameLayer->addBossFlyingObject(object);
}

void BossSkill::summon()
{
	log("summon");
	auto map = GameManager::getInstance()->getMap();
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	std::vector<MonsterData> monsterInfoList;
	JsonUtil::getInstance()->readMonsterInfo(monsterInfoList);

	ValueMap monsterPoint = objGroup->getObject("remonster_01");
	float monsterX = monsterPoint.at("x").asFloat();
	float monsterY = monsterPoint.at("y").asFloat();

	Monster* monster = Monster::create(monsterInfoList[13]);
	monster->setMonsterOriginPosition(Point(monsterX, monsterY));
	monster->idle();
	monster->setScale(0.35);
	m_pGameLayer->addMonster(monster);

	monsterPoint = objGroup->getObject("remonster_02");
	monsterX = monsterPoint.at("x").asFloat();
	monsterY = monsterPoint.at("y").asFloat();

	monster = Monster::create(monsterInfoList[13]);
	monster->setMonsterOriginPosition(Point(monsterX, monsterY));
	monster->idle();
	monster->setScale(0.35);
	m_pGameLayer->addMonster(monster);
}

void BossSkill::debuff()
{
	log("debuff");
}

