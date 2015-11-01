#ifndef __INTROSCENE_SCENE_H__
#define __INTROSCENE_SCENE_H__

#include "PhysicWorld.h"

USING_NS_CC;


class IntroScene : public cocos2d::CCLayer
{
private:
	CCSprite * IntroBackground1;
	CCSprite * IntroBackground2;
	char * picSrc[6];
	int currPic;
public:
	static cocos2d::CCScene* scene();

	virtual bool init();

	void introSkipCall(CCObject* pSender);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	CREATE_FUNC(IntroScene);
};

#endif