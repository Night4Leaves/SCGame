#include "InitialScene.h"
#include "BackgroundLayer.h"
#include "TextDisplayLayer.h"
#include "GameMenuLayer.h"

InitialScene::InitialScene()
{
}

InitialScene::~InitialScene()
{
}

Scene * InitialScene::createScene()
{
	return InitialScene::create();
}

bool InitialScene::init()
{
	do {
		CC_BREAK_IF(!Scene::init());

		//��ʼ�������㲢��ӵ�������
		m_pBackgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(m_pBackgroundLayer == nullptr);
		this->addChild(m_pBackgroundLayer);
		//��ӱ���ͼƬ
		m_pBackgroundLayer->setBackgroundPicture("fantasy_001_2048x1536.png");

		//��ʼ��������ʾ�㲢��ӵ�������
		m_pTextDisplayLayer = TextDisplayLayer::create();
		CC_BREAK_IF(m_pTextDisplayLayer == nullptr);
		this->addChild(m_pTextDisplayLayer);
		//��ӱ���
		m_pTextDisplayLayer->setGameTitle("SCGame", "fonts/Marker Felt.ttf", 30, Color3B::ORANGE);

		//��ʼ���˵��㲢��ӵ�������
		m_pGameMenuLayer = GameMenuLayer::create();
		CC_BREAK_IF(m_pGameMenuLayer == nullptr);
		this->addChild(m_pGameMenuLayer);

		return true;
	} while (0);

	log("InitialScene initialize failed!");

	return false;
}
