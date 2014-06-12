//
//  SetTopBoxMainScene.h
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#ifndef __stbProject__SetTopBoxMainScene__
#define __stbProject__SetTopBoxMainScene__
#include "cocos2d.h"
class SetTopBoxMainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    static SetTopBoxMainScene* create();
    bool init();
};

#endif /* defined(__stbProject__SetTopBoxMainScene__) */
