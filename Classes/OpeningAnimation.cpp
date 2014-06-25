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
    
    auto boardNode = Node::create();
    auto board = Sprite::create("board.png");
    
    boardNode->setPosition(Point(origin.x + visibleSize.width/2, 200 + origin.y));
    //
    board->runAction(RepeatForever::create(RotateBy::create(0.5, 30)));
    boardNode->setScale(1, 0.000);
    
    boardNode->addChild(board);
    this->addChild(boardNode,4);
    
    lightNode = Node::create();
    
    lightNode->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5-330));
    addChild(lightNode);
    
    boardSprite = Sprite::create("MainMenu/boardLight.png");
    boardSprite->setPosition(0,0);
    lightNode->addChild(boardSprite,4);
    boardSprite->runAction(RepeatForever::create(Sequence::create(RotateBy::create(5, 5), RotateBy::create(5, -5),RotateBy::create(5, -5),RotateBy::create(5, 5), NULL)));
    boardSprite->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(3, 0.8),ScaleTo::create(3, 1),ScaleTo::create(3, 1.2),ScaleTo::create(3, 1),NULL)));
    boardSprite->setTag(10);
    boardSprite->setScale(0);
    
    lightBackground = Sprite::create("MainMenu/lightBackground.png");
    lightBackground->setAnchorPoint(Vec2(626.0f/1216.0f, (746-713)/746.0f));
    lightBackground->setPosition(boardSprite->getPosition());
    lightNode->addChild(lightBackground,2);
    lightBackground->setOpacity(200);
    lightBackground->setScale(0.0f);
    
//    lightNode->setScale(0);
    
    for(int i=0;i<10 ;i++){
        
        float randF = rand()%3+2;
        auto light = Light::create("MainMenu/light.png");
        light->setAnchorPoint(Vec2(158.0f/305.f, (752.0f-747.0f)/752.0f));
        light->setPosition(boardSprite->getPosition());
        light->setScaleRan(randF);
        light->setScale(0);
        light->setBlendFunc(BlendFunc::ADDITIVE);
        light->setOpacity(20);
        light->setSpeed(0.03*(rand()%10));
        light->setDirection(i-2);
        light->setRotation(10*(i-4));
        lightNode->addChild(light,3);
        
        lightVec.pushBack(light);
    }
    
    rotateLayerFlag = true;
    

//    progressLight = ProgressTimer::create(Sprite::create("light.png"));
//    progressLight->setType(ProgressTimer::Type::BAR);
//    progressLight->setMidpoint(Vec2(0, 0));
//    progressLight->setBarChangeRate(Vec2(0, 1));
//    progressLight->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y - 55));
//    this->addChild(progressLight);
//    
    //auto explosionCallback =
//    boardNode->runAction(EaseSineOut::create(Sequence::create(DelayTime::create(0.5),ScaleTo::create(0.7,1,0.25),CallFunc::create([&](){
//        progressLight->runAction(Spawn::create(
//                                               Sequence::create(FadeIn::create(0.4f),
//                                                                CallFunc::create(std::bind(&OpeningAnimation::addExplosionCallback, this)),
//                                                                DelayTime::create(0.8),
//                                                                EaseExponentialOut::create(ProgressTo::create(0.8f, 100)),
//                                                                //DelayTime::create(1.5),
//                                                                CallFunc::create(std::bind(&OpeningAnimation::addRotateLayerCallback, this)), nullptr), nullptr));
//    }), nullptr)));
    
    boardNode->runAction(EaseSineOut::create(Sequence::create(DelayTime::create(0.5),ScaleTo::create(2,1,0.25),nullptr)));
    emitter = ParticleSystemQuad::create("mystic.plist");
    addChild(emitter);
    
    emitter->setPosition(Point(origin.x + visibleSize.width/2, 200 + origin.y));
    scheduleUpdate();

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

void OpeningAnimation::update(float dt){
    
    for(auto i=0;i<lightVec.size();i++){
        
        auto light = lightVec.at(i);
        if(light->getDirection()<0){
            light->setRotation(light->getRotation()-light->getSpeed());
            if(light->getRotation()<-30)
                light->setDirection(1);
        }else{
            light->setRotation(light->getRotation()+light->getSpeed());
            if(light->getRotation()>30)
                light->setDirection(-1);
        }
    }
    
    if(boardSprite->getScale()<1){
        boardSprite->setScale(boardSprite->getScale()+0.1);
    }
    
    if(boardSprite->getScaleX()>0.8){

        if(lightBackground->getScale()<1){
            lightBackground->setScale(lightBackground->getScale()+0.05);
        }
    
        for(auto light : lightVec){
        
            if(light->getScale()<light->getScaleRan()){
                light->setScale(light->getScale()+0.05);
            }
        }
    }
    
    if(lightBackground->getScale()>0.7 && rotateLayerFlag){
        
        addRotateLayerCallback();
        rotateLayerFlag=false;
    }
}

bool Light::init(const std::string &filename){
    
    if(Sprite::init()){
        
        setTexture(filename);
        return true;
    }
    
    return false;
}

Light* Light::create(const std::string &filename){
    
    auto pRet = new Light();
    if (pRet && pRet->init(filename)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

