#include "ShopItemButton.h"
#include "PlayerInfo.h"

ShopItemButton * ShopItemButton::create(ShopItemInfo itemInfo)
{
	ShopItemButton *pRet = new(std::nothrow) ShopItemButton();
	if (pRet && pRet->init(itemInfo))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool ShopItemButton::init(ShopItemInfo itemInfo)
{
	do
	{
		CC_BREAK_IF(!Node::init());

		m_strName = itemInfo.str_name;
		m_iNum = itemInfo.i_num;
		m_iPrice = itemInfo.i_price;
		m_enShopItemType = itemInfo.en_shopItemType;

		return true;
	} while (0);
	return false;
}

void ShopItemButton::setStoreVol()
{
	std::string spriteFrameName = StringUtils::format("item_%s.png", m_strName.c_str());
	m_pItemSprite = Sprite::createWithSpriteFrameName(spriteFrameName.c_str());
	this->addChild(m_pItemSprite);

	Sprite* coin = Sprite::createWithSpriteFrameName("coin.png");
	coin->setScale(1.2);
	
	int temp = m_iPrice;

	Sprite* exampleSprite = Sprite::createWithSpriteFrameName("number_0.png");
	Size size = exampleSprite->getContentSize();

	for (int i = 3; i > 0; --i)
	{
		int num = temp % 10;
		std::string numberPictrueName = StringUtils::format("number_%d.png", num);
		Sprite* numSprite = Sprite::createWithSpriteFrameName(numberPictrueName.c_str());
		numSprite->setScale(0.1);
		numSprite->setPosition(size.width * 0.15 * i - 22, -5);
		coin->addChild(numSprite);
		temp /= 10;
	}

	MenuItemSprite* menuItem = MenuItemSprite::create(coin, coin, this, menu_selector(ShopItemButton::buyItem));
	m_pMenu = Menu::create(menuItem, nullptr);
	m_pMenu->setPosition(125, 15);
	this->addChild(m_pMenu);
}

void ShopItemButton::setBackpackVol()
{
	std::string spriteFrameName = StringUtils::format("item_%s.png", m_strName.c_str());
	m_pItemSprite = Sprite::createWithSpriteFrameName(spriteFrameName.c_str());
	this->addChild(m_pItemSprite);

	int temp = PlayerInfo::getInstance()->getItemNum(m_strName);

	Sprite* exampleSprite = Sprite::createWithSpriteFrameName("number_0.png");
	Size size = exampleSprite->getContentSize();

	for (int i = 3; i > 0; --i)
	{
		int num = temp % 10;
		std::string numberPictrueName = StringUtils::format("number_%d.png", num);
		Sprite* numSprite = Sprite::createWithSpriteFrameName(numberPictrueName.c_str());
		numSprite->setScale(0.1);
		numSprite->setPosition(size.width * 0.15 * i + 100, 0);
		this->addChild(numSprite);
		temp /= 10;
	}

	Sprite* menuSprite = Sprite::createWithSpriteFrameName(spriteFrameName.c_str());
	MenuItemSprite* menuItem = MenuItemSprite::create(menuSprite, menuSprite, this, menu_selector(ShopItemButton::equipItem));
	Menu* test = Menu::create(menuItem, nullptr);
	test->setPosition(0, 0);
	this->addChild(test);
}

ShopItemButton::ShopItemButton()
{
}

ShopItemButton::~ShopItemButton()
{
}

void ShopItemButton::buyItem(Ref * pSender)
{
	int playerMoney = PlayerInfo::getInstance()->getMoney();
	if (playerMoney >= m_iPrice)
	{
		playerMoney -= m_iPrice;
		PlayerInfo::getInstance()->setMoney(playerMoney);
		PlayerInfo::getInstance()->setItem(m_strName);
	}
	else
	{
		return;
	}
	
}

void ShopItemButton::equipItem(Ref * pSender)
{
	PlayerInfo::getInstance()->setShopItemType(m_enShopItemType);
}
