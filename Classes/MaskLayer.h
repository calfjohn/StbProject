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

#define ROW 7
#define COL 12

struct structCell{
    std::string fileName;
    cocos2d::Node* pNode;
    int type;/* 1 channel 2 video */
};

class MoreDetailLayer;
class MaskLayer : public cocos2d::Layer{
public:
    enum DIRECTION{
        LEFT,
        DOWN,
        RIGHT,
        UP
    };
    static MaskLayer* create(cocos2d::Sprite* pic);
    virtual void onExit();
    bool init(cocos2d::Sprite* pic);
    void closeMoreDetailLayer();
    void simulateFocusChanged(int tagLostFocus, int tagGetFocus);
    bool simulateFocusMove(MaskLayer::DIRECTION direction);
    // remote control event
    void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);
    void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
    void lostFocus();
    void getFocus();
    float countLeftMargin(int x, int y, cocos2d::Size blockSize);
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);
    bool dotGuyMap[20][20];
protected:
    void initTvMap();
    
    void createCellTv2();
    
    void addLight();

    void callback20();
    
    void callback21();
    
    void callback22();
    
    void callback23();
    
    void callback24();
    
    int index = 1;
    
    void initWithDotGuyMap();
    
    void initRemoteControl();
    cocos2d::ui::Widget *_widget;
    cocos2d::EventListenerFocus *_eventListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
    
    std::map<int, std::map<int, structCell>> _mapTv;
private:
    cocos2d::Sprite *m_pic;
    MoreDetailLayer *m_moreDetailLayer;
    cocos2d::Sprite* selectedSprite;
    cocos2d::Sprite* _rotateLight;
    cocos2d::Point recoverPoint;
    int recoverzOrder;
    cocos2d::Point _beginPoint;
    int nowTag;
};

#endif /* defined(__MyCppGame__MaskLayer__) */
