#include "ScoreCountLayer.h"
#include "ScoreCount.h"

ScoreCountLayer::ScoreCountLayer()
{
}

ScoreCountLayer::~ScoreCountLayer()
{
}

ScoreCountLayer * ScoreCountLayer::create(int number)
{
	ScoreCountLayer* scoreCountLayer = new ScoreCountLayer();
	if (scoreCountLayer && scoreCountLayer->init(number))
	{
		scoreCountLayer->autorelease();
		return scoreCountLayer;
	}
	else
	{
		CC_SAFE_DELETE(scoreCountLayer);
		return nullptr;
	}
	
}

bool ScoreCountLayer::init(int number)
{
	do
	{
		CC_BREAK_IF(!Node::init());

		for (int i = 0; i < 6; ++i)
		{
			Array *array = Array::createWithCapacity(10);
			float f_width = 0.0;

			log("%d", i);

			for (int ii = 0; ii < 10; ++ii)
			{
				std::string numberPictrueName = StringUtils::format("number_%d.png", ii);
				log("%s", numberPictrueName.c_str());

				Sprite *numSprite = Sprite::createWithSpriteFrameName(numberPictrueName.c_str());
				f_width = numSprite->getContentSize().width;

				array->addObject(numSprite);

				numSprite->setScale(0.1);
			}

			ScoreCount* scoreCount = ScoreCount::create(array);
			this->addChild(scoreCount, 0, i);
			scoreCount->setPosition(f_width * i * 0.15 + 700, 550);
		}
		
		this->setNumber(number);

	} while (0);
	return true;
}

void ScoreCountLayer::setNumber(int number, int ceiling)
{
	if (number > ceiling)
	{
		number = ceiling;
	}
	if (number < 0)
	{
		number = 0;
	}
	i_number = number;

	for (int i = 5; i >= 0; --i)
	{
		ScoreCount* scoreCount = (ScoreCount*)getChildByTag(i);
		scoreCount->setDigit(number % 10);
		number /= 10;
	}
}

