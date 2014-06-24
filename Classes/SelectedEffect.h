//
//  SelectedEffect.h
//  stbProject
//
//  Created by Ryeeeeee on 14-6-23.
//
//

#ifndef __stbProject__SelectedEffect__
#define __stbProject__SelectedEffect__

#include "cocos2d.h"

class SelectedEffect : public cocos2d::Node{
public:
    CREATE_FUNC(SelectedEffect);
    virtual bool init();
    
    void runEffect(const std::function<void()>& callback);
    
protected:
    cocos2d::Sprite* _blink1;
    cocos2d::Sprite* _blink2;
    cocos2d::Sprite* _blink3;
};

#endif /* defined(__stbProject__SelectedEffect__) */
