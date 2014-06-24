//
//  DotGuy.h
//  stbProject
//
//  Created by EnCaL on 14-6-19.
//
//

#ifndef __stbProject__dotGuy__
#define __stbProject__dotGuy__
#define ESCAPE_ARGUMENT 20
#define OFFSET_X -88
#define OFFSET_Y -13
#include "cocos2d.h"
class DotGuy : public cocos2d::Node{
public:
    enum DIRECTION{
        LEFT,
        DOWN,
        RIGHT,
        UP
    };
    
    static DotGuy* create(const cocos2d::Vec2& position, DIRECTION direction, cocos2d::Size blockSize, cocos2d::Layer* dataLayer);
    bool init(const cocos2d::Vec2& position, DIRECTION direction, cocos2d::Size blockSize, cocos2d::Layer* dataLayer);
    bool isWall(DIRECTION direction, cocos2d::Vec2 position);
    void walk();
    DIRECTION nextDirection(cocos2d::Vec2 position);
    DIRECTION getNextDirection(cocos2d::Vec2 position);
    
    cocos2d::Vec2 fixOffset(DIRECTION direction, cocos2d::Vec2 position);
    cocos2d::Vec2 escapeBlock(DIRECTION direction, cocos2d::Vec2 position);
    cocos2d::Vec2 getNextMovePosition();
    int fixCount();
    
    DIRECTION getMyDirectionStatus(){return m_directionStatus;}
    void createCycleBody(cocos2d::Vec2 position);
    
    void walkUpdate(float delta);
private:
    DIRECTION m_oldDirectionStatus;
    DIRECTION m_directionStatus;
    cocos2d::Sprite* m_bodySprite;
    cocos2d::Size m_blockSize;
    int m_numOfStep;
    int m_numOfFix;
    int m_stepCount;
    int m_addStep;
    cocos2d::Vec2 m_position;
    cocos2d::Layer* m_dataSource;
};

#endif /* defined(__stbProject__dotGuy__) */
