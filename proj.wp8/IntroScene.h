#ifndef __INTROSCENE_SCENE_H__
#define __INTROSCENE_SCENE_H__

#include "PhysicWorld.h"

USING_NS_CC;


class IntroScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();

	virtual bool init();

	void introSkipCall(CCObject* pSender);

	CREATE_FUNC(IntroScene);
};

#endif