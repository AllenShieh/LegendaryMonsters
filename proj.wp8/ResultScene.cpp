#include<MenuScene.h>
#include<GameScene.h>
#include<ResultScene.h>

cocos2d::CCScene* ResultScene::scene()
{
	auto scene = CCScene::create();   //创建一个场景
	auto layer = ResultScene::create();   //创建一个图层
	scene->addChild(layer);
	return scene;
}

//初始化当前的图层
bool ResultScene::init()
{
	if (!CCLayer::init())      //初始化父类
		return false;

	//获取屏幕大小
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();

	auto * MenuBackground = CCSprite::create("bg3.jpg");
	MenuBackground->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(MenuBackground);

	//创建菜单
	CCMenuItemImage * item4 = CCMenuItemImage::create("2.png", "2.png", this, menu_selector(ResultScene::menuCallretry));
	item4->setPosition(ccp(visibleSize.width*0.9, visibleSize.width*0.5));
	auto menu = CCMenu::create(item4, NULL);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	CCMenuItemImage * item5 = CCMenuItemImage::create("3.png", "3.png", this, menu_selector(ResultScene::menuCallback));
	item5->setPosition(ccp(visibleSize.width*0.2, visibleSize.width*0.5));
	auto menu2 = CCMenu::create(item5, NULL);
	menu2->setAnchorPoint(CCPointZero);
	menu2->setPosition(CCPointZero);
	this->addChild(menu2);

	//---show the result!!!
	result = CCLabelTTF::create("0", "arial", 32);
	result->setColor(ccc3(126, 126, 126));
	result->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(result);
	//---plz work!

	return true;
}

void ResultScene::menuCallretry(CCObject* pSender)
{
	auto *gScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, gScene));
}

void ResultScene::menuCallback(CCObject* pSender)
{
	auto *mScene = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, mScene));
}