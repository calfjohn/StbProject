//
//  adLayer.h
//  stbProject
//
//  Created by EnCaL on 14-6-9.
//
//

#ifndef __stbProject__adLayer__
#define __stbProject__adLayer__

#include "cocos2d.h"
class AdLayer : public cocos2d::Layer{
public:
    static AdLayer* create();
    bool init();
protected:
    cocos2d::Vector<cocos2d::Sprite*> spriteGroup;
    cocos2d::Vector<cocos2d::MenuItemImage*> itemImageGroup;
};

#endif /* defined(__stbProject__adLayer__) */
