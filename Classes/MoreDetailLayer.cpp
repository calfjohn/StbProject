//
//  MoreDetailLayer.cpp
//  MyCppGame
//
//  Created by EnCaL on 14-6-6.
//
//
#define GLOBAL_TOP 80000

#include "MoreDetailLayer.h"
#include "MaskLayer.h"
#include "PlayVideoLayer.h"
USING_NS_CC;
using namespace cocos2d::ui;
std::string _mapStr[2]{
    "XXXX",
    "X111"
};
bool MoreDetailLayer::init()
{
    if (! Layer::init()){
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("moreDetail/background.png");
    this->addChild(bg);
    bg->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.5 + origin.y));
    bg->setGlobalZOrder(GLOBAL_TOP);
    
    auto fg = Sprite::create("moreDetail/foreground.png");
    bg->addChild(fg);
    fg->setPosition(Vec2(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.5));
    fg->setGlobalZOrder(GLOBAL_TOP + 500);
    
    selectedLightSprite = Sprite::create("moreDetail/selectedLight.png");
    this->addChild(selectedLightSprite);
    selectedLightSprite->setGlobalZOrder(GLOBAL_TOP + 700);
    selectedLightSprite->setVisible(false);
    playSprite = Sprite::create("moreDetail/play.png");
    this->addChild(playSprite);
    playSprite->setGlobalZOrder(GLOBAL_TOP + 1000);
    playSprite->setVisible(false);
    
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
   
    int imageCount = 3;
    for (int i = 1; i <= imageCount; ++i) {
        std::string imageName = StringUtils::format("moreDetail/0%d.png", i);
        Sprite *countSprite = Sprite::create(imageName);
        countSprite->setGlobalZOrder(GLOBAL_TOP + 800);
        countSprite->setTag(i * 100 + 1);
        this->addChild(countSprite);
        countSprite->setPosition(Vec2(visibleSize.width * 0.4 + 100 * i + origin.x, visibleSize.height * 0.15 + origin.y));
        if (i == 1){
            nowTag = i * 100 + 1;
            selectedLightSprite->setVisible(true);
            selectedLightSprite->setPosition(countSprite->getPosition());
            playSprite->setVisible(true);
            playSprite->setPosition(countSprite->getPosition() + Vec2(0, 80));
            countSprite->setScale(1.3f);
        }
    }
    //register focus event
    _eventListener = EventListenerFocus::create();
    _eventListener->onFocusChanged = CC_CALLBACK_2(MoreDetailLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(MoreDetailLayer::onKeyboardReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
    
    onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_LEFT, nullptr);
    
    this->setTouchEnabled(true);
    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
    return true;
}

void MoreDetailLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}

void MoreDetailLayer::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* e)
{
    
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ) {
        _preMaskLater->closeMoreDetailLayer();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER || keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER || keyCode == EventKeyboard::KeyCode::KEY_MENU || keyCode == EventKeyboard::KeyCode::KEY_SPACE) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        //this->addChild(PlayVideoLayer::create());
        int x = nowTag / 100;
        if (x == 1){
            PlayVideoLayer::playVideoWithPath("stb1.mov");
        }
        else if (x == 2){
            PlayVideoLayer::playVideoWithPath("stb2.mp4");
        }
        else{
            PlayVideoLayer::playVideoWithPath("stb3.mov");
        }
#endif
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_DOWN || keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
        //_widget = _widget->findNextFocusedWidget(Widget::FocusDirection::DOWN, _widget);
        simulateFocusMove(MoreDetailLayer::DIRECTION::DOWN);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_UP || keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
        //_widget = _widget->findNextFocusedWidget(Widget::FocusDirection::UP, _widget);
        simulateFocusMove(MoreDetailLayer::DIRECTION::UP);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT || keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        //_widget = _widget->findNextFocusedWidget(Widget::FocusDirection::LEFT, _widget);
        simulateFocusMove(MoreDetailLayer::DIRECTION::LEFT);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT || keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        //_widget = _widget->findNextFocusedWidget(Widget::FocusDirection::RIGHT, _widget);
        simulateFocusMove(MoreDetailLayer::DIRECTION::RIGHT);
    }
}

void MoreDetailLayer::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus) {
        //selectedLightSprite->setVisible(true);
        selectedLightSprite->setPosition(Vec2(widgetGetFocus->getPosition().x, 1080 + widgetGetFocus->getPosition().y - 10));
        //playSprite->setVisible(true);
        playSprite->setPosition(Vec2(widgetGetFocus->getPosition().x, 1080 + widgetGetFocus->getPosition().y + 80));
        widgetGetFocus->setScale(1.3f);
    }
    
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus) {
        widgetLostFocus->setScale(1.0);
    }
}

void MoreDetailLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch *touch = touches.at(0);
    Point pt = touch->getLocationInView();
    pt = Director::getInstance()->convertToGL(pt);
    //    CCLOG("x=%f, y = %f", pt.x, pt.y);
    _beginPoint = pt;
}

void MoreDetailLayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}

void MoreDetailLayer::onTouchesCancelled(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}
void MoreDetailLayer::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
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

void MoreDetailLayer::lostFocus()
{
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}

void MoreDetailLayer::getFocus()
{
    //register focus event
    _eventListener = EventListenerFocus::create();
    _eventListener->onFocusChanged = CC_CALLBACK_2(MoreDetailLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(MoreDetailLayer::onKeyboardReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
}

void MoreDetailLayer::simulateFocusChanged(int tagLostFocus, int tagGetFocus)
{
    int getFocus_x = tagGetFocus / 100;
    int getFocus_y = tagGetFocus % 100;
    Sprite* getFocusSprite = (Sprite*)this->getChildByTag(getFocus_x * 100 + getFocus_y);
    selectedLightSprite->setPosition(getFocusSprite->getPosition());
    playSprite->setPosition(getFocusSprite->getPosition() + Vec2(0, 80));
    getFocusSprite->setScale(1.3f);
    
    int lostFocus_x = tagLostFocus / 100;
    int lostFocus_y = tagLostFocus % 100;
    Sprite* lostFocusSprite = (Sprite*)this->getChildByTag(lostFocus_x * 100 + lostFocus_y);
    lostFocusSprite->setScale(1.0f);
}

bool MoreDetailLayer::simulateFocusMove(MoreDetailLayer::DIRECTION direction)
{
    int x = nowTag / 100;
    int y = nowTag % 100;
    switch (direction) {
        case MoreDetailLayer::DIRECTION::LEFT:
            while(--x){
                if (_mapStr[y][x] == '1'){
                    int oldTag = nowTag;
                    nowTag = x * 100 + y;
                    simulateFocusChanged(oldTag, nowTag);
                    return true;
                }
            }
            return false;
            break;
        case MoreDetailLayer::DIRECTION::RIGHT:
            while(++x){
                if (x > 3) break;
                if (_mapStr[y][x] == '1'){
                    int oldTag = nowTag;
                    nowTag = x * 100 + y;
                    simulateFocusChanged(oldTag, nowTag);
                    return true;
                }
            }
            break;
            return false;
        default:
            return false;
    }
    return false;
}