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
	char * pics[6] = { "storylead1.jpg", "storylead2.jpg", "storylead3.jpg", "storylead4.jpg", "storylead5.jpg", "storylead6.jpg" };
	for (int i = 0; i < 6; ++i){
		IntroScene::picSrc[i] = pics[i];
	}
	IntroScene::currPic = 0;
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	//获取屏幕大小
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();

	IntroScene::IntroBackground1 = CCSprite::create(picSrc[0]);
	CCSize pictureSize1 = IntroScene::IntroBackground1->getContentSize();
	IntroScene::IntroBackground1->setScaleX(visibleSize.width / pictureSize1.width);
	IntroScene::IntroBackground1->setScaleY(visibleSize.height / pictureSize1.height);
	IntroScene::IntroBackground1->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(IntroScene::IntroBackground1);

	IntroScene::IntroBackground2 = CCSprite::create(picSrc[1]);
	CCSize pictureSize2 = IntroScene::IntroBackground2->getContentSize();
	IntroScene::IntroBackground2->setScaleX(visibleSize.width / pictureSize2.width);
	IntroScene::IntroBackground2->setScaleY(visibleSize.height / pictureSize2.height);
	IntroScene::IntroBackground2->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(IntroScene::IntroBackground2);
	IntroScene::IntroBackground2->setVisible(false);

	CCLabelTTF * skipLabel = CCLabelTTF::create("skip", "arial", 32);
	skipLabel->setColor(ccc3(0, 0, 0));
	CCMenuItemLabel * skip = CCMenuItemLabel::create(skipLabel, this, menu_selector(IntroScene::introSkipCall));
	skip->setPosition(ccp(visibleSize.width*0.9, visibleSize.height*0.2));
	auto menu = CCMenu::create(skip, NULL);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	setTouchEnabled(true);
	return true;
}

bool IntroScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	IntroScene::IntroBackground2->setVisible(true);
	if (IntroScene::currPic == 5){
		auto menu = MenuScene::scene();
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, menu));
		IntroScene::currPic == 0;
	}
	else{
		CCFadeOut * fadeout = CCFadeOut::create(1);
		CCFadeIn * fadein = CCFadeIn::create(1);
		IntroScene::currPic++;
		CCTexture2D *newPic = CCTextureCache::sharedTextureCache()->addImage(IntroScene::picSrc[IntroScene::currPic]);
		if (IntroScene::currPic % 2 == 0){
			IntroScene::IntroBackground2->runAction(fadeout);
			IntroScene::IntroBackground1->setTexture(newPic);
			IntroScene::IntroBackground1->runAction(fadein);
		}
		else{
			IntroScene::IntroBackground1->runAction(fadeout);
			IntroScene::IntroBackground2->setTexture(newPic);
			IntroScene::IntroBackground2->runAction(fadein);
		}
	}
	return true;
}

void IntroScene::introSkipCall(CCObject* pSender){
	auto menu = MenuScene::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, menu));
}
