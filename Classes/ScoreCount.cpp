#include "ScoreCount.h"

ScoreCount::ScoreCount()
{
}

ScoreCount::~ScoreCount()
{
}

ScoreCount * ScoreCount::create(Array * presenters, int digit)
{
	ScoreCount* scoreCount = new ScoreCount();
	if (scoreCount && scoreCount->init(presenters, digit))
	{
		scoreCount->autorelease();
		return scoreCount;
	}
	else
	{
		CC_SAFE_DELETE(scoreCount);
		return nullptr;
	}
	
}

bool ScoreCount::init(Array * presenters, int digit)
{
	do
	{
		CC_BREAK_IF(!Node::init());

		node_pPresenter = Node::create();
		Object* object = NULL;
		int i = 0;

		CCARRAY_FOREACH(presenters, object)
		{
			Node* node = (Node*)object;
			node_pPresenter->addChild(node, 0, i);
			node->setPosition(Point(0, node->getContentSize().height * i * 0.15));
			++i;
		}
		
		ClippingNode* cliper = ClippingNode::create();
		DrawNode* drawNode = DrawNode::create();

		drawNode->drawSolidRect(Vec2(0, 0), Vec2(15, 20), Color4F::WHITE);
		drawNode->setPosition(-8, -10);
		
		cliper->setStencil(drawNode);
		cliper->addChild(node_pPresenter);

		this->addChild(cliper);
		this->setDigit(digit);

		return true;
	} while (0);
	return false;
}

void ScoreCount::animation(int digit)
{
	Node* node = (Node*)node_pPresenter->getChildByTag(i_digit);
	Point position = node->getPosition();
	node_pPresenter->stopActionByTag(0);
	MoveTo* moveTo = MoveTo::create(0.1f, Point(0, -position.y));
	moveTo->setTag(0);
	node_pPresenter->runAction(moveTo);
}

int ScoreCount::getDigit()
{
	return i_digit;
}

void ScoreCount::setDigit(int digit)
{
	if (i_digit != digit)
	{
		i_digit = digit;
		this->animation(digit);
	}
}
