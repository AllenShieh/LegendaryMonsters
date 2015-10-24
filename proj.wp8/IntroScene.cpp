#include <IntroScene.h>
#include <MenuScene.h>

cocos2d::CCScene* IntroScene::scene()
{
	auto scene = CCScene::create();   //创建一个场景
	auto layer = IntroScene::create();   //创建一个图层
	scene->addChild(layer);
	return scene;
}
bool IntroScene::init(){
	if (!CCLayer::init()){    //初始化父类
		return false;
	}

	//获取屏幕大小
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();

	auto * IntroBackground = CCSprite::create("taopao.jpg");
	CCSize pictureSize = IntroBackground->getContentSize();
	IntroBackground->setScaleX(visibleSize.width/ pictureSize.width);
	IntroBackground->setScaleY(visibleSize.height / pictureSize.height);
	IntroBackground->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(IntroBackground);

	CCLabelTTF * skipLabel = CCLabelTTF::create("skip", "arial", 32);
	skipLabel->setColor(ccc3(0, 0, 0));
	CCMenuItemLabel * skip = CCMenuItemLabel::create(skipLabel, this, menu_selector(IntroScene::introSkipCall));
	skip->setPosition(ccp(visibleSize.width*0.9, visibleSize.height*0.2));
	auto menu = CCMenu::create(skip, NULL);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	return true;
}

void IntroScene::introSkipCall(CCObject* pSender){
	auto menu = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, menu));
}
