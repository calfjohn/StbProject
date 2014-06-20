//
//  MaskLayer.cpp
//  MyCppGame
//
//  Created by EnCaL on 14-6-5.
//
//

#include "MaskLayer.h"
#include "MoreDetailLayer.h"
#include "cellTv.h"
#include "RectangleInterface.h"
USING_NS_CC;
using namespace cocos2d::ui;

#define FIRST_TIME 0.25f
#define SECOND_TIME 0.5f

#define NODE_TAG 1234

#define ROW 7
#define COL 12

#define TEXTURE_WIDTH 133
#define TEXTURE_HEIGHT 133

#define CELL_SPACE 5

std::string mapStr[8]{
    "XXXXXXXXXXXXX",
    "X001000000000",
    "X011100111100",
    "X000110111110",
    "X011111111100",
    "X111111111110",
    "X011111100001",
    "X011001000111"
};

MaskLayer* MaskLayer::create(cocos2d::Sprite* pic)
{
    MaskLayer *pRet = new MaskLayer();
    if (pRet && pRet->init(pic)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MaskLayer::init(cocos2d::Sprite* pic)
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Director::getInstance()->setDepthTest(false);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /*  it should be somewhere else now--lijun modify it
    auto winSize = Director::getInstance()->getWinSize();
    auto maskLayer = LayerColor::create(Color4B(0, 0, 0, 160), winSize.width,winSize.height);
    this->addChild(maskLayer);
        
    m_moreDetailLayer = MoreDetailLayer::create();
    this->addChild(m_moreDetailLayer);
    m_moreDetailLayer->setVisible(false);
    m_moreDetailLayer->setPreMaskLayer(this);
        
    m_pic = pic;
    this->addChild(pic);
    pic->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.5));
    
    auto actionOrb = OrbitCamera::create(FIRST_TIME, 1.0f, 0.0f, 0.0f, 90.0f, 0.0f, 0.0f);
    pic->runAction(Sequence::create(actionOrb, CallFunc::create([this](){
        m_pic->setVisible(false);
        m_moreDetailLayer->setVisible(true);
        auto actionOrb = OrbitCamera::create(SECOND_TIME, 1.0f, 0.0f, 270.0f, 90.0f, 0.0f, 0.0f);
        m_moreDetailLayer->setScale(0.4f);
        auto actionScaleTo = ScaleTo::create(SECOND_TIME, 0.9f);
        m_moreDetailLayer->runAction(Spawn::create(actionOrb, actionScaleTo, NULL));
        }), NULL));
*/
    selectedSprite = Sprite::create("selectedBlock.png");
    this->addChild(selectedSprite);
    selectedSprite->setVisible(false);
    
    RectangleInterface::initialize(ROW, COL, Size(TEXTURE_WIDTH, TEXTURE_HEIGHT), CELL_SPACE, Vec2(visibleSize.width/2, visibleSize.height/2));
    
    initTvMap();
    
    createCellTv2();

    return true;
}

void MaskLayer::closeMoreDetailLayer()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto actionOrb = OrbitCamera::create(SECOND_TIME, 1.0f, 0.0f, 360.0f, -90.0f, 0.0f, 0.0f);
    m_moreDetailLayer->setScale(0.8f);
    auto actionScaleTo = ScaleTo::create(SECOND_TIME, 0.4f);
    m_moreDetailLayer->runAction(Sequence::create(Spawn::create(actionOrb, actionScaleTo, NULL), CallFunc::create([this](){
        m_pic->setVisible(true);
        auto actionOrb = OrbitCamera::create(FIRST_TIME, 1.0f, 0.0f, 90.0f, -90.0f, 0.0f, 0.0f);
        m_pic->runAction(Sequence::create(actionOrb, CallFunc::create([&](){
            _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
            _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
        }), NULL));
    }) , NULL));
}



