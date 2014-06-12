//
//  MoreDetailLayer.cpp
//  MyCppGame
//
//  Created by EnCaL on 14-6-6.
//
//

#include "MoreDetailLayer.h"
USING_NS_CC;
MoreDetailLayer* MoreDetailLayer::create()
{
    MoreDetailLayer *pRet = new MoreDetailLayer();
    if (pRet && pRet->init() && pRet->initWithColor(Color4B(255, 255, 255, 255))){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MoreDetailLayer::init()
{
    auto bRet = false;
    do {
        bRet = true;
    } while ( 0 );
    return bRet;
}

void MoreDetailLayer::onEnter()
{
    LayerColor::onEnter();
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
    LayerColor::onExit();
}