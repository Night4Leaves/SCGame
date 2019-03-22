#include "Boss.h"

Boss::Boss()
	: m_iXSpeed(0)
	, m_iYSpeed(0)
	, m_iFirstSkillDamage(0)
	, m_iFirstSkillCDTime(0)
	, m_iFirstSkillTime(0)
	, m_iSecondSkillDamage(0)
	, m_iSecondSkillCDTime(0)
	, m_iSecondSkillTime(0)
	, m_iThirdSkillDamage(0)
	, m_iThirdSkillCDTime(0)
	, m_iThirdSkillTime(0)
	, m_bIsLock(false)
	, m_fStateTime(0.0)
{
}

Boss::~Boss()
{
}

bool Boss::init(const BossData & bossData)
{
	CombatEntity::saveCombatEntityData(bossData);

	m_iFirstSkillDamage = bossData.i_firstSkillDamage;
	m_iFirstSkillCDTime = bossData.i_firstSkillCDTime;
	m_iSecondSkillDamage = bossData.i_secondSkillDamage;
	m_iSecondSkillCDTime = bossData.i_secondSkillCDTime;
	m_iThirdSkillDamage = bossData.i_thirdSkillDamage;
	m_iThirdSkillCDTime = bossData.i_thirdSkillCDTime;

	return true;
}

void Boss::setBossPosition(Point pos)
{
	Size mapSize = GameManager::getInstance()->getMapSize();
	Size spriteSize = m_pSprite->getContentSize();
	Size visible = Director::getInstance()->getVisibleSize();

	pos.x = std::max(pos.x, mapSize.width - visible.width + spriteSize.width / 2);
	pos.x = std::min(pos.x, mapSize.width - spriteSize.width / 2);
	//防止跑到下边界外
	pos.y = std::max(0.0f, pos.y);

	//获取坐标所在砖块在块地图中的坐标
	Point tiledPos = GameManager::getInstance()->tileCoordForPosition(pos);

	bool notGo = GameManager::getInstance()->checkBoolAttribute(tiledPos, "Collidable");

	if (notGo)
	{
		pos.y -= m_iYSpeed;
		m_iYSpeed = 0;
	}
	setPosition(pos);
}
