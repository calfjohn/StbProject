//
//  MoreDetailLayer.h
//  MyCppGame
//
//  Created by EnCaL on 14-6-6.
//
//

#ifndef __MyCppGame__MoreDetailLayer__
#define __MyCppGame__MoreDetailLayer__

#include "cocos2d.h"

class MoreDetailLayer : public cocos2d::LayerColor{
public:
    static MoreDetailLayer* create();
    bool init();
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__MyCppGame__MoreDetailLayer__) */
