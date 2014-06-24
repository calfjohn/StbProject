//
//  TextEffector.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#include "TextEffector.h"

USING_NS_CC;

TextEffector* TextEffector::create(TextType type, RotateDirection direction)
{
    auto pRet = new TextEffector();
    if (pRet && pRet->init(type, direction)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool TextEffector::init(TextType type, RotateDirection direction)
{
    if (! Layer::init()){
        return false;
    }
    
    _type = type;
    _direction = direction;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _lightNode = Node::create();
    _lightNode->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + 100);
    _lightNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _lightNode->runAction(Repeat::create(Sequence::create(EaseSineOut::create(MoveBy::create(0.05, Vec2(10,0))),
                                                          EaseSineOut::create(MoveBy::create(0.05, Vec2(-10,0))),
                                                          NULL),5
                                         ));
    this->addChild(_lightNode,0);
    
    std::string content;
    switch (_type) {
        case TextType::Game:
            content = "Game";
            break;
        case TextType::Movie:
            content = "Movie";
            break;
        case TextType::Setting:
            content = "Setting";
            break;
        case TextType::TV:
            content = "TV";
            break;
        default:
            break;
    }
    
    switch (_direction) {
        case LeftToRight:
            _rotateY = 90;
            break;
        case RightToLeft:
            _rotateY = -90;
            break;
        default:
            break;
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto label = Label::createWithTTF(content, "dassault.ttf", 50);
#else
    auto label = Label::createWithTTF(content, "fonts/dassault.ttf", 50);
#endif
    
    label->setPosition(Vec2(0, -100));
    label->setRotation3D(Vec3(90, 0, 0));
    //label->setColor(Color3B(163,241,255));
    label->setOpacity(255*0.8);
    label->runAction(Sequence::create(DelayTime::create(0.016),
                                      DelayTime::create(0.2),
                                      CallFunc::create([=](){label->setString(content);}),
                                      DelayTime::create(0.02),
                                      CallFunc::create([=](){label->setString(content);}),
                                      DelayTime::create(0.05),
                                      NULL));
    _lightNode->addChild(label);
    
    //lightNode->runAction();
    _lightNode->setRotation3D(Vec3(-90, _rotateY, 0));
    
    //light
    _light = Sprite::create("text_light.png");
    _light->setPosition(origin.x + visibleSize.width / 2 + 150, origin.y + 65);
    _light->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(0.15, Vec2(origin.x + visibleSize.width * 0.5f, origin.y + 65))),
                                       RemoveSelf::create(),
                                       NULL));
    this->addChild(_light,3);
    
    //light top
    _lightTop = Sprite::create("text_light_top.png");
    _lightTop->setPosition(origin.x + visibleSize.width/2 - 100,origin.y +60);
    _lightTop->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    _lightTop->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(0.3, Vec2(origin.x+visibleSize.width/2+350,origin.y+60))),
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
    _lightBottom->runAction(Sequence::create(EaseSineOut::create(MoveTo::create(0.3, Vec2(origin.x + visibleSize .width/2 - 500,origin.y+50))),
                                            NULL));
    _lightBottom->runAction(ScaleTo::create(0.3, 2, 1));
    _lightBottom->runAction(Sequence::create(DelayTime::create(0.2),
                                             Repeat::create(Sequence::create(FadeTo::create(0.07,30),
                                                            FadeTo::create(0.07,100),
                                                            NULL),2),
                                             RemoveSelf::create(),
                                             NULL));
    this->addChild(_lightBottom,2);
    
//    auto node = Sprite::create("animation_frame1.png");
//    auto cellAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("CellAnimation"));
//    node->runAction(cellAnimate);
//    this->addChild(node);
//    node->setPosition(Vec2(origin.x + 400, origin.y + 400));
//
    
    this->scheduleUpdate();
    
    return true;
}

void TextEffector::update(float delta){
    
    switch (_direction) {
        case LeftToRight:
            if(_rotateY <= 25 && !_endFlag ){
                _rotateY = _rotateY + 8.0;
            }
            else{
                _rotateY = (_rotateY - 8.0)<=0?0:(_rotateY - 8.0);
                _endFlag = true;
            }
            break;
        case RightToLeft:
            if(_rotateY >= -25 && !_endFlag ){
                _rotateY = _rotateY - 8.0;
            }
            else{
                _rotateY = (_rotateY + 8.0)>=0?0:(_rotateY + 8.0);
                _endFlag = true;
            }
            break;
        default:
            break;
    }
    
    _lightNode->setRotation3D(Vec3(-90, _rotateY, 0));
    
}
