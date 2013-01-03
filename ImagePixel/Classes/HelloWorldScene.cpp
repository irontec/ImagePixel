#include "HelloWorldScene.h"
#include "CCTexture2DMutable.h"

USING_NS_CC;

CCRect rect(CCPoint position, CCSize size)
{
    return CCRectMake(position.x - size.width/2, position.y - size.height/2, size.width, size.height);
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCImage *image = new CCImage();
    image->initWithImageFile("example.png");
    
    texture = new CCTexture2DMutable();
    texture->initWithImage(image);
    
    sprite = CCSprite::create();
    sprite->initWithTexture(texture);
    sprite->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(sprite);
    
    CCLabelTTF *label = CCLabelTTF::create("", "Verdana-BoldItalic", 15);
    label->setColor(ccWHITE);
    label->setTag(1);
    label->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 - 75));
    label->setString("Touch sprite");
    this->addChild(label);
    
    return true;
}

void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool HelloWorld::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
    CCPoint touchLocation = touch->getLocation();
    CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(1);
    
    CCRect r = rect(sprite->getPosition(), sprite->getContentSize());
    
    CCLog("RECT:(%f,%f) TOUCH:(%f,%f)", r.origin.x, r.origin.y, touchLocation.x, touchLocation.y);
    
    if (r.containsPoint(touchLocation)) {
        int x = touchLocation.x - r.origin.x;
        int y = sprite->getContentSize().height - (touchLocation.y - r.origin.y);
        CCPoint p = CCPointMake(x, y);
        ccColor4B color = texture->pixelAt(p);
        CCLog("R:%d G:%d B:%d AT POINT: (%d,%d)", color.r, color.g, color.b, x, y);
        
        //Update label
        char rgbString [50];
        sprintf (rgbString, "R:%d G:%d B:%d", color.r, color.g, color.b);
        label->setString(rgbString);
    } else {
        label->setString("Out of rect");
    }
	
	return true;
}

