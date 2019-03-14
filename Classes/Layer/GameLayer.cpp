#include "GameLayer.h"
#include "Entity/Player.h"
#include "Entity/Monster.h"
#include "Entity/AttackFlyingObject.h"
#include "Controller/PlayerController.h"

GameLayer::GameLayer()
	: m_iFlyingObjectFlag(0)
	, m_iMonsterWarningRange(0)
{
}

GameLayer::~GameLayer()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

bool GameLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::addAttackFlyingObject),
			"set_attack_flying_object",
			NULL);
		
		return true;
	} while (0);

	log("GameLayer initialize failed!");

	return false;
}

void GameLayer::addAttackFlyingObject(Ref * pSender)
{
	Point point_playerPoint = m_pPlayer->getPosition();		//玩家坐标
	Size size_playerSize = m_pPlayer->getCollisionSize();	//玩家形象大小
	bool b_isRight = m_pPlayerController->getIsRight();		//玩家是否朝右

	float f_x = 0.0f;	//飞行物X轴起始位置
	float f_y = point_playerPoint.y + size_playerSize.height / 2;	//飞行物Y轴起始位置

	//根据飞行方向设置数值
	if (b_isRight)
	{
		f_x = point_playerPoint.x + size_playerSize.width / 2;	//飞行物X轴起始位置
	}
	else
	{
		f_x = point_playerPoint.x - size_playerSize.width / 2;
	}

	AtkFlyObjPosInfo temp = { Point(f_x, f_y), b_isRight, point_playerPoint, Point() };

	AttackFlyingObject* p_flyingObject = (AttackFlyingObject*)vector_pAttackFlyingObject.at(m_iFlyingObjectFlag);
	p_flyingObject->setFlyingInformation(temp);

	m_iFlyingObjectFlag++;
	if (m_iFlyingObjectFlag == 3)
	{
		m_iFlyingObjectFlag = 0;
	}
}

void GameLayer::setGameScene_1_1(PlayerData & playerData)
{
	m_pMap = TMXTiledMap::create("map/map_1-1.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	std::vector<MonsterData> monsterInfoList;
	JsonUtil::getInstance()->readMonsterInfo(monsterInfoList);

	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		Monster* monster = Monster::create(monsterInfoList[0]);
		monster->setMonsterPosition(Vec2(monsterX, monsterY));
		monster->idle();
		monster->setScale(0.35);
		this->addChild(monster);
	}

	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	Monster* boss = Monster::create(monsterInfoList[0]);
	boss->setMonsterPosition(Vec2(bossX, bossY));
	boss->idle();
	this->addChild(boss);

	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	m_sctPlayerData = playerData;

	m_pPlayer = Player::create(m_sctPlayerData);
	m_pPlayer->setPosition(playerX, playerY);
	m_pPlayer->idle();
	this->addChild(m_pPlayer);

	PlayerController* playerController = PlayerController::create();
	m_pPlayerController = playerController;
	m_pPlayer->setController(m_pPlayerController);
	this->addChild(m_pPlayerController);

	m_pPlayerController->setMap(m_pMap);

	AtkFlyObjIniInfo fireballInfo = { "fireball", Vec2(m_sctPlayerData.i_attackRange, 0), Vec2(m_sctPlayerData.i_xSpeed + 1, 0), m_sctPlayerData.i_attack };
	for (int i = 0; i < 3; i++)
	{
		AttackFlyingObject* flyingObject = AttackFlyingObject::create(fireballInfo);
		CC_BREAK_IF(flyingObject == nullptr);
		vector_pAttackFlyingObject.pushBack(flyingObject);
		this->addChild(flyingObject);
	}
}
