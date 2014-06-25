
//
//  PlayVideoLayer.h
//  stbProject
//
//  Created by EnCaL on 14-6-17.
//
//

#ifndef __stbProject__PlayVideoLayer__
#define __stbProject__PlayVideoLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class PlayVideoLayer : public cocos2d::Layer{
public:
    CREATE_FUNC(PlayVideoLayer);
    virtual bool init();
    virtual void onExit();
    static void playVideoWithPath(const char* path);
    void playResourceVideo();
    void pauseVideo();
    void resumeVideo();
    
    void onFocusChanged(cocos2d::ui::Widget* widgetLostFocus, cocos2d::ui::Widget* widgetGetFocus);
    void onKeyboardReleased(cocos2d::EventKeyboard::KeyCode, cocos2d::Event*);
private:
    void createVideo();
    experimental::ui::VideoPlayer* _videoPlayer;

    Rect _visibleRect;
    cocos2d::ui::Widget *_widget;
    cocos2d::EventListenerFocus *_eventListener;
    cocos2d::EventListenerKeyboard* _keyboardListener;
};
#endif
#endif /*defined(__stbProject__PlayVideoLayer__) */
