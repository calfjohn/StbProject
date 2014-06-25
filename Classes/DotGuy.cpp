//
//  DotGuy.cpp
//  stbProject
//
//  Created by EnCaL on 14-6-19.
//
//

#include "DotGuy.h"
#include "MaskLayer.h"
#include "RectangleInterface.h"

USING_NS_CC;
#define MOVE_SPEED 0.0001f
#define DELAY_TIME 31.0f
DotGuy* DotGuy::create(const cocos2d::Vec2& position, DotGuy::DIRECTION direction, cocos2d::Size blockSize, std::vector<std::string> mapData, const cocos2d::Vec2& startPoint, float lifeCycle)
{
    auto pRet = new DotGuy();
    if (pRet && pRet->init(position, direction, blockSize, mapData, startPoint, lifeCycle)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool DotGuy::init(const cocos2d::Vec2& position, DotGuy::DIRECTION direction, cocos2d::Size blockSize, std::vector<std::string> mapData, const cocos2d::Vec2& startPoint, float lifeCycle)
{
    m_position = position;
    m_directionStatus = direction;
    m_blockSize = blockSize;
    m_dataStr = mapData;
    m_bodySprite = Sprite::create("body.png");
    m_lifeCycle = lifeCycle;
    this->addChild(m_bodySprite);
    m_numOfStep = blockSize.width / m_bodySprite->getContentSize().width;
    
    m_bodySprite->setPosition(fixOffset(direction, startPoint));
    //m_bodySprite->setPosition(Vec2(startPoint.x, startPoint.y - ESCAPE_ARGUMENT));
    m_numOfFix = fixCount();
    return true;
}

Vec2 DotGuy::fixOffset(DotGuy::DIRECTION direction, cocos2d::Vec2 position)
{
    switch (direction) {
        case DotGuy::DIRECTION::LEFT:
            return Vec2(position.x, position.y - ESCAPE_ARGUMENT);
            break;
        case DotGuy::DIRECTION::DOWN:
            return Vec2(position.x - ESCAPE_ARGUMENT, position.y);
            break;
        case DotGuy::DIRECTION::RIGHT:
            return Vec2(position.x, position.y + ESCAPE_ARGUMENT);
            break;
        case DotGuy::DIRECTION::UP:
            return Vec2(position.x + ESCAPE_ARGUMENT, position.y);
            break;
    }
}

bool DotGuy::isWall(DotGuy::DIRECTION direction, cocos2d::Vec2 position)
{
    Vec2 tempVec2 = position;
    switch (direction) {
        case DotGuy::DIRECTION::LEFT:
            tempVec2.x -= 1;
            break;
        case DotGuy::DIRECTION::DOWN:
            tempVec2.y -= 1;
            break;
        case DotGuy::DIRECTION::RIGHT:
            tempVec2.x += 1;
            break;
        case DotGuy::DIRECTION::UP:
            tempVec2.y += 1;
            break;
    }
    if (tempVec2.x <= 0 || tempVec2.y <= 0 || tempVec2.x > RectangleInterface::getColumns() || tempVec2.y > RectangleInterface::getRows()){
        return false;
    }
    else{
        return m_dataStr[tempVec2.y][tempVec2.x] == '1';
    }
}

void DotGuy::walk()
{
    m_stepCount = 0;
    this->schedule(schedule_selector(DotGuy::walkUpdate), MOVE_SPEED);
}

DotGuy::DIRECTION DotGuy::nextDirection(cocos2d::Vec2 position)
{
    Vec2 tempVec2 = m_position;
    switch (m_directionStatus) {
        case DotGuy::DIRECTION::LEFT:
            if (isWall(DIRECTION::LEFT, m_position)){
                return DIRECTION::DOWN;
            }
            else{
                tempVec2.x -= 1;
                if (isWall(DIRECTION::UP, tempVec2)){
                    m_position.x -= 1;
                    return m_directionStatus;
                }
                else{
                    m_position.x -= 1;
                    m_position.y += 1;
                    return DIRECTION::UP;
                }
            }
            break;
        case DotGuy::DIRECTION::DOWN:
            if (isWall(DIRECTION::DOWN, m_position)){
                return DIRECTION::RIGHT;
            }
            else{
                tempVec2.y -= 1;
                if (isWall(DIRECTION::LEFT, tempVec2)){
                    m_position.y -= 1;
                    return m_directionStatus;
                }
                else{
                    m_position.x -= 1;
                    m_position.y -= 1;
                    return DIRECTION::LEFT;
                }
            }
            break;
        case DotGuy::DIRECTION::RIGHT:
            if (isWall(DIRECTION::RIGHT, m_position)){
                return DIRECTION::UP;
            }
            else{
                tempVec2.x += 1;
                if (isWall(DIRECTION::DOWN, tempVec2)){
                    m_position.x += 1;
                    return m_directionStatus;
                }
                else{
                    m_position.x += 1;
                    m_position.y -= 1;
                    return DIRECTION::DOWN;
                }
            }
            break;
        case DotGuy::DIRECTION::UP:
            if (isWall(DIRECTION::UP, m_position)){
                return DIRECTION::LEFT;
            }
            else{
                tempVec2.y += 1;
                if (isWall(DIRECTION::RIGHT, tempVec2)){
                    m_position.y += 1;
                    return m_directionStatus;
                }
                else{
                    m_position.x += 1;
                    m_position.y += 1;
                    return DIRECTION::RIGHT;
                }
            }
            break;
    }
}

DotGuy::DIRECTION DotGuy::getNextDirection(cocos2d::Vec2 position)
{
    Vec2 tempVec2 = m_position;
    switch (m_directionStatus) {
        case DotGuy::DIRECTION::LEFT:
            if (isWall(DIRECTION::LEFT, m_position)){
                return DIRECTION::DOWN;
            }
            else{
                tempVec2.x -= 1;
                if (isWall(DIRECTION::UP, tempVec2)){
                    return m_directionStatus;
                }
                else{
                    return DIRECTION::UP;
                }
            }
            break;
        case DotGuy::DIRECTION::DOWN:
            if (isWall(DIRECTION::DOWN, m_position)){
                return DIRECTION::RIGHT;
            }
            else{
                tempVec2.y -= 1;
                if (isWall(DIRECTION::LEFT, tempVec2)){
                    return m_directionStatus;
                }
                else{
                    return DIRECTION::LEFT;
                }
            }
            break;
        case DotGuy::DIRECTION::RIGHT:
            if (isWall(DIRECTION::RIGHT, m_position)){
                return DIRECTION::UP;
            }
            else{
                tempVec2.x += 1;
                if (isWall(DIRECTION::DOWN, tempVec2)){
                    return m_directionStatus;
                }
                else{
                    return DIRECTION::DOWN;
                }
            }
            break;
        case DotGuy::DIRECTION::UP:
            if (isWall(DIRECTION::UP, m_position)){
                return DIRECTION::LEFT;
            }
            else{
                tempVec2.y += 1;
                if (isWall(DIRECTION::RIGHT, tempVec2)){
                    return m_directionStatus;
                }
                else{
                    return DIRECTION::RIGHT;
                }
            }
            break;
    }
}

void DotGuy::walkUpdate(float delta)
{
    m_stepCount++;
    Vec2 nextMovePosition = getNextMovePosition();
    //CCLOG("MY_X = %f, MY_Y = %f", nextMovePosition.x, nextMovePosition.y);
    this->createCycleBody(nextMovePosition);
    m_bodySprite->setPosition(nextMovePosition);
    if ( m_stepCount >= ( m_numOfStep + m_numOfFix ) ){
        m_stepCount = 0 - m_addStep;
       // CCLOG("%f, %f, %d", m_position.x, m_position.y, m_directionStatus);
        m_oldDirectionStatus = m_directionStatus;
        m_directionStatus = nextDirection(m_position);
        m_numOfFix = fixCount();
       // CCLOG("y = %f, x = %f, step = %d, nextOffset = %d", m_position.y, m_position.x, m_numOfStep + m_numOfFix, m_addStep);
    }
}

int DotGuy::fixCount()
{
    DIRECTION myNextDirection = this->getNextDirection(m_position);
    int surplusStep = ESCAPE_ARGUMENT / (m_bodySprite->getContentSize().width);
    if (myNextDirection == m_directionStatus){
        m_addStep = 0;
        return 1;
    }
    Vec2 position = m_position;
    switch (m_directionStatus) {
        case DotGuy::DIRECTION::LEFT:
            if (myNextDirection == DotGuy::DIRECTION::UP){
                m_addStep = surplusStep;
                return surplusStep + 1;
            }
            else if (myNextDirection == DotGuy::DIRECTION::DOWN){
                m_addStep = - surplusStep;
                return - surplusStep + 1;
            }
            break;
        case DotGuy::DIRECTION::DOWN:
            if (myNextDirection == DotGuy::DIRECTION::LEFT){
                m_addStep = surplusStep;
                return surplusStep + 1;
            }
            else if (myNextDirection == DotGuy::DIRECTION::RIGHT){
                m_addStep = - surplusStep;
                return - surplusStep + 1;
            }
            break;
        case DotGuy::DIRECTION::RIGHT:
            if (myNextDirection == DotGuy::DIRECTION::DOWN){
                m_addStep = surplusStep;
                return surplusStep + 1;
            }
            else if (myNextDirection == DotGuy::DIRECTION::UP){
                m_addStep = - surplusStep;
                return - surplusStep + 1;
            }
            break;
        case DotGuy::DIRECTION::UP:
            if (myNextDirection == DotGuy::DIRECTION::RIGHT){
                m_addStep = surplusStep;
                return surplusStep + 1;
            }
            else if (myNextDirection == DotGuy::DIRECTION::LEFT){
                m_addStep = - surplusStep;
                return - surplusStep + 1;
            }
            break;
    }
}

Vec2 DotGuy::getNextMovePosition()
{
    Vec2 position = m_bodySprite->getPosition();
    switch (m_directionStatus) {
        case DotGuy::DIRECTION::LEFT:
            position.x -= m_bodySprite->getContentSize().width;
            break;
        case DotGuy::DIRECTION::DOWN:
            position.y -= m_bodySprite->getContentSize().height;
            break;
        case DotGuy::DIRECTION::RIGHT:
            position.x += m_bodySprite->getContentSize().width;
            break;
        case DotGuy::DIRECTION::UP:
            position.y += m_bodySprite->getContentSize().height;
            break;
    }
    return position;
}

void DotGuy::createCycleBody(cocos2d::Vec2 position)
{
    auto cycleSprite = Sprite::create("body.png");
    this->addChild(cycleSprite);
    cycleSprite->setPosition(position);
    auto fadeOut = FadeOut::create(1.0f);
    cycleSprite->runAction(Sequence::create(DelayTime::create(m_lifeCycle), fadeOut, RemoveSelf::create(), NULL));
}