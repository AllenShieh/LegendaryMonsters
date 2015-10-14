#ifndef __RESULTSCENE_SCENE_H__
#define __RESULTSCENE_SCENE_H__

#include "PhysicWorld.h"

USING_NS_CC;


class ResultScene : public cocos2d::CCLayer
{
private:
	CCLabelTTF * result;

public:
	static cocos2d::CCScene* scene();

	virtual bool init();

	void menuCallback(CCObject* pSender);

	void menuCallretry(CCObject* pSender);

	CREATE_FUNC(ResultScene);

	void setResult(bool win){
		if (win){
			result->setString("SUCCESS!");
		}
		else{
			result->setString("FAILURE!");
		}
	}
};

#endif