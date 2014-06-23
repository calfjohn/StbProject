
//
//  PlayVideoLayer.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-17.
//
//

#include "PlayVideoLayer.h"
#include "MoreDetailLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
USING_NS_CC;
using namespace cocos2d::experimental::ui;

bool PlayVideoLayer::init()
{
    if (! Layer::init()){
        return false;
    }
    MenuItemFont::setFontSize(16);
    _visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    
    createVideo();
    
    playResourceVideo();
    
    /* ==============test============== */
    LinearLayoutParameter *layoutParams = LinearLayoutParameter::create();
    layoutParams->setMargin(Margin(59,40,0,0));
    
    //first layout 显示上面一排按钮 HBox
    HBox *layoutHeader = HBox::create();
    //    layoutHeader->setLoopFocus(true);
    layoutHeader->setLayoutParameter(layoutParams);
    layoutHeader->setFocused(true);
    _widget = layoutHeader;
    /* ==============test============== */
    
    //register focus event
    _eventListener = EventListenerFocus::create();
    _eventListener->onFocusChanged = CC_CALLBACK_2(PlayVideoLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayVideoLayer::onKeyboardReleased, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
    
    return true;
}

void PlayVideoLayer::playResourceVideo()
{
    if (_videoPlayer)
    {
        _videoPlayer->setFileName("cocosvideo.mp4");
        _videoPlayer->play();
    }
}

void PlayVideoLayer::pauseVideo()
{
    if (_videoPlayer){
        _videoPlayer->pause();
    }
}

void PlayVideoLayer::resumeVideo()
{
    if (_videoPlayer){
        _videoPlayer->resume();
    }
}

void PlayVideoLayer::createVideo()
{
    auto centerPos = Vec2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);
    _videoPlayer = VideoPlayer::create();
    _videoPlayer->setPosition(centerPos);
    _videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _videoPlayer->setContentSize(_visibleRect.size);
    this->addChild(_videoPlayer);
    _videoPlayer->setFullScreenEnabled(true);
}


void PlayVideoLayer::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* e)
{
    
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ) {
        MoreDetailLayer* moreDetailLayer = dynamic_cast<MoreDetailLayer*>(this->getParent());
        if (moreDetailLayer){
            moreDetailLayer->getFocus();
        }
        this->removeFromParentAndCleanup(true);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER) {
        if (_videoPlayer){
            if (_videoPlayer->isPlaying()){
                pauseVideo();
            }
            else{
                resumeVideo();
            }
        }
        
    }
}

void PlayVideoLayer::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
}

void PlayVideoLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}
#endif