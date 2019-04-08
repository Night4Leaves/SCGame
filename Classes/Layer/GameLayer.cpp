#include "GameLayer.h"
#include "Scene/MainScene.h"
#include "Entity/Player.h"
#include "Entity/Monster.h"
#include "Entity/AttackFlyingObject.h"
#include "Entity/BossTianzhao.h"
#include "Entity/LeverSceneItem.h"
#include "Entity/PulleySceneItem.h"
#include "Entity/RailgunSceneItem.h"
#include "Controller/PlayerController.h"
#include "GameManager.h"

#include "Layer/SceneItemLayer.h"

GameLayer::GameLayer()
	: m_iFlyingObjectFlag(0)
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

		//读取怪物数据信息
		JsonUtil::getInstance()->readMonsterInfo(monsterInfoList);
		JsonUtil::getInstance()->readBossInfo(bossDataList);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::addAttackFlyingObject),
			"set_attack_flying_object",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::updateScore),
			"update_score",
			NULL);

		NotificationCenter::getInstance()->addObserver(
			this,
			callfuncO_selector(GameLayer::enterMainScene),
			"exit_game_scene",
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

	//根据飞行方向设置X轴起始位置
	if (b_isRight)
	{
		f_x = point_playerPoint.x + size_playerSize.width / 2;
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
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_1-1.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	auto sceneItemLayer = SceneItemLayer::create();
	this->addChild(sceneItemLayer);

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	//ValueMap fulcrumPoint = objGroup->getObject("scene_item_pulley_fulcrum");
	//SceneItemInfomation itemInfo = { "scene_item_pulley", Point(fulcrumPoint.at("x").asFloat(), fulcrumPoint.at("y").asFloat()), false, en_sceneItem_physics };
	//PulleySceneItem* sceneItem = PulleySceneItem::create(itemInfo);
	//sceneItem->setPulleyPart(en_pulleyPart_fulcrum);
	//sceneItemLayer->setSceneitem(sceneItem);

	//ValueMap pulleyPoint = objGroup->getObject("scene_item_pulley_pulley");
	//itemInfo = { "scene_item_pulley", Point(pulleyPoint.at("x").asFloat(), pulleyPoint.at("y").asFloat()), true, en_sceneItem_physics };
	//sceneItem = PulleySceneItem::create(itemInfo);
	//sceneItem->setPulleyPart(en_pulleyPart_pulley);
	//sceneItemLayer->setSceneitem(sceneItem);

	ValueMap stonePoint = objGroup->getObject("scene_item_lever_stone");
	SceneItemInfomation itemInfo = { "scene_item_stone", Point(stonePoint.at("x").asFloat(), stonePoint.at("y").asFloat()), false, en_sceneItem_physics, en_ph_neutral, en_psig_lever };
	LeverSceneItem* sceneItem = LeverSceneItem::create(itemInfo);
	sceneItem->setLeverPart(en_leverPart_stone);
	sceneItemLayer->setSceneitem(sceneItem);

	ValueMap fulcrumPoint = objGroup->getObject("scene_item_lever_fulcrum");
	itemInfo = { "scene_item_fulcrum", Point(fulcrumPoint.at("x").asFloat(), fulcrumPoint.at("y").asFloat()), false, en_sceneItem_physics, en_ph_neutral, en_psig_lever };
	sceneItem = LeverSceneItem::create(itemInfo);
	sceneItem->setLeverPart(en_leverPart_fulcrum);
	sceneItemLayer->setSceneitem(sceneItem);

	ValueMap rodPoint = objGroup->getObject("scene_item_lever_rod");
	itemInfo = { "scene_item_rod", Point(rodPoint.at("x").asFloat(), rodPoint.at("y").asFloat()), true, en_sceneItem_physics, en_ph_neutral, en_psig_lever };
	sceneItem = LeverSceneItem::create(itemInfo);
	sceneItem->setLeverPart(en_leverPart_rod);
	sceneItemLayer->setSceneitem(sceneItem);

	//根据读取到的怪物信息创建怪物对象
	//根据地图文件中预设的坐标信息放置怪物对象
	//int i = 1;
	//while (true)
	//{
	//	std::string monsterPointID = StringUtils::format("monster_%02d", i++);
	//	ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
	//	CC_BREAK_IF(monsterPoint.empty());

	//	float monsterX = monsterPoint.at("x").asFloat();
	//	float monsterY = monsterPoint.at("y").asFloat();

	//	if (i % 2 == 0)
	//	{
	//		Monster* monster = Monster::create(monsterInfoList[3]);
	//		monster->setMonsterOriginPosition(Point(monsterX, monsterY));
	//		monster->idle();
	//		monster->setScale(0.35);
	//		this->addChild(monster);
	//	}
	//	else
	//	{
	//		Monster* monster = Monster::create(monsterInfoList[6]);
	//		monster->setMonsterOriginPosition(Point(monsterX, monsterY));
	//		monster->idle();
	//		monster->setScale(0.35);
	//		this->addChild(monster);
	//	}

	//}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[0]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setGameScene_1_2(PlayerData & playerData)
{
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_1-2.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	this->addChild(SceneItemLayer::create());

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	//根据读取到的怪物信息创建怪物对象
	//根据地图文件中预设的坐标信息放置怪物对象
	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		if (i % 2 == 0)
		{
			Monster* monster = Monster::create(monsterInfoList[0]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		else
		{
			Monster* monster = Monster::create(monsterInfoList[4]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}

	}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[1]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setGameScene_2_1(PlayerData & playerData)
{
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_2-1.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	this->addChild(SceneItemLayer::create());

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	//根据读取到的怪物信息创建怪物对象
	//根据地图文件中预设的坐标信息放置怪物对象
	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		if (i % 3 == 0)
		{
			Monster* monster = Monster::create(monsterInfoList[1]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		if(i % 3 == 1)
		{
			Monster* monster = Monster::create(monsterInfoList[11]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		if (i % 3 == 2)
		{
			Monster* monster = Monster::create(monsterInfoList[5]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}

	}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[4]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setGameScene_2_2(PlayerData & playerData)
{
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_2-2.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	auto sceneItemLayer = SceneItemLayer::create();
	this->addChild(sceneItemLayer);

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	ValueMap shellPoint = objGroup->getObject("scene_item_railgun_shell");
	SceneItemInfomation itemInfo = { "scene_item_shell", Point(shellPoint.at("x").asFloat(), shellPoint.at("y").asFloat()), false, en_sceneItem_physics };
	RailgunSceneItem* sceneItem = RailgunSceneItem::create(itemInfo);
	sceneItem->setRailgunPart(en_railgunPart_shell);
	sceneItemLayer->setSceneitem(sceneItem);

	ValueMap barrelPoint = objGroup->getObject("scene_item_railgun_barrel");
	itemInfo = { "scene_item_barrel", Point(barrelPoint.at("x").asFloat(), barrelPoint.at("y").asFloat()), false, en_sceneItem_physics };
	sceneItem = RailgunSceneItem::create(itemInfo);
	sceneItem->setRailgunPart(en_railgunPart_barrel);
	sceneItemLayer->setSceneitem(sceneItem);

	ValueMap powerBoxPoint = objGroup->getObject("scene_item_railgun_power_box");
	itemInfo = { "scene_item_power_box", Point(powerBoxPoint.at("x").asFloat(), powerBoxPoint.at("y").asFloat()), false, en_sceneItem_physics };
	sceneItem = RailgunSceneItem::create(itemInfo);
	sceneItem->setRailgunPart(en_railgunPart_powerBox);
	sceneItemLayer->setSceneitem(sceneItem);

	ValueMap batteryPoint = objGroup->getObject("scene_item_railgun_battery");
	itemInfo = { "scene_item_battery", Point(batteryPoint.at("x").asFloat(), batteryPoint.at("y").asFloat()), true, en_sceneItem_physics };
	sceneItem = RailgunSceneItem::create(itemInfo);
	sceneItem->setRailgunPart(en_railgunPart_battery);
	sceneItemLayer->setSceneitem(sceneItem);

	//根据读取到的怪物信息创建怪物对象
	//根据地图文件中预设的坐标信息放置怪物对象
	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		if (i % 2 == 0)
		{
			Monster* monster = Monster::create(monsterInfoList[9]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		else
		{
			Monster* monster = Monster::create(monsterInfoList[7]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}

	}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[3]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setGameScene_3_1(PlayerData & playerData)
{
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_3-1.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	this->addChild(SceneItemLayer::create());

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	//根据读取到的怪物信息创建怪物对象
	//根据地图文件中预设的坐标信息放置怪物对象
	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		if (i % 2 == 0)
		{
			Monster* monster = Monster::create(monsterInfoList[10]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		else
		{
			Monster* monster = Monster::create(monsterInfoList[8]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}

	}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[2]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setGameScene_3_2(PlayerData & playerData)
{
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_3-2.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	this->addChild(SceneItemLayer::create());

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	//根据读取到的怪物信息创建怪物对象
//根据地图文件中预设的坐标信息放置怪物对象
	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		if (i % 2 == 0)
		{
			Monster* monster = Monster::create(monsterInfoList[12]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		else
		{
			Monster* monster = Monster::create(monsterInfoList[13]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}

	}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[5]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setGameScene_4_1(PlayerData & playerData)
{
	//载入地图
	m_pMap = TMXTiledMap::create("map/map_4-1.tmx");
	if (m_pMap == nullptr)
	{
		log("map error");
		return;
	}
	this->addChild(m_pMap);

	this->addChild(SceneItemLayer::create());

	GameManager::getInstance()->setMap(m_pMap);

	//获取地图文件中预设的坐标信息
	TMXObjectGroup* objGroup = m_pMap->getObjectGroup("objects");

	//根据读取到的怪物信息创建怪物对象
	//根据地图文件中预设的坐标信息放置怪物对象
	int i = 1;
	while (true)
	{
		std::string monsterPointID = StringUtils::format("monster_%02d", i++);
		ValueMap monsterPoint = objGroup->getObject(monsterPointID.c_str());
		CC_BREAK_IF(monsterPoint.empty());

		float monsterX = monsterPoint.at("x").asFloat();
		float monsterY = monsterPoint.at("y").asFloat();

		if (i % 2 == 0)
		{
			Monster* monster = Monster::create(monsterInfoList[14]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}
		else
		{
			Monster* monster = Monster::create(monsterInfoList[2]);
			monster->setMonsterOriginPosition(Point(monsterX, monsterY));
			monster->idle();
			monster->setScale(0.35);
			this->addChild(monster);
		}

	}

	//创建Boss对象并设置
	ValueMap bossPoint = objGroup->getObject("boss");

	float bossX = bossPoint.at("x").asFloat();
	float bossY = bossPoint.at("y").asFloat();

	BossTianzhao* boss = BossTianzhao::create(bossDataList[6]);
	boss->setBossPosition(Vec2(bossX, bossY));
	boss->idle();
	boss->setScale(0.45);
	this->addChild(boss);

	//创建玩家角色对象并设置
	ValueMap playerPoint = objGroup->getObject("player");

	float playerX = playerPoint.at("x").asFloat();
	float playerY = playerPoint.at("y").asFloat();

	Point playerPos = Point(playerX, playerY);

	m_sctPlayerData = playerData;

	this->setPlayer(playerPos);
}

void GameLayer::setPlayer(const Point & pos)
{
	m_pPlayer = Player::create(m_sctPlayerData);
	m_pPlayer->setPosition(pos);
	m_pPlayer->idle();
	this->addChild(m_pPlayer);

	//创建玩家控制器并添加
	PlayerController* playerController = PlayerController::create();
	m_pPlayerController = playerController;
	m_pPlayer->setController(m_pPlayerController);
	this->addChild(m_pPlayerController);

	m_pPlayerController->setMap(m_pMap);

	//创建玩家发出的攻击对象，先保存，待玩家攻击时再设置
	AtkFlyObjIniInfo fireballInfo = { "fireball", Vec2(m_sctPlayerData.i_attackRange, 0), Vec2(m_sctPlayerData.i_xSpeed + 1, 0), m_sctPlayerData.i_attack };
	for (int i = 0; i < 3; i++)
	{
		AttackFlyingObject* flyingObject = AttackFlyingObject::create(fireballInfo);
		CC_BREAK_IF(flyingObject == nullptr);
		vector_pAttackFlyingObject.pushBack(flyingObject);
		this->addChild(flyingObject);
	}
}

void GameLayer::updateScore(Ref * pSender)
{
	m_sctPlayerData.i_money += (int)pSender;
}

void GameLayer::enterMainScene(Ref * pSender)
{
	MainScene* mainScene = MainScene::create();
	Director::getInstance()->replaceScene(mainScene);
}
