#include "TextDisplayLayer.h"

TextDisplayLayer::TextDisplayLayer()
{
}

TextDisplayLayer::~TextDisplayLayer()
{
}

bool TextDisplayLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		return true;
	} while (0);

	log("TextDisplayLayer initialize failed!");

	return false;
}

bool TextDisplayLayer::setGameTitle(const char * title, const char * fontType, float fontSize, Color3B color)
{
	//���ݴ�������ݡ��������ࡢ�ֺŴ��������ǩ
	Label* p_titleLabel = Label::create(title, fontType, fontSize);
	if (p_titleLabel == nullptr)
	{
		log("Title create failed!");
	}
	else
	{
		this->addChild(p_titleLabel);

		//���ñ���������ɫ
		p_titleLabel->setColor(color);

		//��ȡOpenGL��ͼ���
		Size winSize = Director::getInstance()->getWinSize();

		//���ñ������ĵ��ڴ�����ͼ����λ��
		p_titleLabel->setPosition(winSize.width * 0.5, winSize.height * 0.8);

	}
	return false;
}
