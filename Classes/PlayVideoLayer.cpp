/*
//
//  PlayVideoLayer.cpp
//  stbProject
//
//  Created by LiuYuye on 14-6-17.
//
//

#include "PlayVideoLayer.h"
USING_NS_CC;
using namespace cocos2d::experimental::ui;

bool PlayVideoLayer::init()
{
    if (! Layer::init()){
        return false;
    }
    MenuItemFont::setFontSize(16);
    _visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    
    auto resourceVideo = MenuItemFont::create("Play resource video", CC_CALLBACK_1(PlayVideoLayer::menuResourceVideoCallback, this));
    resourceVideo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    resourceVideo->setPosition(Vec2(_visibleRect.origin.x + _visibleRect.size.width - 10,_visibleRect.origin.y + 50));
    
    createVideo();
    if (_videoPlayer)
    {
        _videoPlayer->setFileName("cocosvideo.mp4");
        _videoPlayer->play();
    }
    return true;
}

void PlayVideoLayer::menuResourceVideoCallback(Ref* sender)
{
    if (_videoPlayer)
    {
        _videoPlayer->setFileName("cocosvideo.mp4");
        _videoPlayer->play();
    }
}

void PlayVideoLayer::createVideo()
{
    auto centerPos = Vec2(_visibleRect.origin.x + _visibleRect.size.width / 2,_visibleRect.origin.y + _visibleRect.size.height /2);
    
    _videoPlayer = VideoPlayer::create();
    _videoPlayer->setPosition(centerPos);
    _videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _videoPlayer->setContentSize(Size(800, 600));
    this->addChild(_videoPlayer);
}
*/