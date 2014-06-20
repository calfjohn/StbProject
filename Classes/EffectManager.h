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

class EffectManager{
public:
    void lazyInit();
    void initAnimation();
};

extern EffectManager g_effectManager;

#endif /* defined(__stbProject__EffectManager__) */
