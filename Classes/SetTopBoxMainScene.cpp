//
//  SetTopBoxMainScene.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#include "SetTopBoxMainScene.h"
#include "OpeningAnimation.h"
USING_NS_CC;

Scene* SetTopBoxMainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SetTopBoxMainScene::create();
    scene->addChild(layer);
    return scene;
}

SetTopBoxMainScene* SetTopBoxMainScene::create()
{
    auto pRet = new SetTopBoxMainScene();
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

bool SetTopBoxMainScene::init()
{
    if (! Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create("background.png");
    this->addChild(background);
    background->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SetTopBoxMainScene::replayCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    menu->setVisible(false);
    
    this->addChild(OpeningAnimation::create());
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BMG.ogg");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BMG.ogg", true);
    
    return true;
}

void SetTopBoxMainScene::replayCallback(Ref* sender){

    Director::getInstance()->replaceScene(SetTopBoxMainScene::createScene());
}
