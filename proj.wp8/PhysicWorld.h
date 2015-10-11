#ifndef __PHYSICAL_SCENE_H__
#define __PHYSICAL_SCENE_H__

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "ExtensionMacros.h"

USING_NS_CC;


//---borrow from http://code1.okbase.net/codefile/B2Sprite.h_2014022525776_4.htm
//---see if this is working
class B2Sprite : public CCSprite
{
protected:
	bool    m_bIgnoreBodyRotation;

	b2Body  *m_pB2Body;

	// Pixels to Meters ratio
	float   m_fPTMRatio;
public:
	B2Sprite();

	static B2Sprite* create();
	/** Creates an sprite with a texture.
	The rect used will be the size of the texture.
	The offset will be (0,0).
	*/
	static B2Sprite* createWithTexture(CCTexture2D *pTexture);

	/** Creates an sprite with a texture and a rect.
	The offset will be (0,0).
	*/
	static B2Sprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);

	/** Creates an sprite with an sprite frame. */
	static B2Sprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

	/** Creates an sprite with an sprite frame name.
	An CCSpriteFrame will be fetched from the CCSpriteFrameCache by name.
	If the CCSpriteFrame doesn't exist it will raise an exception.
	@since v0.9
	*/
	static B2Sprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

	/** Creates an sprite with an image filename.
	The rect used will be the size of the image.
	The offset will be (0,0).
	*/
	static B2Sprite* create(const char *pszFileName);

	/** Creates an sprite with an image filename and a rect.
	The offset will be (0,0).
	*/
	static B2Sprite* create(const char *pszFileName, const CCRect& rect);

	virtual bool isDirty();

	/** Keep the sprite's rotation separate from the body. */
	bool isIgnoreBodyRotation() const;
	void setIgnoreBodyRotation(bool bIgnoreBodyRotation);

	virtual const CCPoint& getPosition();
	virtual void getPosition(float* x, float* y);
	virtual float getPositionX();
	virtual float getPositionY();
	virtual void setPosition(const CCPoint &position);
	virtual float getRotation();
	virtual void setRotation(float fRotation);
	virtual CCAffineTransform nodeToParentTransform();

	/** Body accessor when using box2d */
	b2Body* getB2Body() const;
	void setB2Body(b2Body *pBody);

	float getPTMRatio() const;
	void setPTMRatio(float fPTMRatio);

protected:
	void updatePosFromPhysics();
};
#endif