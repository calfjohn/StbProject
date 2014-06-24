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
#include "SetTopBoxMainScene.h"
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
#define TOP_ZORDER 1000
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
    
    RectangleInterface::initialize(ROW, COL, Size(TEXTURE_WIDTH, TEXTURE_HEIGHT), CELL_SPACE, Vec2(visibleSize.width/2, visibleSize.height/2));
    
    initTvMap();
    
    createCellTv2();
    
    addLight();
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
        m_pic->setLocalZOrder(recoverzOrder);
        auto actionOrb = OrbitCamera::create(FIRST_TIME, 1.0f, 0.0f, 90.0f, -90.0f, 0.0f, 0.0f);
        auto moveTo = EaseSineOut::create(MoveTo::create(FIRST_TIME, recoverPoint));
        auto scaleTo = ScaleTo::create(FIRST_TIME, 1.0f);
        m_pic->runAction(Sequence::create(Spawn::create(actionOrb, moveTo, scaleTo, NULL), CallFunc::create([&](){
            this->getFocus();
        }), NULL));
    }) , RemoveSelf::create(), NULL));
}

void MaskLayer::addLight(){
    auto winSize = Director::getInstance()->getWinSize();
    _rotateLight = Sprite::create("rotate_light.png");
    _rotateLight->setScale(2);
    _rotateLight->runAction(RepeatForever::create(RotateBy::create(0.1, 0.5)));
    _rotateLight->setPosition(winSize.width/2-300,winSize.height + 100);
    _rotateLight->setGlobalZOrder(10);
    this->addChild(_rotateLight);
}

void MaskLayer::initTvMap()
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("tvMap.plist");
    cache->addSpriteFramesWithFile("tvChannel.plist");
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
    _mapTv[7][4] = cell;
    _mapTv[7][5] = cell;
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
    
    Node *pTvNode = Node::create();
    
    this->addChild(pTvNode);
    pTvNode->setPosition(RectangleInterface::getCenterPosition());
    pTvNode->setTag(NODE_TAG);
    pTvNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    pTvNode->setContentSize(RectangleInterface::getCellSize());
    
    selectedSprite = Sprite::create("selectedBlock.png");
    pTvNode->addChild(selectedSprite);
    selectedSprite->setVisible(false);
    selectedSprite->setGlobalZOrder(999);
    
    float marginX = s.width;
    float marginY = s.height;
    
    float tempGlobalZ = 0.0;
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            tempGlobalZ += 0.1;
            
            auto sprite = cellTv::createNode((*iter2).second.fileName, tempGlobalZ, (*iter2).second.type == 2);
            pTvNode->addChild(sprite, 1);
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
            log("time.....%f",time);
            sprite->setPosition(source);
            sprite->setSourcePosition(source);
            sprite->setDelayTime(time);
            sprite->setDestinationPosition(destination);
            sprite->moveToDestination();
        }
    }
    
    callback20();
}

void MaskLayer::callback20()
{
    Node *pNode = getChildByTag(NODE_TAG);
    if (pNode == NULL) return;
    
    auto move_scale = Spawn::create(EaseSineOut::create(RotateBy::create(3, -30)),
                                    EaseSineOut::create(ScaleTo::create(3, 1.5)), NULL);
    
    pNode->runAction(Sequence::create(DelayTime::create(3), move_scale, CallFunc::create( CC_CALLBACK_0(MaskLayer::callback21,this)), NULL));
}

void MaskLayer::callback21()
{
    float delayTime = 0.1f;
    
    auto flash = LayerColor::create(Color4B::WHITE);
    this->addChild(flash);
    
    flash->setGlobalZOrder(1000);
    auto flashAction = Sequence::create(
                                        //FadeIn::create(delayTime/2),
                                        FadeOut::create(delayTime),
                                        RemoveSelf::create(),
                                        nullptr);
    flash->runAction(flashAction);
    
    Node *pNode = getChildByTag(NODE_TAG);
    if (pNode == NULL) return;
    
    pNode->runAction(Sequence::create(DelayTime::create(delayTime),
                                      EaseQuadraticActionIn::create(Spawn::create(
                                                                                  ScaleTo::create(0.3, 1.0),
                                                                                  RotateBy::create(0.3, Vec3(-30, 30, 15)),
                                                                                  MoveBy::create(0.3, Vec2(300, 250)),
                                                                                  NULL)),
                                      DelayTime::create(0.1),
                                      CallFunc::create( CC_CALLBACK_0(MaskLayer::callback22,this)),
                                      NULL));
}

