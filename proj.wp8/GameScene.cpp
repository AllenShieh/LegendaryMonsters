#include "GameScene.h"
#include "MenuScene.h"
#include "ResultScene.h"
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

	//---update the four points---
	for (int i = 0; i < 4; i++){
		if (sit[i] == 0){
			f_x[i] -= fracdiff;
			if (f_x[i] < 0){
				sit[i] = 1;
				f_x[i] = 0;
			}
			else if (f_x[i] > winSize.width){
				sit[i] = 3;
				f_x[i] = winSize.width;
			}
		}
		else if (sit[i] == 1){
			f_y[i] -= fracdiff;
			if (f_y[i] < 0){
				sit[i] = 2;
				f_y[i] = 0;
			}
			else if (f_y[i] > winSize.height){
				sit[i] = 0;
				f_y[i] = winSize.height;
			}
		}
		else if (sit[i] == 2){
			f_x[i] += fracdiff;
			if (f_x[i] > winSize.width){
				sit[i] = 3;
				f_x[i] = winSize.width;
			}
			else if (f_x[i] < 0){
				sit[i] = 1;
				f_x[i] = 0;
			}
		}
		else if (sit[i] == 3){
			f_y[i] += fracdiff;
			if (f_y[i] > winSize.height){
				sit[i] = 0;
				f_y[i] = winSize.height;
			}
			else if (f_y[i] < 0){
				sit[i] = 2;
				f_y[i] = 0;
			}
		}
	}

	f1->setPosition(ccp((f_x[0] + f_x[1]) / 2.0f, (f_y[0] + f_y[1]) / 2.0f));
	f1->setRotation(atan((f_y[0] - f_y[1]) / (f_x[0] - f_x[1]))*180.0 / 3.14);
	f1->setScale(sqrt((f_y[0] - f_y[1])*(f_y[0] - f_y[1]) + (f_x[0] - f_x[1])*(f_x[0] - f_x[1])) / 1415.0f);

	f2->setPosition(ccp((f_x[1] + f_x[2]) / 2.0f, (f_y[1] + f_y[2]) / 2.0f));
	f2->setRotation(atan((f_y[1] - f_y[2]) / (f_x[1] - f_x[2]))*180.0 / 3.14);
	f2->setScale(sqrt((f_y[1] - f_y[2])*(f_y[1] - f_y[2]) + (f_x[1] - f_x[2])*(f_x[1] - f_x[2])) / 1415.0f);

	f3->setPosition(ccp((f_x[2] + f_x[3]) / 2.0f, (f_y[2] + f_y[3]) / 2.0f));
	f3->setRotation(atan((f_y[2] - f_y[3]) / (f_x[2] - f_x[3]))*180.0 / 3.14);
	f3->setScale(sqrt((f_y[2] - f_y[3])*(f_y[2] - f_y[3]) + (f_x[2] - f_x[3])*(f_x[2] - f_x[3])) / 1415.0f);

	f4->setPosition(ccp((f_x[3] + f_x[0]) / 2.0f, (f_y[3] + f_y[0]) / 2.0f));
	f4->setRotation(atan((f_y[3] - f_y[0]) / (f_x[3] - f_x[0]))*180.0 / 3.14);
	f4->setScale(sqrt((f_y[3] - f_y[0])*(f_y[3] - f_y[0]) + (f_x[3] - f_x[0])*(f_x[3] - f_x[0])) / 1415.0f);
	//---

	g1->setPosition(ccp((f_x[0] + f_x[1]) / 2.0f, (f_y[0] + f_y[1]) / 2.0f));
	g2->setPosition(ccp((f_x[1] + f_x[2]) / 2.0f, (f_y[1] + f_y[2]) / 2.0f));
	g3->setPosition(ccp((f_x[2] + f_x[3]) / 2.0f, (f_y[2] + f_y[3]) / 2.0f));
	g4->setPosition(ccp((f_x[3] + f_x[0]) / 2.0f, (f_y[3] + f_y[0]) / 2.0f));


	//---uodate the physical world---
	mWorld->Step(dt, 8, 3);

	//---remove from the screen
	if (!s1_exist && !s1_delete){
		mWorld->DestroyBody(s1->getB2Body());
		s1->removeFromParent();
		s1_delete = true;
	}
	if (!s2_exist && !s2_delete){
		mWorld->DestroyBody(s2->getB2Body());
		s2->removeFromParent();
		s2_delete = true;
	}
	if (!s3_exist && !s3_delete){
		mWorld->DestroyBody(s3->getB2Body());
		s3->removeFromParent();
		s3_delete = true;
	}
	//---it is working

	char temp[20] = {};
	sprintf(temp, "%d / 3", score);
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
	CCMenuItemImage * item4 = CCMenuItemImage::create("3.png", "3.png", this, menu_selector(GameScene::menuCloseCallback));
	item4->setPosition(ccp(visibleSize.width*0.1, visibleSize.width*0.5));
	auto menu = CCMenu::create(item4, NULL);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	this->addChild(menu);

	score = 0;
	fracdiff = 0.0f;
	s1_exist = true;
	s2_exist = true;
	s3_exist = true;
	s1_delete = false;
	s2_delete = false;
	s3_delete = false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	f_x[0] = winSize.width;
	f_y[0] = winSize.height;
	f_x[1] = 0;
	f_y[1] = winSize.height;
	f_x[2] = 0;
	f_y[2] = 0;
	f_x[3] = winSize.width;
	f_y[3] = 0;
	sit[0] = 0;
	sit[1] = 1;
	sit[2] = 2;
	sit[3] = 3;

	mWorld = new b2World(b2Vec2(0, 0));
	mWorld->SetContactListener(this);

	//---bigger edges~
	f1 = B2Sprite::create("bian3.png");
	b2BodyDef f1Frame;
	f1Frame.type = b2_staticBody;
	f1Frame.position = b2Vec2(winSize.width / 2.0f, winSize.height - 20);
	f1Frame.angle = 0;
	b2Body *f1Body = mWorld->CreateBody(&f1Frame);
	CCSize f1Size = f1->getContentSize();
	b2PolygonShape f1Shape;
	f1Shape.SetAsBox(f1Size.width / 2.0f / RATIO, f1Size.height / 2.0f / RATIO);
	b2FixtureDef f1FixtureDef;
	f1FixtureDef.shape = &f1Shape;
	f1Body->CreateFixture(&f1FixtureDef);
	f1->setPTMRatio(RATIO);
	f1->setB2Body(f1Body);
	this->addChild(f1);

	f2 = B2Sprite::create("bian3.png");
	b2BodyDef f2Frame;
	f2Frame.type = b2_staticBody;
	f2Frame.position = b2Vec2(20, winSize.height / 2.0f);
	f2Frame.angle = 90;
	b2Body *f2Body = mWorld->CreateBody(&f2Frame);
	CCSize f2Size = f2->getContentSize();
	b2PolygonShape f2Shape;
	f2Shape.SetAsBox(f2Size.width / 2.0f / RATIO, f2Size.height / 2.0f / RATIO);
	b2FixtureDef f2FixtureDef;
	f2FixtureDef.shape = &f2Shape;
	f2Body->CreateFixture(&f2FixtureDef);
	f2->setPTMRatio(RATIO);
	f2->setB2Body(f2Body);
	this->addChild(f2);

	f3 = B2Sprite::create("bian3.png");
	b2BodyDef f3Frame;
	f3Frame.type = b2_staticBody;
	f3Frame.position = b2Vec2(winSize.width / 2.0f, 20);
	f3Frame.angle = 0;
	b2Body *f3Body = mWorld->CreateBody(&f3Frame);
	CCSize f3Size = f3->getContentSize();
	b2PolygonShape f3Shape;
	f3Shape.SetAsBox(f3Size.width / 2.0f / RATIO, f3Size.height / 2.0f / RATIO);
	b2FixtureDef f3FixtureDef;
	f3FixtureDef.shape = &f3Shape;
	f3Body->CreateFixture(&f3FixtureDef);
	f3->setPTMRatio(RATIO);
	f3->setB2Body(f3Body);
	this->addChild(f3);

	f4 = B2Sprite::create("bian3.png");
	b2BodyDef f4Frame;
	f4Frame.type = b2_staticBody;
	f4Frame.position = b2Vec2(winSize.width - 20, winSize.height / 2.0f);
	f4Frame.angle = 90;
	b2Body *f4Body = mWorld->CreateBody(&f4Frame);
	CCSize f4Size = f4->getContentSize();
	b2PolygonShape f4Shape;
	f4Shape.SetAsBox(f4Size.width / 2.0f / RATIO, f4Size.height / 2.0f / RATIO);
	b2FixtureDef f4FixtureDef;
	f4FixtureDef.shape = &f4Shape;
	f4Body->CreateFixture(&f4FixtureDef);
	f4->setPTMRatio(RATIO);
	f4->setB2Body(f4Body);
	this->addChild(f4);
	//---let's see what happens

	//---add test object---
	ship_2 = B2Sprite::create("1.png");
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(winSize.width / 2.5f / RATIO, winSize.height / 3.0f / RATIO);
	b2Body *shipBody = mWorld->CreateBody(&bodyDef);
	CCSize shipSize = ship_2->getContentSize();
	//b2PolygonShape shipShape;
	b2CircleShape shipShape;
	shipShape.m_radius = shipSize.height / 2.0f / RATIO;
	//shipShape.SetAsBox(shipSize.width / 2.0f / RATIO, shipSize.height / 2.0f / RATIO);
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
	
	//---add gates---
	g1 = B2Sprite::create("hole.png");
	b2BodyDef g1Frame;
	g1Frame.type = b2_staticBody;
	g1Frame.position = b2Vec2((f_x[0] + f_x[1]) / 2.0f, (f_y[0] + f_y[1]) / 2.0f);
	//g1Frame.angle = 0;
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
	g2Frame.position = b2Vec2((f_x[1] + f_x[2]) / 2.0f, (f_y[1] + f_y[2]) / 2.0f);
	//g2Frame.angle = 0;
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
	g3Frame.position = b2Vec2((f_x[2] + f_x[3]) / 2.0f, (f_y[2] + f_y[3]) / 2.0f);
	//g3Frame.angle = 0;
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
	g4Frame.position = b2Vec2((f_x[3] + f_x[0]) / 2.0f, (f_y[3] + f_y[0]) / 2.0f);
	//g4Frame.angle = 0;
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

	//---add stars---
	s1 = B2Sprite::create("star.png");
	b2BodyDef s1bodyDef;
	s1bodyDef.type = b2_dynamicBody;
	s1bodyDef.position = b2Vec2(winSize.width / 4.0f / RATIO, winSize.height / 2.0f / RATIO);
	b2Body *s1Body = mWorld->CreateBody(&s1bodyDef);
	CCSize s1Size = s1->getContentSize();
	b2PolygonShape s1Shape;
	s1Shape.SetAsBox(s1Size.width / 2.0f / RATIO, s1Size.height / 2.0f / RATIO);
	b2FixtureDef s1FixtureDef;
	s1FixtureDef.shape = &s1Shape;
	s1FixtureDef.density = 0.000000000001f;
	s1FixtureDef.restitution = 0.1f;
	s1FixtureDef.friction = 1.0f;
	s1Body->CreateFixture(&s1FixtureDef);
	s1->setPTMRatio(RATIO);
	s1->setB2Body(s1Body);
	this->addChild(s1);

	s2 = B2Sprite::create("star.png");
	b2BodyDef s2bodyDef;
	s2bodyDef.type = b2_dynamicBody;
	s2bodyDef.position = b2Vec2(winSize.width * 3.0f / 4.0f / RATIO, winSize.height / 2.0f / RATIO);
	b2Body *s2Body = mWorld->CreateBody(&s2bodyDef);
	CCSize s2Size = s2->getContentSize();
	b2PolygonShape s2Shape;
	s2Shape.SetAsBox(s2Size.width / 2.0f / RATIO, s2Size.height / 2.0f / RATIO);
	b2FixtureDef s2FixtureDef;
	s2FixtureDef.shape = &s2Shape;
	s2FixtureDef.density = 0.000000000001f;
	s2FixtureDef.restitution = 0.1f;
	s2FixtureDef.friction = 1.0f;
	s2Body->CreateFixture(&s2FixtureDef);
	s2->setPTMRatio(RATIO);
	s2->setB2Body(s2Body);
	this->addChild(s2);

	s3 = B2Sprite::create("star.png");
	b2BodyDef s3bodyDef;
	s3bodyDef.type = b2_dynamicBody;
	s3bodyDef.position = b2Vec2(winSize.width / 2.0f / RATIO, winSize.height / 4.0f / RATIO);
	b2Body *s3Body = mWorld->CreateBody(&s3bodyDef);
	CCSize s3Size = s3->getContentSize();
	b2PolygonShape s3Shape;
	s3Shape.SetAsBox(s3Size.width / 2.0f / RATIO, s3Size.height / 2.0f / RATIO);
	b2FixtureDef s3FixtureDef;
	s3FixtureDef.shape = &s3Shape;
	s3FixtureDef.density = 0.000000000001f;
	s3FixtureDef.restitution = 0.1f;
	s3FixtureDef.friction = 1.0f;
	s3Body->CreateFixture(&s3FixtureDef);
	s3->setPTMRatio(RATIO);
	s3->setB2Body(s3Body);
	this->addChild(s3);
	//---let's try

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
	fracdiff = -pAccelerationValue->x * 20.0f;
}

