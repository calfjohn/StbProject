
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
    /*
     ==========menuCallback============
     */
    void menuResourceVideoCallback(Ref* sender);
    void menuFullScreenCallback(Ref* sender);
    void menuPauseCallback(Ref* sender);
    void menuResumeCallback(Ref* sender);
    void menuStopCallback(Ref* sender);
    void menuHintCallback(Ref* sender);
    
private:
    void createVideo();
    experimental::ui::VideoPlayer* _videoPlayer;

    Rect _visibleRect;
    Layout* _widget;
};
#endif
#endif /*defined(__stbProject__PlayVideoLayer__) */
