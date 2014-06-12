//
//  MaskLayer.cpp
//  MyCppGame
//
//  Created by EnCaL on 14-6-5.
//
//

#include "MaskLayer.h"
#include "MoreDetailLayer.h"
USING_NS_CC;

#define FIRST_TIME 0.25f
#define SECOND_TIME 0.5f

MaskLayer* MaskLayer::create(cocos2d::Sprite* pic)
{
    MaskLayer *pRet = new MaskLayer();
    if (pRet && pRet->init(pic)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MaskLayer::init(cocos2d::Sprite* pic)
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto winSize = Director::getInstance()->getWinSize();
    auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 160), winSize.width,winSize.height);
    this->addChild(maskLayer);
        
    m_moreDetailLayer = MoreDetailLayer::create();
    this->addChild(m_moreDetailLayer);
    m_moreDetailLayer->setVisible(false);
        
    m_pic = pic;
    this->addChild(pic);
    pic->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.5));
    
    auto actionOrb = OrbitCamera::create(FIRST_TIME, 1.0f, 0.0f, 0.0f, 90.0f, 0.0f, 0.0f);
    pic->runAction(Sequence::create(actionOrb, CallFunc::create([this](){
        m_pic->setVisible(false);
        m_moreDetailLayer->setVisible(true);
        auto actionOrb = OrbitCamera::create(SECOND_TIME, 1.0f, 0.0f, 270.0f, 90.0f, 0.0f, 0.0f);
        m_moreDetailLayer->setScale(0.4f);
        auto actionScaleTo = ScaleTo::create(SECOND_TIME, 0.8f);
        m_moreDetailLayer->runAction(Spawn::create(actionOrb, actionScaleTo, NULL));
        }), NULL));
    return true;
}

void MaskLayer::onEnter()
{
    Layer::onEnter();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto myListener = EventListenerTouchOneByOne::create();
    myListener->setSwallowTouches(true);
    myListener->onTouchBegan = [=](Touch* touch, Event* event){
        if (m_moreDetailLayer->isVisible()){
            auto winSize = Director::getInstance()->getWinSize();
            auto actionOrb = OrbitCamera::create(SECOND_TIME, 1.0f, 0.0f, 360.0f, -90.0f, 0.0f, 0.0f);
            m_moreDetailLayer->setScale(0.8f);
            auto actionScaleTo = ScaleTo::create(SECOND_TIME, 0.4f);
            m_moreDetailLayer->runAction(Sequence::create(Spawn::create(actionOrb, actionScaleTo, NULL),CallFunc::create([this](){
                    m_pic->setVisible(true);
                    auto actionOrb = OrbitCamera::create(FIRST_TIME, 1.0f, 0.0f, 90.0f, -90.0f, 0.0f, 0.0f);
                    m_pic->runAction(Sequence::create(actionOrb, CallFunc::create([this](){
                        this->removeFromParentAndCleanup(true);
                    }), NULL));
                }) , NULL));
        }
        return true;
    };
    dispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
}

void MaskLayer::onExit()
{
    Layer::onExit();
}