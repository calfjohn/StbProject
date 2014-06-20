//
//  EffectManager.cpp
//  stbProject
//
//  Created by Ryeeeeee on 14-6-19.
//
//

#include "EffectManager.h"
#include "cocos2d.h"

USING_NS_CC;

EffectManager g_effectManager;

void EffectManager::lazyInit(){
    initAnimation();
}

void EffectManager::initAnimation(){
    
    auto cellAnimation = Animation::create();
    for (int i = 1; i <= 4; i++) {
        cellAnimation->addSpriteFrameWithFile(StringUtils::format("animation_frame%d.png", i).c_str());
    }
    cellAnimation->setDelayPerUnit(0.1f);
    cellAnimation->setLoops(1);
    AnimationCache::getInstance()->addAnimation(cellAnimation, "CellAnimation");
}