void MaskLayer::callback22()
{
    
    Node *pNode = getChildByTag(NODE_TAG);
    if (pNode == NULL) return;
    
    std::map<int, structCell>::iterator iter;
    for(int i = 1; i <=COL; i++)
    {
        for(int j = 1; j <=ROW; j++)
        {
            iter = _mapTv[j].find(i);
            if( iter == _mapTv[j].end()) continue;
            
            cellTv *pcellTv = (cellTv* )(*iter).second.pNode;
            if(pNode == NULL) continue;
            
            if((*iter).second.type == 1) continue;
            
            pcellTv->rotateDelay(i);
        }
    }
    
    pNode->runAction(Sequence::create(//DelayTime::create(delayTime*2),
                                      EaseSineOut::create(MoveBy::create(5.0, Point(-250, -100))),
                                      CallFunc::create( CC_CALLBACK_0(MaskLayer::callback23,this)),
                                      MoveBy::create(3.0, Point(-250, -100)),
                                      NULL)
                     );
}

void MaskLayer::callback23()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    auto flash = Sprite::create("flash.png");
    this->addChild(flash);
    
    flash->setScale(5);
    flash->setVisible(false);
    flash->setPosition(_rotateLight->getPosition());
    flash->setGlobalZOrder(10000);
    
    flash->runAction(Sequence::create(DelayTime::create(1.8f),
                                      Show::create(),
                                      EaseQuadraticActionIn::create(ScaleTo::create(0.2, 70)),
                                      CallFunc::create([=](){
                                            _rotateLight->setPosition(winSize.width/2+300,winSize.height + 100);
                                            flash->setPosition(_rotateLight->getPosition());
                                        }),
                                      EaseQuadraticActionOut::create(ScaleTo::create(0.2, 5)),
                                      RemoveSelf::create(),
                                      NULL));

    
    Node *pNode = getChildByTag(NODE_TAG);
    if (pNode == NULL) return;
    
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            cellTv *pcellTv = (cellTv* )(*iter2).second.pNode;
            if(pNode == NULL) continue;
            
            pcellTv->moveToSource();
        }
    }
    
    pNode->runAction(Sequence::create(
                                      DelayTime::create(3.0),
                                      CallFunc::create( CC_CALLBACK_0(MaskLayer::callback24,this)),
                                      NULL)
                     );
}

void MaskLayer::callback24()
{
    Node *pNode = getChildByTag(NODE_TAG);
    if (pNode == NULL) return;
    
    pNode->setPosition(RectangleInterface::getCenterPosition());
    pNode->setScale(1);
    pNode->setRotation3D(Vec3::ZERO);
    
    std::map<int, std::map<int, structCell>>::iterator iter1;
    std::map<int, structCell>::iterator iter2;
    for(iter1 = _mapTv.begin(); iter1 != _mapTv.end(); ++iter1)
    {
        std::map<int, structCell> &tempMap = (*iter1).second;
        for(iter2 = tempMap.begin(); iter2 != tempMap.end(); ++iter2)
        {
            cellTv *pNode = (cellTv *)(*iter2).second.pNode;
            if(pNode == NULL) continue;
            
            pNode->moveToDestination();
            pNode->runRotateAction();
        }
    }
    
    initRemoteControl();
}

