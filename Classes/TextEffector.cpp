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
    
//    TTFConfig ttfConfig;
//    ttfConfig.outlineSize = 5;
//    ttfConfig.fontFilePath = "britanic bold.ttf";
//    ttfConfig.fontSize = 50;
//    auto leftLabel = Label::createWithTTF(ttfConfig, "C");
//    leftLabel->enableOutline(Color4B::BLACK);
//    leftLabel->setPosition(origin.x, origin.y+ 60);
//    leftLabel->runAction(Sequence::create(DelayTime::create(1.0),
//                                          DelayTime::create(0.3),
//                                          DelayTime::create(0.05),
//                                          CallFunc::create([=](){leftLabel->setString("Co");}),
//                                          DelayTime::create(0.05),
//                                          CallFunc::create([=](){leftLabel->setString("Coc");}),
//                                          DelayTime::create(0.05),
//                                          CallFunc::create([=](){leftLabel->setString("Coco");}),
//                                          DelayTime::create(0.05),
//                                          CallFunc::create([=](){leftLabel->setString("Cocos");}),
//                                          NULL));
//    leftLabel->runAction(Sequence::create(DelayTime::create(1),
//                                          MoveTo::create(0.3, Point(origin.x+visibleSize.width/2,60)),
//                                          MoveBy::create(0.5, Point(-100,0)),
//                                          NULL));
//    this->addChild(leftLabel,2);
//    
//    auto particleLeft = ParticleSystemQuad::create("text_effect.plist");
//    particleLeft->setPositionType(ParticleSystem::PositionType::GROUPED);
//    particleLeft->setPosition(Point(origin.x,100));
//    particleLeft->setScale(1);
//    particleLeft->runAction(Sequence::create(DelayTime::create(1),
//                                             MoveTo::create(0.3, Point(origin.x+visibleSize.width/2,100)),
//                                             DelayTime::create(0.2),
//                                             RemoveSelf::create(),
//                                             NULL));
//    this->addChild(particleLeft);
//    
//    auto rightLabel = Label::createWithTTF(ttfConfig, "e");
//    rightLabel->setPosition(origin.x+visibleSize.width, origin.y+ 60);
//    rightLabel->runAction(Sequence::create(DelayTime::create(1.0),
//                                           DelayTime::create(0.3),
//                                           DelayTime::create(0.05),
//                                           CallFunc::create([=](){rightLabel->setString("ie");}),
//                                           DelayTime::create(0.05),
//                                           CallFunc::create([=](){rightLabel->setString("vie");}),
//                                           DelayTime::create(0.05),
//                                           CallFunc::create([=](){rightLabel->setString("ovie");}),
//                                           DelayTime::create(0.05),
//                                           CallFunc::create([=](){rightLabel->setString("Movie");}),
//                                           NULL));
//    rightLabel->runAction(Sequence::create(DelayTime::create(1),
//                                           MoveTo::create(0.3, Point(origin.x+visibleSize.width/2,60)),
//                                           MoveBy::create(0.5, Point(100,0)),
//                                           NULL));
//    
//    auto particleRight = ParticleSystemQuad::create("text_effect.plist");
//    particleRight->setPositionType(ParticleSystem::PositionType::GROUPED);
//    particleRight->setPosition(origin.x+visibleSize.width, origin.y+ 20);
//    particleRight->setScaleX(-1);
//    particleRight->runAction(Sequence::create(DelayTime::create(1),
//                                              MoveTo::create(0.3, Point(origin.x+visibleSize.width/2,20)),
//                                              DelayTime::create(0.2),
//                                              RemoveSelf::create(),
//                                              NULL));
//    this->addChild(particleRight);
//    this->addChild(rightLabel,2);
    
    _lightNode = Node::create();
    _lightNode->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + 100);
    _lightNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _lightNode->runAction(Repeat::create(Sequence::create(MoveBy::create(0.05, Vec2(10,0)),
                                                                 MoveBy::create(0.05, Vec2(-10,0)),
                                                                 NULL),5
                                         ));
    this->addChild(_lightNode,0);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto label = Label::createWithTTF("Co Mi", "dassault.ttf", 50);
#else
    auto label = Label::createWithTTF("Co Mi", "fonts/dassault.ttf", 50);
#endif
    
    label->setPosition(Vec2(0, -100));
    label->setRotation3D(Vec3(90, 0, 0));
    label->setColor(Color3B(163,241,255));
    label->setOpacity(255*0.8);
    label->runAction(Sequence::create(DelayTime::create(0.016),
                                      DelayTime::create(0.2),
                                      CallFunc::create([=](){label->setString("Cos Mie");}),
                                      DelayTime::create(0.02),
                                      CallFunc::create([=](){label->setString("Cocos Movie");}),
                                      DelayTime::create(0.05),
                                      NULL));
    _lightNode->addChild(label);
    
    //lightNode->runAction();
    _lightNode->setRotation3D(Vec3(-90, _rotateY, 0));
    
    //light
    _light = Sprite::create("text_light.png");
    _light->setPosition(origin.x + visibleSize.width / 2 + 150, origin.y + 65);
    //_light->setScale(1);
    _light->runAction(Sequence::create(MoveTo::create(0.15, Point(origin.x + visibleSize.width * 0.5f, origin.y + 65)),
                                       RemoveSelf::create(),
                                       NULL));
    this->addChild(_light,3);
    
    //light top
    _lightTop = Sprite::create("text_light_top.png");
    _lightTop->setPosition(origin.x + visibleSize.width/2 -100,origin.y +60);
    _lightTop->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    //_lightTop->setScale(1,1);
    _lightTop->runAction(Sequence::create(MoveTo::create(0.3, Point(origin.x+visibleSize.width/2+450,origin.y+60)),
//                                          ScaleTo::create(0.1,1,2),
                                          NULL));
    _lightTop->runAction(Sequence::create(DelayTime::create(0.2),
                                          Repeat::create(Sequence::create(FadeTo::create(0.07,30),
                                                                          FadeTo::create(0.07,100),
                                                                          NULL),2),
                                          RemoveSelf::create(),
                                          NULL));
    this->addChild(_lightTop,2);
    
    //light bottom
    _lightBottom = Sprite::create("text_light_bottom.png");
    _lightBottom->setScaleX(1);
    _lightBottom->setPosition(origin.x + visibleSize.width/2,origin.y + 50);
    _lightBottom->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _lightBottom->runAction(Sequence::create(MoveTo::create(0.3, Point(origin.x + visibleSize .width/2 - 600,origin.y+50)),
                                            NULL));
    _lightBottom->runAction(ScaleTo::create(0.3, 2, 1));
    _lightBottom->runAction(Sequence::create(DelayTime::create(0.2),
                                             Repeat::create(Sequence::create(FadeTo::create(0.07,30),
                                                            FadeTo::create(0.07,100),
                                                            NULL),2),
                                             RemoveSelf::create(),
                                             NULL));
    this->addChild(_lightBottom,2);
    
    this->scheduleUpdate();
    
    return true;
}

void TextEffector::update(float delta){
    
    //text
    if(_rotateY >= -25 && !_endFlag ){
        _rotateY = _rotateY - 8.0;
        //log(">-20 _%f",_rotateY);
    }
    else{
        _rotateY = (_rotateY + 8.0)>=0?0:(_rotateY + 8.0);
        //log("else _%f",_rotateY);
        _endFlag = true;
    }
    
    _lightNode->setRotation3D(Vec3(-90, _rotateY, 0));
    
}
