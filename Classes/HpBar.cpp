#include "HpBar.h"

bool HpBar::init()
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_pEmptyHpBar = Sprite::createWithSpriteFrameName("HP_Bar_Empty.png");
		m_pHpBar = LoadingBar::create("HP_Bar.png");
		m_pEmptyHpBar->addChild(m_pHpBar);
		this->addChild(m_pEmptyHpBar);

		m_pHpBar->setDirection(LoadingBar::Direction::LEFT);
		m_pHpBar->setPosition(Vec2(459, 44));

		m_pEmptyHpBar->setScale(0.2);

		return true;
	} while (0);

	return false;
}

void HpBar::setHpBarPosition(Point pos)
{
	setPosition(pos);
}

void HpBar::setResidueHp(float residue)
{
	m_pHpBar->setPercent(residue);
}

void HpBar::startFadeOut()
{
	Blink* blinkAction = Blink::create(1.0f, 2);
	FadeOut* fadeOut = FadeOut::create(1.0f);
	Sequence* actionSequnence = Sequence::create(blinkAction, fadeOut, nullptr);
	m_pEmptyHpBar->runAction(actionSequnence);
}

HpBar::HpBar()
{
}

HpBar::~HpBar()
{
}