void MaskLayer::initRemoteControl()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    VBox *outerLayout = VBox::create();
    outerLayout->setPosition(Point(0, visibleSize.height));
    outerLayout->setContentSize(Size(visibleSize.width, visibleSize.height));
    LinearLayoutParameter *layoutParams = LinearLayoutParameter::create();
    layoutParams->setMargin(Margin(0, 0, 0, 0));
    
    bool isFirst = true;
    Size blockSize;
    for(int y = 1; y <= ROW; y++){
        HBox *bottomLayout = HBox::create();
        bottomLayout->setLayoutParameter(layoutParams);
        for(int x = 1; x <= COL; x++){
            if (mapStr[y][x] == '1'){
                ImageView *imageView = ImageView::create();
                imageView->setLayoutParameter(layoutParams);
                bottomLayout->addChild(imageView);
                imageView->setTag(x * 100 + y);
                if (isFirst){
                    m_pic = (Sprite*)_mapTv[y][x].pNode;
                    imageView->setFocused(true);
                    _widget = imageView;
                    blockSize = _mapTv[y][x].pNode->getContentSize();
                    
                    selectedSprite->setVisible(true);
                    selectedSprite->setPosition(RectangleInterface::getPosition(y, x));
                    selectedSprite->setLocalZOrder(100);
                    
                    isFirst = false;
                }
                imageView->setContentSize(blockSize);
                imageView->setPosition(RectangleInterface::getPosition(y, x));
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
    
    //for test
    this->setTouchEnabled(true);
}

void MaskLayer::onFocusChanged(cocos2d::ui::Widget *widgetLostFocus, cocos2d::ui::Widget *widgetGetFocus)
{
    Layout *getLayout1 = dynamic_cast<Layout*>(widgetLostFocus);
    if (!getLayout1 && widgetLostFocus) {
        int x = widgetLostFocus->getTag() / 100;
        int y = widgetLostFocus->getTag() % 100;
        
        cellTv *pNode = (cellTv*)_mapTv[y][x].pNode;
        pNode->runAction(ScaleTo::create(0.02, 1.0));
        pNode->resetGlobelZorder();
    }
    
    Layout *getLayout = dynamic_cast<Layout*>(widgetGetFocus);
    if (!getLayout && widgetGetFocus) {
        int x = widgetGetFocus->getTag() / 100;
        int y = widgetGetFocus->getTag() % 100;
        m_pic = (Sprite*)_mapTv[y][x].pNode;
        cellTv *pNode = (cellTv *)m_pic;
        if (pNode){
            pNode->runAction(EaseSineOut::create(ScaleTo::create(0.05, 1.5)));
            pNode->bringNodeToTop();
//            pNode->setScale(1.1f);
//            pNode->runAction(Sequence::create(ScaleTo::create(0.02, 1.1f), ScaleTo::create(0.02, 1.0f) , NULL));
            selectedSprite->runAction(EaseSineOut::create(ScaleTo::create(0.05, 1.5)));
            selectedSprite->setPosition(pNode->getPosition());
        }
    }
    Layout *loseLayout = dynamic_cast<Layout*>(widgetLostFocus);
    if (!loseLayout && widgetLostFocus) {
        /*
        int x = widgetLostFocus->getTag() / 100;
        int y = widgetLostFocus->getTag() % 100;
        if (_mapTv[y][x].pNode){
            _mapTv[y][x].pNode->setScale(1.0f);
        }*/
    }
}

void MaskLayer::onKeyboardReleased(EventKeyboard::KeyCode keyCode, Event* e)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ) {
        auto newScene = SetTopBoxMainScene::createScene();
        auto FadeScene = TransitionFade::create(0.3f, newScene, Color3B::WHITE);
        Director::getInstance()->replaceScene(FadeScene);
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
    else if (keyCode == EventKeyboard::KeyCode::KEY_DPAD_CENTER || keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
        if (m_pic){
            this->lostFocus();
            auto winSize = Director::getInstance()->getWinSize();
            
            m_moreDetailLayer = MoreDetailLayer::create();
            Director::getInstance()->getRunningScene()->addChild(m_moreDetailLayer);
            m_moreDetailLayer->setVisible(false);
            m_moreDetailLayer->setPreMaskLayer(this);
            
            auto actionOrb = OrbitCamera::create(FIRST_TIME, 1.0f, 0.0f, 0.0f, 90.0f, 0.0f, 0.0f);
            auto moveTo = EaseSineOut::create(MoveTo::create(FIRST_TIME, m_pic->getParent()->convertToNodeSpace(winSize * 0.5)));
            auto scaleTo = ScaleTo::create(FIRST_TIME, 3.0f);
            recoverPoint = m_pic->getPosition();
            recoverzOrder = m_pic->getLocalZOrder();
            m_pic->setLocalZOrder(TOP_ZORDER);
            m_pic->runAction(Sequence::create(Spawn::create(actionOrb, moveTo, scaleTo, NULL), CallFunc::create([this](){
                m_pic->setVisible(false);
                m_moreDetailLayer->setVisible(true);
                auto actionOrb = OrbitCamera::create(SECOND_TIME, 1.0f, 0.0f, 270.0f, 90.0f, 0.0f, 0.0f);
                m_moreDetailLayer->setScale(0.4f);
                auto actionScaleTo = ScaleTo::create(SECOND_TIME, 0.9f);
                m_moreDetailLayer->runAction(Spawn::create(actionOrb, actionScaleTo, NULL));
            }), NULL));
        }
    }
}

void MaskLayer::lostFocus()
{
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}

void MaskLayer::getFocus()
{
    //register focus event
    _eventListener = EventListenerFocus::create();
    _eventListener->onFocusChanged = CC_CALLBACK_2(MaskLayer::onFocusChanged, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_eventListener, 1);
    //register the keyboard event
    _keyboardListener = EventListenerKeyboard::create();
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(MaskLayer::onKeyboardReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 2);
}

void MaskLayer::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(_eventListener);
    _eventDispatcher->removeEventListener(_keyboardListener);
}

void MaskLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    Touch *touch = touches.at(0);
    Point pt = touch->getLocationInView();
    pt = Director::getInstance()->convertToGL(pt);
    //    CCLOG("x=%f, y = %f", pt.x, pt.y);
    _beginPoint = pt;
}

void MaskLayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}

void MaskLayer::onTouchesCancelled(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    
}
void MaskLayer::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
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
        onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_DOWN, nullptr);
    }
    
    if (pt.y - _beginPoint.y > offest) {
        onKeyboardReleased(EventKeyboard::KeyCode::KEY_DPAD_UP, nullptr);
    }
}