void MaskLayer::initTvMap()
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("tvMap.plist");
    
    structCell cell;
    
    cell.fileName = "cell01";
    cell.pNode = NULL;
    cell.type = 2;
    
    
    _mapTv[1][3] = cell;
    
    _mapTv[2][2] = cell;
    _mapTv[2][3] = cell;
    _mapTv[2][4] = cell;
    _mapTv[2][7] = cell;
    _mapTv[2][8] = cell;
    _mapTv[2][9] = cell;
    _mapTv[2][10] = cell;
    
    _mapTv[3][4] = cell;
    _mapTv[3][5] = cell;
    _mapTv[3][7] = cell;
    _mapTv[3][8] = cell;
    _mapTv[3][9] = cell;
    _mapTv[3][10] = cell;
    _mapTv[3][11] = cell;
    
    _mapTv[4][2] = cell;
    _mapTv[4][4] = cell;
    _mapTv[4][5] = cell;
    _mapTv[4][6] = cell;
    _mapTv[4][7] = cell;
    _mapTv[4][8] = cell;
    
    _mapTv[4][10] = cell;
    _mapTv[5][1] = cell;
    _mapTv[5][3] = cell;
    _mapTv[5][5] = cell;
    _mapTv[5][7] = cell;
    _mapTv[5][9] = cell;
    _mapTv[5][11] = cell;
    
    _mapTv[6][2] = cell;
    _mapTv[6][3] = cell;
    _mapTv[6][4] = cell;
    _mapTv[6][5] = cell;
    _mapTv[6][6] = cell;
    _mapTv[6][7] = cell;
    _mapTv[6][12] = cell;
    
    _mapTv[7][2] = cell;
    _mapTv[7][3] = cell;
    _mapTv[7][6] = cell;
    _mapTv[7][10] = cell;
    _mapTv[7][11] = cell;
    _mapTv[7][12] = cell;
    
    cell.type = 1;
    cell.fileName = "channel7.png";
    _mapTv[4][3] = cell;
    cell.fileName = "channel6.png";
    _mapTv[4][9] = cell;
    cell.fileName = "channel5.png";
    _mapTv[5][2] = cell;
    cell.fileName = "channel4.png";
    _mapTv[5][4] = cell;
    cell.fileName = "channel3.png";
    _mapTv[5][6] = cell;
    cell.fileName = "channel2.png";
    _mapTv[5][8] = cell;
    cell.fileName = "channel1.png";
    _mapTv[5][10] = cell;
    
    int temp = 1;
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            if( (*iter2).second.type == 2)
            {
                (*iter2).second.fileName = StringUtils::format("cell%02d.png", temp++);
            }
        }
    }
}

void MaskLayer::createCellTv2()
{
    removeChildByTag(NODE_TAG);
    
    Size s = Director::getInstance()->getVisibleSize();
    
    Node *pTemp = Node::create();
    
    addChild(pTemp);
    pTemp->setPosition(RectangleInterface::getCenterPosition());
    pTemp->setTag(NODE_TAG);
    pTemp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pTemp->setContentSize(RectangleInterface::getCellSize());
    
    float marginX = s.width/2+100;
    float marginY = s.height/2+100;
    
    float tempGlobalZ = 0.0;
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            tempGlobalZ += 0.1;
            
            auto sprite = cellTv::createNode((*iter2).second.fileName, tempGlobalZ);
            pTemp->addChild(sprite, 1);
            (*iter2).second.pNode = sprite;
            
            Vec2 destination = RectangleInterface::getPosition((*iter1).first, (*iter2).first);
            Vec2 source =destination;
            
            double degree = RectangleInterface::ConvertRadiansToDegrees(std::atan(destination.y/destination.x));
            if (destination.x >= 0 && destination.y >= 0) {
                if (degree < 45) {
                    //from right
                    source.x += marginX;
                }
                else{
                    //from top
                    source.y += marginY;
                }
            }
            else if (destination.x <= 0 && destination.y >= 0){
                degree += 180;
                if (degree < 135) {
                    //from top
                    source.y += marginY;
                }
                else{
                    //from left
                    source.x -= marginX;
                }
            }
            else if (destination.x <=0 && destination.y <= 0){
                degree += 180;
                if (degree < 225) {
                    //from left
                    source.x -= marginX;
                }
                else{
                    //from bottom
                    source.y -= marginY;
                }
            }
            else if (destination.x >=0 && destination.y <= 0){
                degree += 360;
                if (degree < 315) {
                    //from bottom
                    source.y -= marginY;
                }
                else{
                    //from right
                    source.x += marginX;
                }
            }
            
            float time = sqrt( powf(destination.x, 2) + powf(destination.y, 2) ) / 1000;
            time += CCRANDOM_0_1();
            
            sprite->setPosition(source);
            sprite->setSourcePosition(source);
            sprite->setDelayTime(time);
            sprite->setDestinationPosition(destination);
            sprite->runMoveAction();
        }
    }
    
    auto rotate_scale = Spawn::create(RotateBy::create(3, -30),
                                    ScaleTo::create(3, 1.5), NULL);
    
    pTemp->runAction(Sequence::create(DelayTime::create(3), rotate_scale, CallFunc::create( CC_CALLBACK_0(MaskLayer::callback21,this)), NULL));
}

void MaskLayer::callback21()
{
    Node *pNode = getChildByTag(NODE_TAG);
    pNode->runAction(Sequence::create(
                                      Spawn::create(
                                                    ScaleTo::create(0.5, 2),
                                                    RotateBy::create(0.5, Vec3(-30, 30, 5)),
                                                    MoveBy::create(0.5, Vec2(200, 150)),
                                                    NULL),
                                      DelayTime::create(0.1),
                                      CallFunc::create( CC_CALLBACK_0(MaskLayer::callback22,this)),
                                      NULL));
}

void MaskLayer::callback22()
{
    Node *pNode = getChildByTag(NODE_TAG);
    
    pNode->runAction(Sequence::create(
                                      MoveBy::create(10, Point(-250, -100)),
                                      CallFunc::create( CC_CALLBACK_0(MaskLayer::callback23,this)),
                                      NULL)
                     );
}