void GameScene::BeginContact(b2Contact *contact){
	if ((contact->GetFixtureA()->GetBody()->GetUserData() == g4&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
		(contact->GetFixtureB()->GetBody()->GetUserData() == g4&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2)){
		CCScene *rScene = CCScene::create();
		ResultScene *layer = ResultScene::create();
		layer->setResult(true);
		rScene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, rScene));
	}
	else if ((contact->GetFixtureA()->GetBody()->GetUserData() == g1&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
		(contact->GetFixtureB()->GetBody()->GetUserData() == g1&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2) ||
		(contact->GetFixtureA()->GetBody()->GetUserData() == g2&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
		(contact->GetFixtureB()->GetBody()->GetUserData() == g2&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2) ||
		(contact->GetFixtureA()->GetBody()->GetUserData() == g3&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
		(contact->GetFixtureB()->GetBody()->GetUserData() == g3&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2)){
		CCScene *rScene = CCScene::create();
		ResultScene *layer = ResultScene::create();
		layer->setResult(false);
		rScene->addChild(layer);
		CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f, rScene));
	}
	if (s1_exist){
		if ((contact->GetFixtureA()->GetBody()->GetUserData() == s1&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
			(contact->GetFixtureB()->GetBody()->GetUserData() == s1&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2)){
			score++;
			//s1->removeFromParentAndCleanup(true);
			s1_exist = false;
		}
	}
	if (s2_exist){
		if ((contact->GetFixtureA()->GetBody()->GetUserData() == s2&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
			(contact->GetFixtureB()->GetBody()->GetUserData() == s2&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2)){
			score++;
			//s2->removeFromParentAndCleanup(true);
			s2_exist = false;
		}
	}
	if (s3_exist){
		if ((contact->GetFixtureA()->GetBody()->GetUserData() == s3&&contact->GetFixtureB()->GetBody()->GetUserData() == ship_2) ||
			(contact->GetFixtureB()->GetBody()->GetUserData() == s3&&contact->GetFixtureA()->GetBody()->GetUserData() == ship_2)){
			score++;
			//s3->removeFromParentAndCleanup(true);
			s3_exist = false;
		}
	}
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	ship_2->getB2Body()->SetLinearVelocity(b2Vec2(2.0*ship_2->getB2Body()->GetLinearVelocity().x, 2.0*ship_2->getB2Body()->GetLinearVelocity().y));
}