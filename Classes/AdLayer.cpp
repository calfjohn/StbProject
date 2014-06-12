//
//  adLayer.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-9.
//
//

#include "AdLayer.h"
USING_NS_CC;
AdLayer* AdLayer::create()
{
    auto pRet = new AdLayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool AdLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    auto adCount = 4;
    for(int i = 1; i <= adCount; i++){
        char tmp[128] = {0};
        sprintf(tmp, "banner_0%d.jpg", i);
        auto bannerSprite = Sprite::create(tmp);
        spriteGroup.pushBack(bannerSprite);
        bannerSprite->setTag(i);
        this->addChild(bannerSprite);
        bannerSprite->setPosition(winSize * 0.5);
    }
    
    return true;
}