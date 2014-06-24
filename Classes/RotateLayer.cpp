//
//  RotateLayer.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-10.
//
//
#include "RotateLayer.h"
#include "SetTopBoxMainScene.h"
#include "TextEffector.h"
#include "PlayVideoLayer.h"
#include "MaskLayer.h"
#include "HelloWorldScene.h"
USING_NS_CC;
using namespace cocos2d::ui;

const float OPACITY_PARAM[4] = {1.0f, 0.9f, 0.45f, 0.9f};
const float SCALE_PARAM[4] = {1.0f, 0.45f, 0.4f, 0.45f};
const float ANIMATE_SPEED = 0.5f;
const int BEZIER_OFFSET_X[4] = {1, 0, 1, 0};
const int BEZIER_OFFSET_Y[4] = {0, 1, 0, 1};

RotateLayer* RotateLayer::create()
{
    auto pRet = new RotateLayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool RotateLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    isLocked = true;
    loadedCount = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    for(auto i = 0; i < 4; i++){
        pointGroup[i].x = visibleSize.width * 0.5 + origin.x;
        pointGroup[i].y = visibleSize.height * 0.5 + origin.y + 200;
    }
    pointGroup[0].y -= 200;     //bottom
    pointGroup[1].x -= 450;     //left
    pointGroup[2].y += 100;     //top
    pointGroup[3].x += 450;     //right
    
    for(auto i = 0; i < 4; i++){
        auto iconSprite = Sprite::create(StringUtils::format("icon%d.png", i).c_str());
        iconGroup.pushBack(iconSprite);
        iconSprite->setPosition(pointGroup[i]);
        this->addChild(iconSprite);
        iconSprite->setTag(i);
        iconSprite->setOpacity(0);
    }
    this->setIconScale();
    
    for(auto i = 0; i < 4; i++){
        iconGroup.at(i)->runAction(EaseSineOut::create(Sequence::create(FadeTo::create(0.5f, 255 * OPACITY_PARAM[i]),CallFunc::create([&](){
            loadedCount++;
            if (loadedCount >= 4){
                isLocked = false;
            }
        }), nullptr)));
    }
    _textEffector = TextEffector::create(TextType::TV);
    this->addChild(_textEffector);
    
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
    _eventListener->onFocusChanged = CC_CALLBACK_2(RotateLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(RotateLayer::onKeyboardReleased, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
    
    this->setTouchEnabled(true);
    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
    
    rotateRight();
    
    return true;
}

void RotateLayer::setIconScale()
{
    for(auto i = 0; i < 4; i++){
        auto iconSprite = iconGroup.at(i);
        iconSprite->setScale(SCALE_PARAM[i]);
        //iconSprite->setOpacity(255 * OPACITY_PARAM[i]);
    }
}

void RotateLayer::rotateLeft()
{
    isLocked = true;
    for(auto i = 0; i < 4; i++){
        auto iconSprite = iconGroup.at(i);
        auto nextSpriteTag = (iconSprite->getTag() + 1) % 4;
        //scale
        auto scaleTo = ScaleTo::create(ANIMATE_SPEED, SCALE_PARAM[nextSpriteTag]);
        //opacity
        auto opacityTo = FadeTo::create(ANIMATE_SPEED, 255 * OPACITY_PARAM[nextSpriteTag]);
        //bezier
        auto winSize = Director::getInstance()->getWinSize();
        ccBezierConfig bezierConfig;
        bezierConfig.controlPoint_1 = bezierConfig.controlPoint_2 = Vec2(pointGroup[(iconSprite->getTag() + BEZIER_OFFSET_X[iconSprite->getTag()]) % 4].x, pointGroup[(iconSprite->getTag() + BEZIER_OFFSET_Y[iconSprite->getTag()]) % 4].y);
        bezierConfig.endPosition = Vec2(pointGroup[nextSpriteTag]);
        auto bezierTo = BezierTo::create(ANIMATE_SPEED, bezierConfig);
        //runAction
        iconSprite->setTag(nextSpriteTag);
        iconSprite->runAction( EaseSineOut::create(Sequence::create( Spawn::create(scaleTo, opacityTo, EaseSineIn::create(bezierTo), nullptr), CallFunc::create([&](){
            isLocked = false;
        }), nullptr) ));
    }
}

void RotateLayer::rotateRight()
{
    isLocked = true;
    for(auto i = 0; i < 4; i++){
        auto iconSprite = iconGroup.at(i);
        auto nextSpriteTag = (iconSprite->getTag() + 3) % 4;
        //scale
        auto scaleTo = ScaleTo::create(ANIMATE_SPEED, SCALE_PARAM[nextSpriteTag]);
        //opacity
        auto opacityTo = FadeTo::create(ANIMATE_SPEED, 255 * OPACITY_PARAM[nextSpriteTag]);
        //bezier
        auto winSize = Director::getInstance()->getWinSize();
        ccBezierConfig bezierConfig;
        bezierConfig.controlPoint_1 = bezierConfig.controlPoint_2 = Vec2(pointGroup[(iconSprite->getTag() + 4 - BEZIER_OFFSET_X[iconSprite->getTag()]) % 4].x, pointGroup[(iconSprite->getTag() + 4 - BEZIER_OFFSET_Y[iconSprite->getTag()]) % 4].y);
        bezierConfig.endPosition = Vec2(pointGroup[nextSpriteTag]);
        auto bezierTo = BezierTo::create(ANIMATE_SPEED, bezierConfig);
        //runAction
        iconSprite->setTag(nextSpriteTag);
        iconSprite->runAction( EaseSineOut::create(Sequence::create( Spawn::create(scaleTo, opacityTo, EaseSineIn::create(bezierTo), nullptr), CallFunc::create([&](){
            isLocked = false;
        }), nullptr) ));
    }
}

void RotateLayer::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* e)
{
    
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ) {
        Director::getInstance()->end();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_DOWN) {
        MessageBox("down", "pressed");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_UP) {
        MessageBox("up", "pressed");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
        //MessageBox("left", "pressed");
        if (! isLocked){
            rotateLeft();
            if (_textEffector){
                _textEffector->removeFromParentAndCleanup(true);
            }
            for(auto i = 0; i < 4; i++){
                if (iconGroup.at(i)->getTag() == 0){
                    switch (i){
                        case 0:
                            _textEffector = TextEffector::create(TextType::TV);
                            break;
                        case 1:
                            _textEffector = TextEffector::create(TextType::Game);
                            break;
                        case 2:
                            _textEffector = TextEffector::create(TextType::Movie);
                            break;
                        case 3:
                            _textEffector = TextEffector::create(TextType::Setting);
                            break;
                    }
                }
            }
            this->addChild(_textEffector);
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT) {
        //MessageBox("right", "pressed");
        if (! isLocked){
            rotateRight();
            if (_textEffector){
                _textEffector->removeFromParentAndCleanup(true);
            }
            for(auto i = 0; i < 4; i++){
                if (iconGroup.at(i)->getTag() == 0){
                    switch (i){
                        case 0:
                            _textEffector = TextEffector::create(TextType::TV);
                            break;
                        case 1:
                            _textEffector = TextEffector::create(TextType::Game);
                            break;
                        case 2:
                            _textEffector = TextEffector::create(TextType::Movie);
                            break;
                        case 3:
                            _textEffector = TextEffector::create(TextType::Setting);
                            break;
                    }
                }
            }
            this->addChild(_textEffector);
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_MENU){
        Director::getInstance()->getRunningScene()->removeAllChildrenWithCleanup(true);
        Director::getInstance()->getRunningScene()->addChild(SetTopBoxMainScene::create());
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER || keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
        for(auto i = 0; i < 4; i++){
            if (iconGroup.at(i)->getTag() == 0){
                switch (i){
                    case 0:
                        MessageBox("tv", "pressed");
                        //this->addChild(PlayVideoLayer::create());
                        break;
                    case 1:
                    {
                        //MessageBox("game", "pressed");
                        auto newScene = HelloWorld::createScene();
                        auto FadeScene = TransitionFade::create(0.3f, newScene, Color3B::WHITE);
                        Director::getInstance()->replaceScene(FadeScene);
                        newScene->addChild(MaskLayer::create(Sprite::create("picture01.jpg")));
                    }
                        break;
                    case 2:
                        MessageBox("internet", "pressed");
                        break;
                    case 3:
                        MessageBox("system", "pressed");
                        break;
                }
            }
        }
    }
}

void RotateLayer::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    //一般只管定义状态
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus) {
        widgetGetFocus->setScale(1.2);
        widgetGetFocus->setColor(Color3B::RED);
    }
    
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus) {
        widgetLostFocus->setScale(1.0);
        widgetLostFocus->setColor(Color3B::WHITE);
    }
}

void RotateLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}

void RotateLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch *touch = touches.at(0);
    Point pt = touch->getLocationInView();
    pt = Director::getInstance()->convertToGL(pt);
    //    CCLOG("x=%f, y = %f", pt.x, pt.y);
    _beginPoint = pt;
}

void RotateLayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}

void RotateLayer::onTouchesCancelled(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}
void RotateLayer::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch *touch = touches.at(0);
    Point pt = touch->getLocationInView();
    pt = Director::getInstance()->convertToGL(pt);
    
    const float offest = 100;
    if (pt.x - _beginPoint.x > offest) {
        onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_RIGHT, nullptr);
    }
    
    if (pt.x - _beginPoint.x < -offest) {
        onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_LEFT, nullptr);
    }
    
    if (pt.y - _beginPoint.y < -offest) {
        onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_CENTER, nullptr);
    }
    
    if (pt.y - _beginPoint.y > offest) {
        onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_CENTER, nullptr);
    }
}