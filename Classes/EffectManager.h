//
//  EffectManager.h
//  stbProject
//
//  Created by Ryeeeeee on 14-6-19.
//
//

#ifndef __stbProject__EffectManager__
#define __stbProject__EffectManager__

#include <iostream>
#include "cocos2d.h"

enum EffectTypes{
    cellBlink
};

class EffectManager{
public:
    void lazyInit();
    void initAnimation();
    cocos2d::Animation* getAnimationByType(EffectTypes type);
};

extern EffectManager g_effectManager;

#endif /* defined(__stbProject__EffectManager__) */
