;//
//  OpeningAnimation.h
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#ifndef __stbProject__OpeningAnimation__
#define __stbProject__OpeningAnimation__

#include "cocos2d.h"

USING_NS_CC;

class Light;
class OpeningAnimation : public Layer{
public:
    static OpeningAnimation* create();
    bool init();
    void update(float dt);
protected:
    cocos2d::ProgressTimer *progressLight;
    cocos2d::ParticleSystemQuad*    emitter;
    
    void addExplosionCallback();
    void addRotateLayerCallback();
    Vector<Light*> lightVec;
    Node *lightNode;
};

class Light : public Sprite{
    
public:
    
    bool init(const std::string& filename);
    static Light* create(const std::string& filename);
    CC_SYNTHESIZE(float, scaleRan, ScaleRan);
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(int, direction, Direction);
};

#endif /* defined(__stbProject__OpeningAnimation__) */
