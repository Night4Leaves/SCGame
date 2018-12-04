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
	//根据传入的内容、字体种类、字号创建标题标签
	Label* p_titleLabel = Label::create(title, fontType, fontSize);
	if (p_titleLabel == nullptr)
	{
		log("Title create failed!");
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
	return false;
}
