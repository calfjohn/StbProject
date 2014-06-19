//
//  MaskLayer.h
//  MyCppGame
//
//  Created by EnCaL on 14-6-5.
//
//

#ifndef __MyCppGame__MaskLayer__
#define __MyCppGame__MaskLayer__

#include "cocos2d.h"

class MoreDetailLayer;
class MaskLayer : public cocos2d::Layer{
public:
    static MaskLayer* create(cocos2d::Sprite* pic);
    bool init(cocos2d::Sprite* pic);
    void closeMe();
private:
    cocos2d::Sprite *m_pic;
    MoreDetailLayer *m_moreDetailLayer;
};

#endif /* defined(__MyCppGame__MaskLayer__) */
