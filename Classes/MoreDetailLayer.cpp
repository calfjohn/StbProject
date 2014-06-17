//
//  MoreDetailLayer.cpp
//  MyCppGame
//
//  Created by EnCaL on 14-6-6.
//
//

#include "MoreDetailLayer.h"
USING_NS_CC;

bool MoreDetailLayer::init()
{
    if (! Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("moreDetail/moreDetail_bg.png");
    this->addChild(bg);
    bg->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    
    return true;
}

void MoreDetailLayer::onEnter()
{
    Layer::onEnter();
    auto winSize = Director::getInstance()->getWinSize();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto myListener = EventListenerTouchOneByOne::create();
    myListener->setSwallowTouches(true);
    myListener->onTouchBegan = [=](Touch* touch, Event* event){
        Point touchLocation = touch->getLocation();
        touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
        Rect rect = Rect( (winSize.width - this->getContentSize().width * 0.8) / 2, (winSize.height - this->getContentSize().height * 0.8) / 2, this->getContentSize().width * 0.8, this->getContentSize().height * 0.8);
        if (! rect.containsPoint(touchLocation)){
            return false;
        }
        
        return true;
    };
    dispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
}

void MoreDetailLayer::onExit()
{
    Layer::onExit();
}