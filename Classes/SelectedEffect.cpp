//
//  SelectedEffect.cpp
//  stbProject
//
//  Created by Ryeeeeee on 14-6-23.
//
//

#include "SelectedEffect.h"

USING_NS_CC;

bool SelectedEffect::init(){
    _blink1 = Sprite::create("ring.png");
    _blink2 = Sprite::create("ring.png");
    _blink3 = Sprite::create("ring.png");
    
    _blink1->setVisible(false);
    _blink2->setVisible(false);
    _blink3->setVisible(false);
    
    this->addChild(_blink1);
    this->addChild(_blink2);
    this->addChild(_blink3);
    
    return true;
}

void SelectedEffect::runEffect(const std::function<void()>& callback){
    
    auto spawn = Spawn::create(ScaleTo::create(0.2, 2), FadeOut::create(0.2), NULL);
    
    auto effect1 = Sequence::create(Show::create(), spawn, RemoveSelf::create(), NULL);
    auto effect2 = Sequence::create(DelayTime::create(0.1), effect1->clone(), NULL);
    auto effect3 = Sequence::create(DelayTime::create(0.2), effect1->clone(), CallFunc::create(callback),NULL);
    
    _blink1->runAction(effect1);
    _blink2->runAction(effect2);
    _blink3->runAction(effect3);
    
}