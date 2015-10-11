#ifndef __MENUSCENE_SCENE_H__
#define __MENUSCENE_SCENE_H__

#include "PhysicWorld.h"

USING_NS_CC;


class MenuScene : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();

	virtual bool init();

	void menuCallback(CCObject* pSender);

	CREATE_FUNC(MenuScene);
};

#endif