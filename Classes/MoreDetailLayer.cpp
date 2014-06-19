//
//  MoreDetailLayer.cpp
//  MyCppGame
//
//  Created by EnCaL on 14-6-6.
//
//

#include "MoreDetailLayer.h"
USING_NS_CC;
using namespace cocos2d::ui;

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
    
    auto fg = Sprite::create("moreDetail/foreground.png");
    bg->addChild(fg);
    fg->setPosition(Vec2(bg->getContentSize().width * 0.5, bg->getContentSize().height * 0.5));
    
    VBox *outerLayout = VBox::create();
    //only the first outer layout should care about the position, all the other layout and element
    //they should care only about their layout and layoutParameter type
    outerLayout->setPosition(Point(0, visibleSize.height));
    outerLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
    
    LinearLayoutParameter *layoutParams = LinearLayoutParameter::create();
    layoutParams->setMargin(Margin(0, 0, 0, 0));
    
    HBox *bottomLayout = HBox::create();
    bottomLayout->setLayoutParameter(layoutParams);
    bottomLayout->setFocused(true);
    _widget = bottomLayout;
    
    LinearLayoutParameter *bottomLayoutParameters = LinearLayoutParameter::create();
    float leftOffset = 860;
    float offsetHeight = 905;
    
    int imageCount = 3;
    for (int i = 1; i <= imageCount; ++i) {
        std::string imageName = StringUtils::format("moreDetail/0%d.png", i);
        ImageView *imageView = ImageView::create(imageName);
        if (i == 1){
            bottomLayoutParameters->setMargin(Margin(leftOffset,offsetHeight, 0, 0));
        }
        else{
            bottomLayoutParameters->setMargin(Margin(leftOffset, offsetHeight, - 760, 0));
        }
        imageView->setLayoutParameter(bottomLayoutParameters);
        //you don't set the postion of each imageview, the layout will handle it
        bottomLayout->addChild(imageView);
    }
    outerLayout->addChild(bottomLayout);
    this->addChild(outerLayout);
    //register focus event
    _eventListener = EventListenerFocus::create();
    _eventListener->onFocusChanged = CC_CALLBACK_2(MoreDetailLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(MoreDetailLayer::onKeyboardReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
    
    selectedLightSprite = Sprite::create("moreDetail/selectedLight.png");
    this->addChild(selectedLightSprite);
    selectedLightSprite->setVisible(false);
    playSprite = Sprite::create("moreDetail/play.png");
    this->addChild(playSprite);
    playSprite->setVisible(false);
    
    this->setTouchEnabled(true);
    this->setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
    return true;
}

void MoreDetailLayer::onEnter()
{
    Layer::onEnter();
    /*auto winSize = Director::getInstance()->getWinSize();
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto myListener = EventListenerTouchOneByOne::create();
    myListener->setSwallowTouches(true);
    myListener->onTouchBegan = [=](Touch* touch, Event* event){
        Point touchLocation = touch->getLocation();
        touchLocation = this->getParent()->convertToNodeSpace(touchLocation);
        Rect rect = Rect( (winSize.width - this->getContentSize().width * 0.8) / 2, (winSize.height - this->getContentSize().height * 0.8) / 2, this->getContentSize().width * 0.8, this->getContentSize().height * 0.8);
        if (! rect.containsPoint(touchLocation)){
            return false;
        }
        
        return true;
    };
    dispatcher->addEventListenerWithSceneGraphPriority(myListener, this);*/
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
        Director::getInstance()->end();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
        CCLOG("enter pressed");
        MessageBox("enter", "pressed");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_DOWN) {
        _widget = _widget->findNextFocusedWidget(Widget::FocusDirection::DOWN, _widget);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_UP) {
        _widget = _widget->findNextFocusedWidget(Widget::FocusDirection::UP, _widget);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_LEFT) {
        _widget = _widget->findNextFocusedWidget(Widget::FocusDirection::LEFT, _widget);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_RIGHT) {
        _widget = _widget->findNextFocusedWidget(Widget::FocusDirection::RIGHT, _widget);
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_MENU){
        MessageBox("menu", "pressed");
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER) {
        MessageBox("center", "pressed");
    }
}

void MoreDetailLayer::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    //一般只管定义状态
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus) {
        selectedLightSprite->setVisible(true);
        selectedLightSprite->setPosition(Vec2(widgetGetFocus->getPosition().x, 1080 + widgetGetFocus->getPosition().y - 10));
        CCLOG("%f,%f",widgetGetFocus->getPosition().x, widgetGetFocus->getPosition().y);
        playSprite->setVisible(true);
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