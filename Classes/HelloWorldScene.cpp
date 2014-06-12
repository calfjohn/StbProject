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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto buttonItem = MenuItemImage::create("CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(HelloWorld::menuCallback1,this));
    buttonItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 - 100,
                                origin.y + closeItem->getContentSize().height/2));

    auto buttonMenu = Menu::create(buttonItem, nullptr);
    buttonMenu->setPosition(Vec2::ZERO);
    this->addChild(buttonMenu, 2);
    
    
    auto buttonItem2 = MenuItemImage::create("CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(HelloWorld::menuCallback2,this));
    buttonItem2->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 - 200,
                                 origin.y + closeItem->getContentSize().height/2));
    
    auto buttonMenu2 = Menu::create(buttonItem2, nullptr);
    buttonMenu2->setPosition(Vec2::ZERO);
    this->addChild(buttonMenu2, 2);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto rotateLayer = RotateLayer::create();
    this->addChild(rotateLayer);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    auto test = MaskLayer::create(Sprite::create("picture01.jpg"));
    this->addChild(test);
    return;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuCallback1(cocos2d::Ref* pSender)
{
    auto winSize = Director::getInstance()->getWinSize();
    auto countDownBg = Sprite::create("countdown_11.png");
    countDownBg->setPosition(winSize * 0.5);
    this->addChild(countDownBg);
    
    auto countDownfg = Sprite::create("countdown_12.png");
    countDownfg->setPosition(winSize * 0.5);
    this->addChild(countDownfg);
    countDownfg->runAction(RepeatForever::create(RotateBy::create(1.0f, -360)));
}

void HelloWorld::menuCallback2(cocos2d::Ref* pSender)
{
    auto test = AdLayer::create();
    this->addChild(test);
}

