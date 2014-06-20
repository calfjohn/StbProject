#include "HelloWorldScene.h"
#include "MaskLayer.h"
#include "AdLayer.h"
#include "RotateLayer.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("background.png");
    this->addChild(bg);
    bg->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    return true;
}