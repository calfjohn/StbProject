//
//  TextEffector.h
//  stbProject
//
//  Created by EnCaL on 14-6-11.
//
//

#ifndef __stbProject__TextEffector__
#define __stbProject__TextEffector__

#include "cocos2d.h"
class TextEffector : public cocos2d::Layer{
public:
    static TextEffector* create();
    bool init();
    
protected:
    float _rotateY = 90;
    float _topScaleX = 3;

    cocos2d::Node* _lightNode;
    cocos2d::Sprite* _light;
    cocos2d::Sprite* _lightTop;
    cocos2d::Sprite* _lightBottom;
    
    int _endFlag = 0;
    void update(float delta);
};

#endif /* defined(__stbProject__TextEffector__) */
