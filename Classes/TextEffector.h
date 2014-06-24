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

enum TextType{
    Movie,
    TV,
    Game,
    Setting
};

enum RotateDirection{
    LeftToRight,
    RightToLeft
};

class TextEffector : public cocos2d::Layer{
public:
    static TextEffector* create(TextType type, RotateDirection direction);
    bool init(TextType type, RotateDirection direction);
    
protected:
    float _rotateY = 90;
    float _topScaleX = 3;

    cocos2d::Node* _lightNode;
    cocos2d::Sprite* _light;
    cocos2d::Sprite* _lightTop;
    cocos2d::Sprite* _lightBottom;
    
    RotateDirection _direction;
    TextType _type;
    
    int _endFlag = 0;
    void update(float delta);
};

#endif /* defined(__stbProject__TextEffector__) */
