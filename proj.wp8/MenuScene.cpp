#include<MenuScene.h>
#include<GameScene.h>

cocos2d::CCScene* MenuScene::scene()
{
	auto scene = CCScene::create();   //创建一个场景
	auto layer = MenuScene::create();   //创建一个图层
	scene->addChild(layer);
	return scene;
}

//初始化当前的图层
bool MenuScene::init()
{
	if (!CCLayer::init())      //初始化父类
		return false;

	//获取屏幕大小
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();

	auto * MenuBackground = CCSprite::create("bg1.jpg");
	MenuBackground->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(MenuBackground);

	//创建菜单
	CCMenuItemImage * item4 = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MenuScene::menuCallback));
	item4->setPosition(ccp(visibleSize.width*0.9, visibleSize.width*0.5));
	auto menu = CCMenu::create(item4, NULL);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	this->addChild(menu);


	return true;
}

void MenuScene::menuCallback(CCObject* pSender)
{
	auto *gScene = GameScene::scene();
	/*CCScene *gScene = CCScene::create();
	GameScene *layer = GameScene::create();
	layer->setR();
	gScene->addChild(layer);*/
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f,gScene));
}