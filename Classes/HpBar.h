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

	//设置血条显示的位置
	void setHpBarPosition(Point pos);
	//设置血条显示
	void setResidueHp(float residue);
	//血条消失
	void startFadeOut();

private:
	HpBar();
	virtual ~HpBar();

private:
	Sprite* m_pEmptyHpBar;	//空血条
	LoadingBar* m_pHpBar;	//血条
};


#endif // !__HP_BAR_H__
