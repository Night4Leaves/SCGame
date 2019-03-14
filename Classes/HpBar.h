#pragma once
#ifndef __HP_BAR_H__
#define __HP_BAR_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class HpBar : public Node
{
public:
	CREATE_FUNC(HpBar);
	virtual bool init();

	void setHpBarPosition(Point pos);
	void setResidueHp(float residue);
	void startFadeOut();

private:
	HpBar();
	virtual ~HpBar();
	Sprite* m_pEmptyHpBar;
	LoadingBar* m_pHpBar;
};


#endif // !__HP_BAR_H__
