#include "GameScene.h"
#include "MenuScene.h"
#include <math.h>
#define RATIO 48.0f

USING_NS_CC;

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void GameScene::update(float dt){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	//why getR becomes a nonsense value when doing the real test?
	if (abs(getR) > 1000) getR = 0;

	diffR = frameRotate * dt;
	newR = getR + diffR;

	//---uodate the physical world---
	mWorld->Step(dt, 8, 3);

	b1->setPosition(ccp(winSize.width*0.5 + 245 * sin(-newR* 3.14 / 180.0f), winSize.height*0.5 - 245 * cos(-newR*3.14 / 180.0f)));
	b1->setRotation(90 - newR);
	b2->setPosition(ccp(winSize.width*0.5 + 245 * cos(-newR* 3.14 / 180.0f), winSize.height*0.5 + 245 * sin(-newR*3.14 / 180.0f)));
	b2->setRotation(-newR);
	b3->setPosition(ccp(winSize.width*0.5 - 245 * sin(-newR* 3.14 / 180.0f), winSize.height*0.5 + 245 * cos(-newR*3.14 / 180.0f)));
	b3->setRotation(90 - newR);
	b4->setPosition(ccp(winSize.width*0.5 - 245 * cos(-newR* 3.14 / 180.0f), winSize.height*0.5 - 245 * sin(-newR*3.14 / 180.0f)));
	b4->setRotation(-newR);

	g1->setPosition(ccp(winSize.width*0.5 + 245 * sin(-newR* 3.14 / 180.0f), winSize.height*0.5 - 245 * cos(-newR*3.14 / 180.0f)));
	g1->setRotation(90 - newR);
	g2->setPosition(ccp(winSize.width*0.5 + 245 * cos(-newR* 3.14 / 180.0f), winSize.height*0.5 + 245 * sin(-newR*3.14 / 180.0f)));
	g2->setRotation(-newR);
	g3->setPosition(ccp(winSize.width*0.5 - 245 * sin(-newR* 3.14 / 180.0f), winSize.height*0.5 + 245 * cos(-newR*3.14 / 180.0f)));
	g3->setRotation(90 - newR);
	g4->setPosition(ccp(winSize.width*0.5 - 245 * cos(-newR* 3.14 / 180.0f), winSize.height*0.5 - 245 * sin(-newR*3.14 / 180.0f)));
	g4->setRotation(-newR);

	getR = newR;

	char temp[20] = {};
	sprintf(temp, "%d, %f", score, newR);
	label->setString(temp);
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	auto * GameBackground = CCSprite::create("bg2.jpg");
	GameBackground->setPosition(ccp(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(GameBackground);

	//´´½¨²Ëµ¥
	CCMenuItemImage * item4 = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(GameScene::menuCloseCallback));
	item4->setPosition(ccp(visibleSize.width*0.1, visibleSize.width*0.5));
	auto menu = CCMenu::create(item4, NULL);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	getR = 0;
	diffR = 0;
	newR = 0;
	score = 0;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	mWorld = new b2World(b2Vec2(0, 0));
	mWorld->SetContactListener(this);


	//---add test object---
	ship_2 = B2Sprite::create("CloseSelected.png");
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(winSize.width / 2.5f / RATIO, winSize.height / 3.0f / RATIO);
	b2Body *shipBody = mWorld->CreateBody(&bodyDef);
	CCSize shipSize = ship_2->getContentSize();
	b2PolygonShape shipShape;
	shipShape.SetAsBox(shipSize.width / 2.0f / RATIO, shipSize.height / 2.0f / RATIO);
	b2FixtureDef shipFixtureDef;
	shipFixtureDef.shape = &shipShape;
	shipFixtureDef.density = 0.1f;
	shipFixtureDef.restitution = 1.0f;
	shipFixtureDef.friction = 0.0f;
	shipBody->CreateFixture(&shipFixtureDef);
	ship_2->setPTMRatio(RATIO);
	ship_2->setB2Body(shipBody);
	shipBody->SetLinearVelocity(b2Vec2(5.0f, 5.0f));
	this->addChild(ship_2);
	//---see if it is working---

	//---add edges~
	b1 = B2Sprite::create("bian2.png");
	b2BodyDef b1Frame;
	b1Frame.type = b2_staticBody;
	//b1Frame.position = b2Vec2(winSize.width / 2.0f / RATIO, (winSize.height / 2.0f - 245) / RATIO);
	//b1Frame.angle = 3.14 / 2.0f;
	b1Frame.position = b2Vec2(winSize.width*0.5 + 245 * sin(-getR* 3.14 / 180.0f), winSize.height*0.5 - 245 * cos(-getR*3.14 / 180.0f));
	b1Frame.angle = 90 - getR;
	b2Body *b1Body = mWorld->CreateBody(&b1Frame);
	CCSize b1Size = b1->getContentSize();
	b2PolygonShape b1Shape;
	b1Shape.SetAsBox(b1Size.width / 2.0f / RATIO, b1Size.height / 2.0f / RATIO);
	b2FixtureDef b1FixtureDef;
	b1FixtureDef.shape = &b1Shape;
	b1Body->CreateFixture(&b1FixtureDef);
	b1->setPTMRatio(RATIO);
	b1->setB2Body(b1Body);
	this->addChild(b1);

	b2 = B2Sprite::create("bian2.png");
	b2BodyDef b2Frame;
	b2Frame.type = b2_staticBody;
	//b2Frame.position = b2Vec2((winSize.width / 2.0f + 245) / RATIO, winSize.height / 2.0f / RATIO);
	//b2Frame.angle = 0;
	b2Frame.position = b2Vec2(winSize.width*0.5 + 245 * cos(-getR* 3.14 / 180.0f), winSize.height*0.5 + 245 * sin(-getR*3.14 / 180.0f));
	b2Frame.angle = -getR;
	b2Body *b22Body = mWorld->CreateBody(&b2Frame);
	CCSize b2Size = b2->getContentSize();
	b2PolygonShape b2Shape;
	b2Shape.SetAsBox(b2Size.width / 2.0f / RATIO, b2Size.height / 2.0f / RATIO);
	b2FixtureDef b22FixtureDef;
	b22FixtureDef.shape = &b2Shape;
	b22Body->CreateFixture(&b22FixtureDef);
	b2->setPTMRatio(RATIO);
	b2->setB2Body(b22Body);
	this->addChild(b2);

	b3 = B2Sprite::create("bian2.png");
	b2BodyDef b3Frame;
	b3Frame.type = b2_staticBody;
	//b3Frame.position = b2Vec2(winSize.width / 2.0f / RATIO, (winSize.height / 2.0f + 245) / RATIO);
	//b3Frame.angle = -3.14 / 2.0f;
	b3Frame.position = b2Vec2(winSize.width*0.5 - 245 * sin(-getR* 3.14 / 180.0f), winSize.height*0.5 + 245 * cos(-getR*3.14 / 180.0f));
	b3Frame.angle = 90 - getR;
	b2Body *b3Body = mWorld->CreateBody(&b3Frame);
	CCSize b3Size = b3->getContentSize();
	b2PolygonShape b3Shape;
	b3Shape.SetAsBox(b3Size.width / 2.0f / RATIO, b3Size.height / 2.0f / RATIO);
	b2FixtureDef b3FixtureDef;
	b3FixtureDef.shape = &b3Shape;
	b3Body->CreateFixture(&b3FixtureDef);
	b3->setPTMRatio(RATIO);
	b3->setB2Body(b3Body);
	this->addChild(b3);

	b4 = B2Sprite::create("bian2.png");
	b2BodyDef b4Frame;
	b4Frame.type = b2_staticBody;
	//b4Frame.position = b2Vec2((winSize.width / 2.0f - 245) / RATIO, winSize.height / 2.0f / RATIO);
	//b4Frame.angle = 3.14;
	b4Frame.position = b2Vec2(winSize.width*0.5 - 245 * cos(-getR* 3.14 / 180.0f), winSize.height*0.5 - 245 * sin(-getR*3.14 / 180.0f));
	b4Frame.angle = -getR;
	b2Body *b4Body = mWorld->CreateBody(&b4Frame);
	CCSize b4Size = b4->getContentSize();
	b2PolygonShape b4Shape;
	b4Shape.SetAsBox(b4Size.width / 2.0f / RATIO, b4Size.height / 2.0f / RATIO);
	b2FixtureDef b4FixtureDef;
	b4FixtureDef.shape = &b4Shape;
	b4Body->CreateFixture(&b4FixtureDef);
	b4->setPTMRatio(RATIO);
	b4->setB2Body(b4Body);
	this->addChild(b4);
	//---let's see what happens

	//---add gates---
	g1 = B2Sprite::create("hole.png");
	b2BodyDef g1Frame;
	g1Frame.type = b2_staticBody;
	//g1Frame.position = b2Vec2(winSize.width / 2.0f / RATIO, (winSize.height / 2.0f - 245) / RATIO);
	//g1Frame.angle = 3.14 / 2.0f;
	g1Frame.position = b2Vec2(winSize.width*0.5 + 245 * sin(-getR* 3.14 / 180.0f), winSize.height*0.5 - 245 * cos(-getR*3.14 / 180.0f));
	g1Frame.angle = 90 - getR;
	b2Body *g1Body = mWorld->CreateBody(&g1Frame);
	CCSize g1Size = g1->getContentSize();
	b2PolygonShape g1Shape;
	g1Shape.SetAsBox(g1Size.width / 2.0f / RATIO, g1Size.height / 2.0f / RATIO);
	b2FixtureDef g1FixtureDef;
	g1FixtureDef.shape = &g1Shape;
	g1Body->CreateFixture(&g1FixtureDef);
	g1->setPTMRatio(RATIO);
	g1->setB2Body(g1Body);
	this->addChild(g1);

	g2 = B2Sprite::create("hole.png");
	b2BodyDef g2Frame;
	g2Frame.type = b2_staticBody;
	//g2Frame.position = b2Vec2((winSize.width / 2.0f + 245) / RATIO, winSize.height / 2.0f / RATIO);
	//g2Frame.angle = 0;
	g2Frame.position = b2Vec2(winSize.width*0.5 + 245 * cos(-getR* 3.14 / 180.0f), winSize.height*0.5 + 245 * sin(-getR*3.14 / 180.0f));
	g2Frame.angle = -getR;
	b2Body *g22Body = mWorld->CreateBody(&g2Frame);
	CCSize g2Size = g2->getContentSize();
	b2PolygonShape g2Shape;
	g2Shape.SetAsBox(g2Size.width / 2.0f / RATIO, g2Size.height / 2.0f / RATIO);
	b2FixtureDef g22FixtureDef;
	g22FixtureDef.shape = &g2Shape;
	g22Body->CreateFixture(&g22FixtureDef);
	g2->setPTMRatio(RATIO);
	g2->setB2Body(g22Body);
	this->addChild(g2);

	g3 = B2Sprite::create("hole.png");
	b2BodyDef g3Frame;
	g3Frame.type = b2_staticBody;
	//g3Frame.position = b2Vec2(winSize.width / 2.0f / RATIO, (winSize.height / 2.0f + 245) / RATIO);
	//g3Frame.angle = -3.14 / 2.0f;
	g3Frame.position = b2Vec2(winSize.width*0.5 - 245 * sin(-getR* 3.14 / 180.0f), winSize.height*0.5 + 245 * cos(-getR*3.14 / 180.0f));
	g3Frame.angle = 90 - getR;
	b2Body *g3Body = mWorld->CreateBody(&g3Frame);
	CCSize g3Size = g3->getContentSize();
	b2PolygonShape g3Shape;
	g3Shape.SetAsBox(g3Size.width / 2.0f / RATIO, g3Size.height / 2.0f / RATIO);
	b2FixtureDef g3FixtureDef;
	g3FixtureDef.shape = &g3Shape;
	g3Body->CreateFixture(&g3FixtureDef);
	g3->setPTMRatio(RATIO);
	g3->setB2Body(g3Body);
	this->addChild(g3);

	g4 = B2Sprite::create("gate.png");
	b2BodyDef g4Frame;
	g4Frame.type = b2_staticBody;
	//g4Frame.position = b2Vec2((winSize.width / 2.0f - 245) / RATIO, winSize.height / 2.0f / RATIO);
	//g4Frame.angle = 3.14;
	g4Frame.position = b2Vec2(winSize.width*0.5 - 245 * cos(-getR* 3.14 / 180.0f), winSize.height*0.5 - 245 * sin(-getR*3.14 / 180.0f));
	g4Frame.angle = -getR;
	b2Body *g4Body = mWorld->CreateBody(&g4Frame);
	CCSize g4Size = g4->getContentSize();
	b2PolygonShape g4Shape;
	g4Shape.SetAsBox(g4Size.width / 2.0f / RATIO, g4Size.height / 2.0f / RATIO);
	b2FixtureDef g4FixtureDef;
	g4FixtureDef.shape = &g4Shape;
	g4Body->CreateFixture(&g4FixtureDef);
	g4->setPTMRatio(RATIO);
	g4->setB2Body(g4Body);
	this->addChild(g4);
	//---let's try it

	//---i want to show the points right now!!!
	label = CCLabelTTF::create("0", "arial", 32);
	label->setPosition(ccp(winSize.width / 2.0f, winSize.height - 80));
	this->addChild(label);
	//---plz work!

	this->scheduleUpdate();

	this->setAccelerometerEnabled(true);
	setTouchEnabled(true);

	return true;
}


void GameScene::menuCloseCallback(CCObject* pSender)
{
	this->unscheduleUpdate();
	auto *mScene = MenuScene::scene();
	this->unscheduleUpdate();
	CCDirector::sharedDirector()->replaceScene(mScene);

}

void GameScene::didAccelerate(CCAcceleration* pAccelerationValue){
#define frameMaxRotate 314
	frameRotate = frameMaxRotate * pAccelerationValue->x;
}

void GameScene::BeginContact(b2Contact *contact){
	if (contact->GetFixtureA()->GetBody()->GetUserData() == g4 ||
		contact->GetFixtureB()->GetBody()->GetUserData() == g4){
		score++;
	}
	if (contact->GetFixtureA()->GetBody()->GetUserData() == g1 ||
		contact->GetFixtureB()->GetBody()->GetUserData() == g1 ||
		contact->GetFixtureA()->GetBody()->GetUserData() == g2 ||
		contact->GetFixtureB()->GetBody()->GetUserData() == g2 ||
		contact->GetFixtureA()->GetBody()->GetUserData() == g3 ||
		contact->GetFixtureB()->GetBody()->GetUserData() == g3){
		score--;
	}
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	//ship_2->getB2Body()->SetLinearVelocity(b2Vec2(2.0*ship_2->getB2Body()->GetLinearVelocity().x, 2.0*ship_2->getB2Body()->GetLinearVelocity().y));
	//if (ship_2->getB2Body()->GetLinearVelocity().x == 0 && ship_2->getB2Body()->GetLinearVelocity().y == 0)
	//	ship_2->getB2Body()->SetLinearVelocity(b2Vec2(5.0f, 5.0f));
}