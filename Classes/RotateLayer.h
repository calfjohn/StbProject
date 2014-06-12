//
//  RotateLayer.h
//  stbProject
//
//  Created by EnCaL on 14-6-10.
//
//

#ifndef __stbProject__RotateLayer__
#define __stbProject__RotateLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class TextEffector;
class RotateLayer : public cocos2d::Layer{
public:
    static RotateLayer* create();
    bool init();
    
    virtual void onExit();
    
    void setIconScale();
    void rotateLeft();
    void rotateRight();
    
    void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);
    void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
protected:
    bool isLocked;
    int loadedCount;
    cocos2d::Vector<cocos2d::Sprite*> iconGroup;
    cocos2d::Vec2 pointGroup[4];
    cocos2d::ui::Widget *_widget;
    cocos2d::EventListenerFocus *_eventListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    TextEffector *_textEffector;
};

#endif /* defined(__stbProject__RotateLayer__) */
