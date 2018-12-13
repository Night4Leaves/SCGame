#pragma once
#ifndef __GAME_MENU_LAYER_H__
#define __GAME_MENU_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class GameMenuLayer : public Layer
{
public:
	GameMenuLayer();
	virtual ~GameMenuLayer();

	CREATE_FUNC(GameMenuLayer);
	virtual bool init();

	//���ó�ʼ����Ĳ˵�ѡ��
	void setInitialMenu();

	//����������Ĳ˵�ѡ��
	void setMainMenu();

private:
	//��ʼ���湦��
	void startGame(CCObject *sender);
	void continueGame(CCObject *sender);
	void openOptionWin(CCObject *sender);
	void exitGame(CCObject *sender);

	//�����湦��
	void selectGameScene(CCObject *sender);
};

#endif // !1