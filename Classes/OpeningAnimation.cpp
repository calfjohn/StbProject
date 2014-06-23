//
//  OpeningAnimation.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#include "OpeningAnimation.h"
#include "RotateLayer.h"
#include "ExplosionEffect.h"

USING_NS_CC;

OpeningAnimation* OpeningAnimation::create()
{
    auto pRet = new OpeningAnimation();
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

bool OpeningAnimation::init()
{
    if (! Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto light = Sprite::create("Comet.png");
    auto boardNode = Node::create();
    auto board = Sprite::create("board.png");
    
    light->setColor(Color3B(139,255,255));
    
    boardNode->setPosition(Point(origin.x + visibleSize.width/2, 200 + origin.y));
    light->setPosition(Point(origin.x + visibleSize.width/2, 200 + origin.y));
    //
    light->runAction(Sequence::create(ScaleTo::create(0.5f,800/64.0f,0.01),RemoveSelf::create(), NULL));
    board->runAction(RepeatForever::create(RotateBy::create(0.5, 30)));
    //boardNode->setScale(1, 0.25);
    boardNode->setScale(1, 0.000);
    
    boardNode->addChild(board);
    this->addChild(boardNode,1);
    this->addChild(light,1);

    progressLight = ProgressTimer::create(Sprite::create("light.png"));
    progressLight->setType(ProgressTimer::Type::BAR);
    progressLight->setMidpoint(Vec2(0, 0));
    progressLight->setBarChangeRate(Vec2(0, 1));
    progressLight->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y - 55));
    this->addChild(progressLight);
    
    //auto explosionCallback =
    boardNode->runAction(Sequence::create(DelayTime::create(0.5),ScaleTo::create(0.7,1,0.25),CallFunc::create([&](){
        progressLight->runAction(Spawn::create(
                                               Sequence::create(FadeIn::create(0.4f),
                                                                CallFunc::create(std::bind(&OpeningAnimation::addExplosionCallback, this)),
                                                                DelayTime::create(0.8),
                                                                EaseExponentialOut::create(ProgressTo::create(0.8f, 100)),
                                                                //DelayTime::create(1.5),
                                                                CallFunc::create(std::bind(&OpeningAnimation::addRotateLayerCallback, this)), nullptr), nullptr));
    }), nullptr));
    
    emitter = ParticleSystemQuad::create("mystic.plist");
    addChild(emitter);
    
    emitter->setPosition(Point(origin.x + visibleSize.width/2, 200 + origin.y));

    return true;
}

void OpeningAnimation::addExplosionCallback(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto explosion = ExplosionEffect::create();
    explosion->setPosition(visibleSize.width/2 - 200 + origin.x, origin.y);
    this->addChild(explosion);
}

void OpeningAnimation::addRotateLayerCallback(){
    this->addChild(RotateLayer::create());
}
