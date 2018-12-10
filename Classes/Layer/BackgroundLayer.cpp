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
	//根据图片名创建精灵对象并添加到层中
	Sprite* p_bgSprite = Sprite::create(pictureName);
	if (p_bgSprite == nullptr)
	{
		log("setBackgroundPicture set failed!");
		return;
	}
	else
	{
		this->addChild(p_bgSprite);

		//获取精灵对象内容大小，即图片大小
		Size size = p_bgSprite->getContentSize();
		//获取OpenGL视图规格
		Size winSize = Director::getInstance()->getWinSize();

		//根据图片大小与视图规格比例，对背景图片进行缩放，确保背景没有黑条
		p_bgSprite->setScale(MAX(winSize.width / size.width, winSize.height / size.height));

		//设置图片中心点在窗口视图中心
		p_bgSprite->setPosition(winSize.width * 0.5, winSize.height * 0.5);
	}

}

void BackgroundLayer::setGameTitle(const char * title, const char * fontType, float fontSize, Color3B color)
{
	//根据传入的内容、字体种类、字号创建标题标签
	Label* p_titleLabel = Label::create(title, fontType, fontSize);
	if (p_titleLabel == nullptr)
	{
		log("Title create failed!");
		return;
	}
	else
	{
		this->addChild(p_titleLabel);

		//设置标题字体颜色
		p_titleLabel->setColor(color);

		//获取OpenGL视图规格
		Size winSize = Director::getInstance()->getWinSize();

		//设置标题中心点在窗口视图合适位置
		p_titleLabel->setPosition(winSize.width * 0.5, winSize.height * 0.8);
	}

}
