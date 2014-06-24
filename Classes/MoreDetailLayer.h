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
class MaskLayer;
class MoreDetailLayer : public cocos2d::Layer{
public:
    enum DIRECTION{
        LEFT,
        DOWN,
        RIGHT,
        UP
    };
    CREATE_FUNC(MoreDetailLayer);
    virtual bool init();
    virtual void onExit();
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);
    void simulateFocusChanged(int tagLostFocus, int tagGetFocus);
    bool simulateFocusMove(MoreDetailLayer::DIRECTION direction);
    // remote control event
    void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);
    void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
    void lostFocus();
    void getFocus();
    
    void setPreMaskLayer(MaskLayer* maskLayer){_preMaskLater = maskLayer;}
private:
    cocos2d::ui::Widget *_widget;
    cocos2d::EventListenerFocus *_eventListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    cocos2d::Sprite* selectedLightSprite;
    cocos2d::Sprite* playSprite;
    cocos2d::Point _beginPoint;
    MaskLayer* _preMaskLater;
    int nowTag;
};

#endif /* defined(__MyCppGame__MoreDetailLayer__) */
