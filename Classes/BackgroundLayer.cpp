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
	//根据图片名创建精灵对象并添加到层中
	Sprite* p_bgSprite = Sprite::create(pictureName);
	if (p_bgSprite == nullptr)
	{
		log("setBackgroundPicture set failed!");
		return false;
	}
	this->addChild(p_bgSprite);

	//获取精灵对象内容大小，即图片大小
	Size size = p_bgSprite->getContentSize();
	//获取OpenGL视图规格
	Size p_winSize = Director::getInstance()->getWinSize();

	//根据图片大小与视图规格比例，对背景图片进行缩放，确保背景没有黑条
	p_bgSprite->setScale(MAX(p_winSize.width / size.width, p_winSize.height / size.height));

	//设置图片中心点在窗口视图中心
	p_bgSprite->setPosition(p_winSize.width * 0.5, p_winSize.height * 0.5);

	return true;
}
