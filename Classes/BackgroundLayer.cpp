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

bool BackgroundLayer::createBackgroundPicture(const char * pictureName)
{
	//����ͼƬ���������������ӵ�����
	Sprite* p_bgSprite = Sprite::create(pictureName);
	if (p_bgSprite == nullptr)
	{
		log("setBackgroundPicture set failed!");
		return false;
	}
	this->addChild(p_bgSprite);

	//��ȡ����������ݴ�С����ͼƬ��С
	Size size = p_bgSprite->getContentSize();
	//��ȡOpenGL��ͼ���
	Size p_winSize = Director::getInstance()->getWinSize();

	//����ͼƬ��С����ͼ���������Ա���ͼƬ�������ţ�ȷ������û�к���
	p_bgSprite->setScale(MAX(p_winSize.width / size.width, p_winSize.height / size.height));

	//����ͼƬ���ĵ��ڴ�����ͼ����
	p_bgSprite->setPosition(p_winSize.width * 0.5, p_winSize.height * 0.5);

	return true;
}
