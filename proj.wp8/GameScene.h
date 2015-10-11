#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "PhysicWorld.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer, public b2ContactListener
{
private:
	B2Sprite * ship_2;
	float frameRotate;
	B2Sprite *b1;
	B2Sprite *b2;
	B2Sprite *b3;
	B2Sprite *b4;
	B2Sprite *g1;
	B2Sprite *g2;
	B2Sprite *g3;
	B2Sprite *g4;

	b2World *mWorld;

	CCLabelTTF * label;
	int score;

	float getR;
	float diffR;
	float newR;

	void update(float dt);
	void BeginContact(b2Contact* contact);
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(GameScene);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	void setR(){ getR = 0; }
};

#endif