void MaskLayer::callback23()
{
    Node *pNode = getChildByTag(NODE_TAG);
    
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            cellTv *pcellTv = (cellTv* )(*iter2).second.pNode;
            float time = 1.5 + pcellTv->getDelayTime();
            auto action = MoveTo::create(time, pcellTv->getSourcePosition());
            pcellTv->runAction(EaseIn::create(action, time));
        }
    }
    
    pNode->runAction(Sequence::create(
                                      DelayTime::create(2.0),
                                      CallFunc::create( CC_CALLBACK_0(MaskLayer::callback24,this)),
                                      NULL)
                     );
}

void MaskLayer::callback24()
{
    removeChildByTag(NODE_TAG);
    
    Size s = Director::getInstance()->getVisibleSize();
    
    Node *pTemp = Node::create();
    
    addChild(pTemp);
    pTemp->setPosition(RectangleInterface::getCenterPosition());
    pTemp->setTag(NODE_TAG);
    pTemp->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pTemp->setContentSize(RectangleInterface::getCellSize());
    
    int marginX = s.width/2 + TEXTURE_WIDTH;
    int marginY = s.height/2 + TEXTURE_HEIGHT;
    
    float tempGlobalZ = 0.0;
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            tempGlobalZ += 0.1;
            auto sprite = cellTv::createNode((*iter2).second.fileName, tempGlobalZ);
            pTemp->addChild(sprite);
            
            Vec2 destination = RectangleInterface::getPosition((*iter1).first, (*iter2).first);
            Vec2 source =destination;
            
            double degree = RectangleInterface::ConvertRadiansToDegrees(std::atan(destination.y/destination.x));
            if (destination.x >= 0 && destination.y >= 0) {
                if (degree < 45) {
                    //from right
                    source.x += marginX;
                }
                else{
                    //from top
                    source.y += marginY;
                }
            }
            else if (destination.x <= 0 && destination.y >= 0){
                degree += 180;
                if (degree < 135) {
                    //from top
                    source.y += marginY;
                }
                else{
                    //from left
                    source.x -= marginX;
                }
            }
            else if (destination.x <=0 && destination.y <= 0){
                degree += 180;
                if (degree < 225) {
                    //from left
                    source.x -= marginX;
                }
                else{
                    //from bottom
                    source.y -= marginY;
                }
            }
            else if (destination.x >=0 && destination.y <= 0){
                degree += 360;
                if (degree < 315) {
                    //from bottom
                    source.y -= marginY;
                }
                else{
                    //from right
                    source.x += marginX;
                }
            }
            
            float time = sqrt( powf(destination.x, 2) + powf(destination.y, 2) ) / TEXTURE_WIDTH;
            time += CCRANDOM_0_1();
            
            sprite->setPosition(source);
            sprite->setSourcePosition(source);
            sprite->setDelayTime(time);
            sprite->setDestinationPosition(destination);
            sprite->runMoveAction();
            sprite->runRotateAction();
        }
    }
    initRemoteControl();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto testBg = Sprite::create("testbg.png");
    this->addChild(testBg);
    testBg->setPosition(visibleSize * 0.5);
}

void MaskLayer::initRemoteControl()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    VBox *outerLayout = VBox::create();
    outerLayout->setPosition(Point(0, visibleSize.height));
    outerLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
    LinearLayoutParameter *layoutParams = LinearLayoutParameter::create();
    layoutParams->setMargin(Margin(0, 0, 0, 0));
    
    for(int y = 1; y <= ROW; y++){
        HBox *bottomLayout = HBox::create();
        bottomLayout->setLayoutParameter(layoutParams);
        if (1 == y){
            bottomLayout->setFocused(true);
            _widget = bottomLayout;
        }
        for(int x = 1; x <= COL; x++){
            if (mapStr[y][x] == '1'){
                ImageView *imageView = ImageView::create();
                imageView->setLayoutParameter(layoutParams);
                bottomLayout->addChild(imageView);
                imageView->setTag(x * 100 + y);
            }
        }
        outerLayout->addChild(bottomLayout);
    }
    this->addChild(outerLayout);
    //register focus event
    _eventListener = EventListenerFocus::create();
    _eventListener->onFocusChanged = CC_CALLBACK_2(MaskLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(MaskLayer::onKeyboardReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
}

void MaskLayer::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus) {
        int x = widgetGetFocus->getTag() / 100;
        int y = widgetGetFocus->getTag() % 100;
        MessageBox(StringUtils::format("y=%d, x=%d", y, x).c_str(), "encal");
        if (_mapTv[y][x].pNode){
            _mapTv[y][x].pNode->setScale(1.2f);
            selectedSprite->setVisible(true);
            selectedSprite->setPosition(Vec2(_mapTv[y][x].pNode->getPosition()));
        }
    }
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus) {
        int x = widgetLostFocus->getTag() / 100;
        int y = widgetLostFocus->getTag() % 100;
        if (_mapTv[y][x].pNode){
            MessageBox(StringUtils::format("y=%d, x=%d", y, x).c_str(), "encal");
            
            _mapTv[y][x].pNode->setScale(1.0f);
        }
    }
}

void MaskLayer::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* e)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ) {
        //_preMaskLater->closeMe();
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

void MaskLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}