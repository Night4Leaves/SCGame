#include "HeartCount.h"

HeartCount::HeartCount()
{
}

HeartCount::~HeartCount()
{
}

HeartCount * HeartCount::create(int digit)
{
	HeartCount* heartCount = new HeartCount();
	if (heartCount && heartCount->init(digit))
	{
		heartCount->autorelease();
		return heartCount;
	}
	else
	{
		CC_SAFE_DELETE(heartCount);
		return nullptr;
	}
	
}

bool HeartCount::init(int digit)
{
	do
	{
		CC_BREAK_IF(!Node::init());

		node_pPresenter = Node::create();

		for (int i = 0; i < digit; ++i)
		{
			Sprite* redHeart = Sprite::createWithSpriteFrameName("Red_Heart.png");
			Sprite* emptyHeart = Sprite::createWithSpriteFrameName("Empty_Heart.png");
			redHeart->setScale(0.15);
			emptyHeart->setScale(0.15);
			redHeart->setPosition(Point(30 + 42 * i, 0));
			emptyHeart->setPosition(Point(30 + 42 * i, 0));
			node_pPresenter->addChild(emptyHeart);
			node_pPresenter->addChild(redHeart, 0, i);
		}

		m_iMaxHP = digit;
		m_iHP = digit;
		this->addChild(node_pPresenter);

		return true;
	} while (0);
	return false;
}

void HeartCount::reduceHP()
{
	if (m_iHP == 0)
	{
		return;
	}

	Node* node = (Node*)node_pPresenter->getChildByTag(m_iHP - 1);

	MoveBy* moveBy = MoveBy::create(1.5f, Vec2(0, 15));
	FadeOut* fadeOut = FadeOut::create(1.5f);
	Spawn* spawn = Spawn::create(moveBy, fadeOut, NULL);

	node->runAction(spawn);
	--m_iHP;
}

void HeartCount::recoverHP()
{
	m_iHP++;
	if (m_iHP > m_iMaxHP)
	{
		m_iHP = m_iMaxHP;
		return;
	}

	Node* node = (Node*)node_pPresenter->getChildByTag(m_iHP - 1);

	MoveBy* moveBy = MoveBy::create(1.5f, Vec2(0, -15));
	FadeIn* fadeIn = FadeIn::create(1.5f);
	Spawn* spawn = Spawn::create(moveBy, fadeIn, NULL);

	node->runAction(spawn);
}
