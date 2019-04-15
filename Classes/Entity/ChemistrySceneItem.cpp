#include "ChemistrySceneItem.h"

bool ChemistrySceneItem::init()
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_pSprite = Sprite::createWithSpriteFrameName("scene_item_chemistry.png");
		this->addChild(m_pSprite);

		return true;
	} while (0);
	return false;
}

void ChemistrySceneItem::startPause(Ref * pSender)
{
}

void ChemistrySceneItem::endPause(Ref * pSender)
{
}

void ChemistrySceneItem::setType(ChemistryType chemistryType)
{
	m_enChemistryType = chemistryType;
	Sprite* sprite;
	switch (chemistryType)
	{
	case en_ct_HCl:
		sprite = Sprite::createWithSpriteFrameName("hcl.png");
		break;
	case en_ct_NaOH:
		sprite = Sprite::createWithSpriteFrameName("naoh.png");
		break;
	case en_ct_H2SO4:
		sprite = Sprite::createWithSpriteFrameName("h2so4.png");
		break;
	case en_ct_CAOH2:
		sprite = Sprite::createWithSpriteFrameName("caoh2.png");
		break;
	case en_ct_H2CO3:
		sprite = Sprite::createWithSpriteFrameName("h2co3.png");
		break;
	default:
		break;
	}

	this->addChild(sprite);
	sprite->setScale(0.5);
}

ChemistrySceneItem::ChemistrySceneItem()
{
}

ChemistrySceneItem::~ChemistrySceneItem()
{
}

