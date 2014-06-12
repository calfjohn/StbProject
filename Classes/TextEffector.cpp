//
//  TextEffector.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#include "TextEffector.h"
USING_NS_CC;

TextEffector* TextEffector::create()
{
    auto pRet = new TextEffector();
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

bool TextEffector::init()
{
    if (! Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    TTFConfig ttfConfig;
    ttfConfig.outlineSize = 5;
    ttfConfig.fontFilePath = "britanic bold.ttf";
    ttfConfig.fontSize = 50;
    auto leftLabel = Label::createWithTTF(ttfConfig, "C");
    leftLabel->enableOutline(Color4B::BLACK);
    leftLabel->setPosition(origin.x, origin.y+ 60);
    leftLabel->runAction(Sequence::create(DelayTime::create(0.3),
                                          DelayTime::create(0.1),
                                          CallFunc::create([=](){leftLabel->setString("Co");}),
                                          DelayTime::create(0.1),
                                          CallFunc::create([=](){leftLabel->setString("Coc");}),
                                          DelayTime::create(0.1),
                                          CallFunc::create([=](){leftLabel->setString("Coco");}),
                                          DelayTime::create(0.1),
                                          CallFunc::create([=](){leftLabel->setString("Cocos");}),
                                          NULL));
    leftLabel->runAction(Sequence::create(MoveTo::create(0.3, Point(origin.x+visibleSize.width/2,60)),
                                          MoveBy::create(0.5, Point(-100,0)),
                                          NULL));
    this->addChild(leftLabel,2);
    
    auto rightLabel = Label::createWithTTF(ttfConfig, "M");
    rightLabel->setPosition(visibleSize.width, origin.y+ 60);
    rightLabel->runAction(Sequence::create(DelayTime::create(0.3),
                                           DelayTime::create(0.1),
                                           CallFunc::create([=](){rightLabel->setString("Mo");}),
                                           DelayTime::create(0.1),
                                           CallFunc::create([=](){rightLabel->setString("Mov");}),
                                           DelayTime::create(0.1),
                                           CallFunc::create([=](){rightLabel->setString("Movi");}),
                                           DelayTime::create(0.1),
                                           CallFunc::create([=](){rightLabel->setString("Movie");}),
                                           NULL));
    rightLabel->runAction(Sequence::create(MoveTo::create(0.3, Point(origin.x+visibleSize.width/2,60)),
                                           MoveBy::create(0.5, Point(100,0)),
                                           NULL));
    this->addChild(rightLabel,2);
    return true;
}
