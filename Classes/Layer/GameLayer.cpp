#include "GameLayer.h"
#include "Entity/Player.h"
#include "Controller/PlayerController.h"
#include "Entity/Monster.h"
#include "Controller/MonsterController.h"
#include "Entity/AttackFlyingObject.h"

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		i_flyingObjectFlag = 0;

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::addAttackFlyingObject),
			"attack",
			NULL);

		m_pMap = TMXTiledMap::create("map/map_3-1.tmx");
		CC_BREAK_IF(m_pMap == nullptr);
		this->addChild(m_pMap);

		TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

		ValueMap monsterPoint = objGroup->getObject("monster");

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		Monster* monster = Monster::create("boss_01");
		monster->setPosition(Vec2(monsterX, monsterY));
		monster->idle();
		this->addChild(monster);

		MonsterController* monsterController = MonsterController::create();
		monster->setController(monsterController);
		this->addChild(monsterController);

		ValueMap playerPoint = objGroup->getObject("player");

		float playerX = playerPoint.at("x").asFloat();
		float playerY = playerPoint.at("y").asFloat();

		Player* player = Player::create("player_01");
		player->setMap(m_pMap);
		player->setPosition(Vec2(playerX, playerY));
		player->idle();
		this->addChild(player);
		m_pPlayer = player;

		PlayerController* playerController = PlayerController::create();
		CC_BREAK_IF(playerController == nullptr);
		m_pPlayerController = playerController;
		player->setController(playerController);
		this->addChild(playerController);

		for (int i = 0; i < 5; i++)
		{
			AttackFlyingObject* flyingObject = AttackFlyingObject::create("fireball");
			CC_BREAK_IF(flyingObject == nullptr);
			vector_pAttackFlyingObject.pushBack(flyingObject);
			this->addChild(flyingObject);
		}

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
	Vec2 vec2_flyingDistance = Vec2();	//飞行物飞行距离
	float f_xSpeed = 0.0f;	//飞行物X轴速度
	float f_ySpeed = 0.0f;	//飞行物Y轴速度
	float f_x = 0.0f;	//飞行物X轴起始位置
	float f_y = point_playerPoint.y + size_playerSize.height / 2;	//飞行物Y轴起始位置

	//根据飞行方向设置数值
	if (b_isRight)
	{
		f_x = point_playerPoint.x + size_playerSize.width / 2;	//飞行物X轴起始位置
		vec2_flyingDistance = Vec2(HORIZONTAL_DISTANCE, 0);		//飞行物飞行距离
		f_xSpeed = HORIZONTAL_SPPED + 1;	//飞行物X轴飞行速度
	}
	else
	{
		f_x = point_playerPoint.x - size_playerSize.width / 2;
		vec2_flyingDistance = Vec2(-HORIZONTAL_DISTANCE, 0);
		f_xSpeed = -HORIZONTAL_SPPED - 1;
	}

	AttackFlyingObject* p_flyingObject = (AttackFlyingObject*)vector_pAttackFlyingObject.at(i_flyingObjectFlag);
	p_flyingObject->setFlyingInformation(Point(f_x, f_y), vec2_flyingDistance, Point(f_xSpeed, f_ySpeed), b_isRight);

	i_flyingObjectFlag++;
	if (i_flyingObjectFlag == 5)
	{
		i_flyingObjectFlag = 0;
	}
}
