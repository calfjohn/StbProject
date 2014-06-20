//
//  OpeningAnimation.h
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#ifndef __stbProject__OpeningAnimation__
#define __stbProject__OpeningAnimation__

#include "cocos2d.h"
class OpeningAnimation : public cocos2d::Layer{
public:
    static OpeningAnimation* create();
    bool init();
protected:
    cocos2d::ProgressTimer *progressLight;
    cocos2d::ParticleSystemQuad*    emitter;
    
    void addExplosionCallback();
    void addRotateLayerCallback();
};

#endif /* defined(__stbProject__OpeningAnimation__) */
