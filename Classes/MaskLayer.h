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

struct structCell{
    std::string fileName;
    cocos2d::Node* pNode;
    int type;/* 1 channel 2 video */
};

class MoreDetailLayer;
class MaskLayer : public cocos2d::Layer{
public:
    static MaskLayer* create(cocos2d::Sprite* pic);
    virtual void onExit();
    bool init(cocos2d::Sprite* pic);
    void closeMoreDetailLayer();
    // remote control event
    void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);
    void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
protected:
    void initTvMap();
    
    void createCellTv2();
    
    void callback21();
    
    void callback22();
    
    void callback23();
    
    void callback24();
    
    int index = 1;
    
    void initRemoteControl();
    cocos2d::ui::Widget *_widget;
    cocos2d::EventListenerFocus *_eventListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    
    std::map<int, std::map<int, structCell>> _mapTv;
private:
    cocos2d::Sprite *m_pic;
    MoreDetailLayer *m_moreDetailLayer;
    cocos2d::Sprite* selectedSprite;
};

#endif /* defined(__MyCppGame__MaskLayer__) */
