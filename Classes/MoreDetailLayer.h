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
#include "ui/CocosGUI.h"

class MoreDetailLayer : public cocos2d::Layer{
public:
    CREATE_FUNC(MoreDetailLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);
    // remote control event
    void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);
    void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
private:
    cocos2d::ui::Widget *_widget;
    cocos2d::EventListenerFocus *_eventListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    cocos2d::Sprite* selectedLightSprite;
    cocos2d::Sprite* playSprite;
    cocos2d::Point _beginPoint;
};

#endif /* defined(__MyCppGame__MoreDetailLayer__) */
