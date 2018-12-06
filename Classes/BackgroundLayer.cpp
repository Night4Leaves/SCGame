#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer()
{
}

BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		return true;
	} while (0);

	log("BackgroundLayer initialize failed!");

	return false;
}

void BackgroundLayer::setBackgroundPicture(const char * pictureName)
{
	//����ͼƬ���������������ӵ�����
	Sprite* p_bgSprite = Sprite::create(pictureName);
	if (p_bgSprite == nullptr)
	{
		log("setBackgroundPicture set failed!");
		return;
	}
	else
	{
		this->addChild(p_bgSprite);

		//��ȡ����������ݴ�С����ͼƬ��С
		Size size = p_bgSprite->getContentSize();
		//��ȡOpenGL��ͼ���
		Size winSize = Director::getInstance()->getWinSize();

		//����ͼƬ��С����ͼ���������Ա���ͼƬ�������ţ�ȷ������û�к���
		p_bgSprite->setScale(MAX(winSize.width / size.width, winSize.height / size.height));

		//����ͼƬ���ĵ��ڴ�����ͼ����
		p_bgSprite->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	}

}

void BackgroundLayer::setGameTitle(const char * title, const char * fontType, float fontSize, Color3B color)
{
	//���ݴ�������ݡ��������ࡢ�ֺŴ��������ǩ
	Label* p_titleLabel = Label::create(title, fontType, fontSize);
	if (p_titleLabel == nullptr)
	{
		log("Title create failed!");
		return;
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

}
