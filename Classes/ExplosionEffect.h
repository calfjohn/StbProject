//
//  ExplosionEffect.h
//  stbProject
//
//  Created by Ryeeeeee on 14-6-20.
//
//

#ifndef __stbProject__ExplosionEffect__
#define __stbProject__ExplosionEffect__

#include <iostream>
#include "cocos2d.h"

class ExplosionEffect : public cocos2d::Node{
public:
    CREATE_FUNC(ExplosionEffect);
    virtual bool init();
    
protected:
    void addExplosionCallBack(float dt);
};

#endif /* defined(__stbProject__ExplosionEffect__) */
